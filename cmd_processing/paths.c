#include "../paths.h"

Condition get_build_paths(int argc, char **argv, char **file_path,
                          char **bin_path) {
    Condition condition;

    if (argc < 3) {
        condition.state = NO_SOURCE_PATH;
        return condition;
    }

    *file_path = argv[2];

    if (argc > 3) {
        *bin_path = argv[3];
    } else {
        *bin_path = "a.out";
    }

    condition.state = OK;
    return condition;
}