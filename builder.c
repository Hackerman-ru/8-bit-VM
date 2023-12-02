#include "builder.h"
#include "paths.h"

vm_condition build(int argc, char **argv) {
    char *file_path, *bin_path;
    vm_condition codition = get_build_paths(argc, argv, &file_path, &bin_path);

    if (codition != OK) {
        return codition;
    }

    return OK;
}