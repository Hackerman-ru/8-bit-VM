#include "../mode.h"
#include <string.h>

Mode get_mode(Condition *condition, int argc, char **argv) {
    if (argc < 2) {
        condition->state = NO_MODE;
        return EMPTY;
    }

    char *str = argv[1];
    Mode mode = UNKNOWN;

    if (strcmp(str, "build") == 0) {
        mode = BUILD;
    } else if (strcmp(str, "run") == 0) {
        mode = RUN;
    } else if (strcmp(str, "help") == 0) {
        mode = HELP;
    } else {
        condition->state = UNKNOWN_MODE;
        condition->str_info = str;
    }

    return mode;
}