#include "builder.h"
#include "instructions.h"
#include "paths.h"
#include "print.h"
#include "vm_condition.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

static Condition open_files(char *source_path, char *destination_path,
                            FILE **source_file, FILE **destination_file) {
    Condition condition;
    condition.state = OK;

    if ((*source_file = fopen(source_path, "r")) == NULL) {
        condition.state = NO_FILE_FOUND;
    } else if ((*destination_file = fopen(destination_path, "wb")) == NULL) {
        condition.state = BAD_DESTINATION_PATH;
    }

    return condition;
}

static Condition close_files(FILE *source_file, FILE *destination_file) {
    int source_res = fclose(source_file);
    int destination_res = fclose(destination_file);
    Condition condition;
    condition.state = OK;

    if (source_res != 0 || destination_res != 0) {
        condition.state = ERROR_WHEN_CLOSING;
    }

    return condition;
}

static Condition get_instruction_and_arguments(FILE *source, instruction *inst,
                                               int *buf) {
    Condition condition;
    condition.state = OK;
    char inst_str[3];
    fscanf(source, "%s", inst_str);

    if (strcmp(inst_str, "mov") == 0) {
    } else if (strcmp(inst_str, "xor") == 0) {

    } else if (strcmp(inst_str, "and") == 0) {

    } else if (strcmp(inst_str, "bor") == 0) {

    } else if (strcmp(inst_str, "add") == 0) {

    } else if (strcmp(inst_str, "sub") == 0) {

    } else if (strcmp(inst_str, "shl") == 0) {

    } else if (strcmp(inst_str, "shr") == 0) {

    } else if (strcmp(inst_str, "jmp") == 0) {

    } else if (strcmp(inst_str, "jrz") == 0) {

    } else {
        condition.state = UNKNOWN_INSTRUCTION;
    }
}

static Condition parse_instructions(FILE *source, FILE *destination) {
    Condition condition;
    condition.state = OK;
    size_t line_number = 0;
    instruction inst;

    do {
        line_number++;
        int buf[2] = {};
        condition = get_instruction_and_arguments(source, &inst, buf);

        if (condition.state != OK) {
            condition.int_info = line_number;
            break;
        }

    } while (inst != eof);

    return condition;
}

Condition build(int argc, char **argv) {
    char *source_path, *destination_path;
    FILE *source, *destination;
    Condition condition;

    if ((condition =
             get_build_paths(argc, argv, &source_path, &destination_path))
                .state != OK ||
        (condition =
             open_files(source_path, destination_path, &source, &destination))
                .state != OK ||
        (condition = parse_instructions(source, destination)).state != OK ||
        (condition = close_files(source, destination)).state != OK) {
    }

    return condition;
}
