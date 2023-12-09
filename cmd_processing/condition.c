#include "../condition.h"

#include "../help.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_contain(char *str, char c) {
    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (str[i] == c) {
            return true;
        }
    }

    return false;
}

void react_on_condition(Condition condition) {
    switch (condition.state) {
    case NO_SOURCE_PATH:
        printf("No source path was given.\n");
        break;
    case NO_FILE_FOUND:
        printf("The file with the path \"%s\" not found.\n",
               condition.str_info);
        break;
    case NO_MODE:
        printf("No mode was given.\n");
        break;
    case BAD_DESTINATION_PATH:
        printf("Can't open \"%s\" for writing.\n", condition.str_info);
        break;
    case UNKNOWN_INSTRUCTION:
        printf("Unknown instruction \"%s\" in line %lu.\n", condition.str_info,
               condition.int_info);
        free(condition.str_info);
        break;
    case ERROR_WHEN_CLOSING:
        printf("Error when closing the files\n");
        break;
    case ERROR_WHEN_WRITING:
        printf("Error when writing to the destination file\n");
        break;
    case ERROR_WHEN_READING:
        printf("Error when reading from source file\n");
        break;
    case UNKNOWN_MODE:
        printf("Unknown mode \"%s\".\n", condition.str_info);
        break;
    case INVALID_ARGUMENTS_FOR_INSTRUCTION:
        printf("Invalid arguments in line %lu:\n%s", condition.int_info,
               condition.str_info);

        if (!is_contain(condition.str_info, '\n')) {
            printf("\n");
        }

        free(condition.str_info);
        break;
    case INVALID_MEMORY_ACCESS:
        printf("Invalid memory access while executing\n");
        break;
    case JMP_ERROR:
        printf("Printing jmp error...\n");
    default:
        break;
    }
}