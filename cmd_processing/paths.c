#include "../paths.h"

void get_build_paths(Condition *condition, int argc, char **argv,
                     char **source_path, char **destination_path) {
    if (condition->state != OK) {
        return;
    }

    if (argc < 3) {
        condition->state = NO_SOURCE_PATH;
        return;
    }

    *source_path = argv[2];

    if (argc > 3) {
        *destination_path = argv[3];
    } else {
        *destination_path = "a.out";
    }
}

void get_interpret_path(Condition* condition, int argc, char** argv, char** source_path){

}