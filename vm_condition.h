#pragma once

typedef enum {
    OK,
    NO_SOURCE_PATH,
    NO_FILE_FOUND,
    BAD_DESTINATION_PATH,
    UKNOWN_INSTRUCTION,
    ERROR_WHEN_RUN,
    UNKNOWN_ERROR,
} vm_condition;

void react_on_condition(vm_condition condition);