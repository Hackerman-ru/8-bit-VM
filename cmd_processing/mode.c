#include "../vm_mode.h"
#include <string.h>

vm_mode get_mode(char **argv) {
    char *str = argv[1];
    vm_mode mode = UNKNOWN;

    if (strcmp(str, "build") == 0) {
        mode = BUILD;
    } else if (strcmp(str, "run") == 0) {
        mode = RUN;
    } else if (strcmp(str, "help") == 0) {
        mode = HELP;
    }

    return mode;
}