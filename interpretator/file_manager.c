#include "file_manager.h"

void open_file(Condition *condition, char **argv, FILE **file) {
    if (condition->state != OK) {
        return;
    }

    if ((*file = fopen(argv[1], "rb")) == NULL) {
        condition->state = NO_FILE_FOUND;
        condition->str_info = argv[1];
    }
}

void close_file(Condition *condition, FILE *file) {
    if (condition->state != OK) {
        return;
    }

    if (fclose(file) != 0) {
        condition->state = ERROR_WHEN_CLOSING;
    }
}