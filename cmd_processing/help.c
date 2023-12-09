#include "../help.h"
#include <stdio.h>

void print_help() {
    printf(
        "This is the 8-bit virtual machine\nAvailable commands:\n1)help - "
        "prints this help\n2)build <SOURCE_PATH> <DESTINATION_PATH> - compiles "
        "special assembly\n   code in a new binary at DESTINATION_PATH or by "
        "default at \"a.out\"\n3)run <SOURCE_PATH> - executes the resulting "
        "binary file\n");
}
