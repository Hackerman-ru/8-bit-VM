#pragma once

#include <stddef.h>

typedef enum {
    OK,
    NO_SOURCE_PATH,
    NO_FILE_FOUND,
    BAD_DESTINATION_PATH,
    UNKNOWN_INSTRUCTION,
    ERROR_WHEN_RUN,
    ERROR_WHEN_CLOSING,
    UNKNOWN_ERROR,
} State;

typedef struct Condition {
    State state;
    char *str_info;
    size_t int_info;
} Condition;

void react_on_condition(Condition condition);