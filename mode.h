#pragma once

#include "condition.h"

typedef enum {
    HELP,
    BUILD,
    RUN,
    EMPTY,
    UNKNOWN,
} Mode;

Mode get_mode(Condition *condition, int argc, char **argv);