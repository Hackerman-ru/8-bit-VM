#pragma once

typedef enum {
    OK,
    NO_SOURCE_PATH,
    ERROR_WHEN_RUN,
    UNKNOWN_ERROR,
} vm_condition;

void react_on_condition(vm_condition condition);