#pragma once

#include <stddef.h>

typedef enum {
    OK,
    NO_SOURCE_PATH,
    NO_FILE_FOUND,
    NO_MODE,
    BAD_DESTINATION_PATH,
    UNKNOWN_INSTRUCTION,
    ERROR_WHEN_CLOSING,
    ERROR_WHEN_WRITING,
    ERROR_WHEN_READING,
    UNKNOWN_MODE,
    INVALID_ARGUMENTS_FOR_INSTRUCTION,
    JMP_ERROR,
} State;

typedef struct Condition {
    State state;
    char *str_info;
    size_t int_info;
} Condition;

void react_on_condition(Condition condition);