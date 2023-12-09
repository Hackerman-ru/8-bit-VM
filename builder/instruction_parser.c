#include "instruction_parser.h"

#include "../instructions.h"
#include "file_manager.h"

#include <ctype.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    REGISTER,
    NUMBER,
    MEMORY,
    MEMORY_REGISTER,
    JUNK,
} Argument;

static Argument get_argument(uint8_t *value) {
    char *temp;
    char *inst = strtok(NULL, " ,");

    if (inst == NULL) {
        return JUNK;
    }

    if (*inst == 'r') {
        *value = (uint8_t)strtol(inst + 1, &temp, 0);

        if (*value >= 0 && *value <= 4) {
            return REGISTER;
        }

        return JUNK;
    }

    if (*inst == '[') {
        if (*(inst + 1) == 'r') {
            *value = (uint8_t)strtol(inst + 2, &temp, 0);

            if (*value >= 0 && *value <= 4 && *temp == ']') {
                return MEMORY_REGISTER;
            }

            return JUNK;
        }

        long num = strtol(inst + 1, &temp, 0);

        if (*temp != ']') {
            return JUNK;
        }

        if (num != (long)(uint8_t)num) {
            return JUNK;
        }

        *value = (uint8_t)num;

        return MEMORY;
    }

    *value = strtol(inst, &temp, 0);

    return NUMBER;
}

static void make_invalid(Condition *condition, char *buff) {
    condition->state = INVALID_ARGUMENTS_FOR_INSTRUCTION;
    condition->str_info = buff;
}

static bool is_empty(char *buff) {
    for (size_t i = 0; buff[i] != '\0'; ++i) {
        if (!isspace(buff[i])) {
            return false;
        }
    }

    return true;
}

static void get_instruction_and_arguments(Condition *condition, FILE *source,
                                          Instruction *instruction,
                                          uint8_t *arg_buff) {
    if (condition->state != OK) {
        return;
    }

    char *buff = NULL;
    size_t size;

    if (getline(&buff, &size, source) == -1) {
        *instruction = eof;
        free(buff);
        return;
    }

    if (is_empty(buff)) {
        *instruction = empty;
        free(buff);
        return;
    }

    char *buff_copy = strdup(buff);
    char *inst = strtok(buff, " ");

    if (inst == NULL) {
        *instruction = eof;
        free(buff);
        free(buff_copy);
        return;
    }

    if (*inst == '/' && *(inst + 1) == '/') {
        *instruction = empty;
        free(buff);
        free(buff_copy);
        return;
    } else if (strcmp(inst, "mov") == 0) {
        Argument argument = get_argument(arg_buff++);

        switch (argument) {
        case JUNK:
            make_invalid(condition, buff_copy);
            break;
        case NUMBER:
            argument = get_argument(arg_buff);

            if (argument != REGISTER) {
                make_invalid(condition, buff_copy);
            }

            *instruction = movnr;
            break;
        case MEMORY:
            argument = get_argument(arg_buff);

            if (argument != REGISTER) {
                make_invalid(condition, buff_copy);
            }

            *instruction = movmr;
            break;
        case REGISTER:
            argument = get_argument(arg_buff);

            switch (argument) {
            case REGISTER:
                *instruction = movrr;
                break;
            case MEMORY:
                *instruction = movrm;
                break;
            case MEMORY_REGISTER:
                *instruction = movrmr;
                break;
            default:
                make_invalid(condition, buff_copy);
            }

            break;
        case MEMORY_REGISTER:
            argument = get_argument(arg_buff);

            if (argument != REGISTER) {
                make_invalid(condition, buff_copy);
            }

            *instruction = movmrr;
            break;
        }
    } else if (strcmp(inst, "xor") == 0) {
        Argument argument = get_argument(arg_buff++);

        if (argument != REGISTER) {
            make_invalid(condition, buff_copy);
        }

        argument = get_argument(arg_buff);

        if (argument != REGISTER) {
            make_invalid(condition, buff_copy);
        }

        *instruction = xorrr;
    } else if (strcmp(inst, "and") == 0) {
        Argument argument = get_argument(arg_buff++);

        if (argument != REGISTER) {
            make_invalid(condition, buff_copy);
        }

        argument = get_argument(arg_buff);

        if (argument != REGISTER) {
            make_invalid(condition, buff_copy);
        }

        *instruction = andrr;
    } else if (strcmp(inst, "bor") == 0) {
        Argument argument = get_argument(arg_buff++);

        if (argument != REGISTER) {
            make_invalid(condition, buff_copy);
        }

        argument = get_argument(arg_buff);

        if (argument != REGISTER) {
            make_invalid(condition, buff_copy);
        }

        *instruction = borrr;
    } else if (strcmp(inst, "add") == 0) {
        Argument argument = get_argument(arg_buff++);

        if (argument != REGISTER) {
            make_invalid(condition, buff_copy);
        }

        argument = get_argument(arg_buff);

        if (argument != REGISTER) {
            make_invalid(condition, buff_copy);
        }

        *instruction = addrr;
    } else if (strcmp(inst, "sub") == 0) {
        Argument argument = get_argument(arg_buff++);

        if (argument != REGISTER) {
            make_invalid(condition, buff_copy);
        }

        argument = get_argument(arg_buff);

        if (argument != REGISTER) {
            make_invalid(condition, buff_copy);
        }

        *instruction = subrr;
    } else if (strcmp(inst, "shl") == 0) {
        Argument argument = get_argument(arg_buff++);

        if (argument != NUMBER) {
            make_invalid(condition, buff_copy);
        }

        argument = get_argument(arg_buff);

        if (argument != REGISTER) {
            make_invalid(condition, buff_copy);
        }

        *instruction = shlnr;
    } else if (strcmp(inst, "shr") == 0) {
        Argument argument = get_argument(arg_buff++);

        if (argument != NUMBER) {
            make_invalid(condition, buff_copy);
        }

        argument = get_argument(arg_buff);

        if (argument != REGISTER) {
            make_invalid(condition, buff_copy);
        }

        *instruction = shrnr;
    } else if (strcmp(inst, "jmp") == 0) {
        Argument argument = get_argument(arg_buff++);

        if (argument != NUMBER) {
            make_invalid(condition, buff_copy);
        }

        *instruction = jmpn;
    } else if (strcmp(inst, "jrz") == 0) {
        Argument argument = get_argument(arg_buff++);

        if (argument != NUMBER) {
            make_invalid(condition, buff_copy);
        }

        argument = get_argument(arg_buff);

        if (argument != REGISTER) {
            make_invalid(condition, buff_copy);
        }

        *instruction = jrznr;
    } else if (strcmp(inst, "inc") == 0) {
        Argument argument = get_argument(arg_buff++);

        if (argument != REGISTER) {
            make_invalid(condition, buff_copy);
        }

        *instruction = incr;
    } else if (strcmp(inst, "dec") == 0) {
        Argument argument = get_argument(arg_buff++);

        if (argument != REGISTER) {
            make_invalid(condition, buff_copy);
        }

        *instruction = decr;
    } else {
        condition->state = UNKNOWN_INSTRUCTION;
        condition->str_info = strdup(inst);
    }

    free(buff);

    if (condition->state == OK) {
        free(buff_copy);
    }
}

void parse_instructions(Condition *condition, FILE *source, FILE *destination) {
    if (condition->state != OK) {
        return;
    }

    Instruction instruction;

    for (size_t line_number = 1; instruction != eof; line_number++) {
        uint8_t buff[3] = {};
        get_instruction_and_arguments(condition, source, &instruction,
                                      buff + 1);

        if (condition->state != OK) {
            condition->int_info = line_number;
            break;
        }

        if (instruction != eof && instruction != empty) {
            buff[0] = (uint8_t)instruction;
            write_command(condition, buff, destination);

            if (condition->state != OK) {
                break;
            }
        }
    }
}