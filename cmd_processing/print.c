#include "../print.h"
#include <stdio.h>

void print_unknown_mode(char **argv) {
}

void print_unknown_instruction(char *str) {
    printf("Unknown instruction %s", str);
}

void print_line(size_t line_number) {
    printf(" in line %lu\n", line_number);
}

void print_help() {
}
