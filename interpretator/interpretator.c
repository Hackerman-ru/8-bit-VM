#include "../interpretator.h"

#include "../condition.h"
#include "../instructions.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void open_file(Condition *condition, char **argv, FILE **file) {
    if (condition->state != OK) {
        return;
    }

    if ((*file = fopen(argv[1], "rb")) == NULL) {
        condition->state = NO_FILE_FOUND;
        condition->str_info = argv[1];
    }
}

static void close_file(Condition *condition, FILE *file) {
    if (condition->state != OK) {
        return;
    }

    if (fclose(file) != 0) {
        condition->state = ERROR_WHEN_CLOSING;
    }
}

static void get_instruction_and_arguments(Condition *condition,
                                          FILE *source_file,
                                          Instruction *instruction,
                                          uint8_t *args) {
    if (condition->state != OK) {
        return;
    }

    uint8_t buff[3] = {};

    if (fread(buff, sizeof(*buff), 3, source_file) != 3) {
        if (ferror(source_file)) {
            condition->state = ERROR_WHEN_READING;
            return;
        }

        *instruction = eof;
        return;
    }

    *instruction = (Instruction)(buff[0]);
    args[0] = buff[1];
    args[1] = buff[2];
}

static void execute(Condition *condition, void *memory, uint8_t *registers,
                    Instruction instruction, uint8_t *args, FILE *source_file) {
    switch (instruction) {
    case movrr:
        registers[args[1]] = registers[args[0]];
        break;
    case movnr:
        registers[args[1]] = args[0];
        break;
    case movmr:
        registers[args[1]] = *(uint8_t *)(memory + args[0]);
        break;
    case movrm:
        *(uint8_t *)(memory + args[1]) = registers[args[0]];
        break;
    case xorrr:
        registers[args[1]] ^= registers[args[0]];
        break;
    case andrr:
        registers[args[1]] &= registers[args[0]];
        break;
    case borrr:
        registers[args[1]] |= registers[args[0]];
        break;
    case addrr:
        registers[args[1]] += registers[args[0]];
        break;
    case subrr:
        registers[args[1]] -= registers[args[0]];
        break;
    case shlnr:
        registers[args[1]] <<= args[0];
        break;
    case shrnr:
        registers[args[1]] >>= args[0];
        break;
    case jmpn:
        if (fseek(source_file, args[0], SEEK_SET) != 0) {
            condition->state = JMP_ERROR;
        }
        break;
    case jrznr:
        if (registers[args[1]] == 0) {
            if (fseek(source_file, args[0], SEEK_SET) != 0) {
                condition->state = JMP_ERROR;
            }
        }
        break;
    case eof:
        break;
    }
}

static void print_registers(uint8_t *registers) {
    for (int i = 0; i < 4; ++i) {
        printf("Register %d = %" PRId8 "\n", i, registers[i]);
    }
}

Condition interpret(char **argv) {
    FILE *source_file;
    Condition condition;
    condition.state = OK;

    open_file(&condition, argv, &source_file);

    if (condition.state != OK) {
        return condition;
    }

    void *memory = malloc(256);
    uint8_t registers[4] = {};
    print_registers(registers);

    do {
        Instruction instruction = eof;
        uint8_t args[2] = {};
        get_instruction_and_arguments(&condition, source_file, &instruction,
                                      args);
        if (instruction == eof) {
            break;
        }

        execute(&condition, memory, registers, instruction, args, source_file);
        print_registers(registers);
    } while (condition.state == OK);

    free(memory);
    close_file(&condition, source_file);

    return condition;
}