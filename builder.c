#include "builder.h"
#include "instructions.h"
#include "paths.h"
#include "print.h"
#include "vm_condition.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

static vm_condition open_files(char *source_path, char *destination_path,
                               FILE **source_file, FILE **destination_file) {
    if ((*source_file = fopen(source_path, "r")) == NULL) {
        return NO_FILE_FOUND;
    }

    if ((*destination_file = fopen(destination_path, "wb")) == NULL) {
        return BAD_DESTINATION_PATH;
    }

    return OK;
}

static instruction get_instruction_and_arguments(FILE *source,
                                                 instruction *inst, int *buf) {
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
        print_unknown_instruction(inst_str);
        return unknown;
    }
}

static vm_condition parse_instructions(FILE *source, FILE *destination) {
    instruction inst;
    vm_condition condition;
    size_t line_number = 0;

    do {
        line_number++;
        int buf[2] = {};
        get_instruction_and_arguments(source, &inst, buf);

        if (inst == unknown) {
            print_line_of_unknown_instruction(line_number);
            condition = UKNOWN_INSTRUCTION;
            break;
        }

    } while (inst != eof);

    return condition;
}

vm_condition build(int argc, char **argv) {
    char *source_path, *destination_path;
    vm_condition condition;

    if ((condition = get_build_paths(argc, argv, &source_path,
                                     &destination_path)) != OK) {
        return condition;
    }

    FILE *source, *destination;

    if ((condition = open_files(source_path, destination_path, &source,
                                &destination)) != OK) {
        return condition;
    }

    return parse_instructions(source, destination);
}
