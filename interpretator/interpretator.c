#include "../interpretator.h"

#include "../condition.h"
#include "../instructions.h"
#include "../paths.h"
#include "file_manager.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG

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
    case movmrr:
        registers[args[1]] = *(uint8_t *)(memory + registers[args[0]]);
        break;
    case movrmr:
        *(uint8_t *)(memory + registers[args[1]]) = registers[args[0]];
        break;
    case decr:
        registers[args[0]]--;
        break;
    case incr:
        registers[args[0]]++;
        break;
    case empty:
        break;
    }
}

#ifdef DEBUG
static void print_registers(uint8_t *registers) {
    for (int i = 0; i < 4; ++i) {
        printf("Register %d = %" PRId8 "\n", i, registers[i]);
    }
    printf("\n");
}

static void print_memory(void *memory) {
    uint8_t *data = memory;
    for (size_t i = 0; i < 20; ++i) {
        printf("%" PRId8 " ", data[i]);
    }
    printf("\n");
}
#endif

Condition interpret(int argc, char **argv) {
    char *source_path;
    FILE *source_file;
    Condition condition;
    condition.state = OK;

    get_interpret_path(&condition, argc, argv, &source_path);
    open_file(&condition, source_path, &source_file);

    if (condition.state != OK) {
        return condition;
    }

    void *memory = malloc(256);
    uint8_t registers[4] = {};
#ifdef DEBUG
    *(uint8_t *)memory = 13;
    print_registers(registers);
    print_memory(memory);
#endif

    do {
        Instruction instruction = eof;
        uint8_t args[2] = {};
        get_instruction_and_arguments(&condition, source_file, &instruction,
                                      args);
        if (instruction == eof) {
            break;
        }

        execute(&condition, memory, registers, instruction, args, source_file);
#ifdef DEBUG
        print_registers(registers);
        print_memory(memory);
#endif
    } while (condition.state == OK);

    free(memory);
    close_file(&condition, source_file);

    return condition;
}