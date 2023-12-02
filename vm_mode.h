#pragma once

typedef enum {
    HELP,
    BUILD,
    RUN,
    UNKNOWN,
} vm_mode;

vm_mode get_mode(char **argv);