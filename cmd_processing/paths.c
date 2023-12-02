#include "../paths.h"

vm_condition get_build_paths(int argc, char **argv, char **file_path,
                             char **bin_path) {
    if (argc < 3) {
        return NO_SOURCE_PATH;
    }

    *file_path = argv[2];

    if (argc > 3) {
        *bin_path = argv[3];
    } else {
        *bin_path = "a.out";
    }

    return OK;
}