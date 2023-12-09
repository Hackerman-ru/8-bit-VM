#include "file_manager.h"

void open_file(Condition *condition, char *source_path, FILE **file) {
    if (condition->state != OK) {
        return;
    }

    if ((*file = fopen(source_path, "rb")) == NULL) {
        condition->state = NO_FILE_FOUND;
        condition->str_info = source_path;
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