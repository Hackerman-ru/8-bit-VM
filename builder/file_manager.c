#include "file_manager.h"

void open_files(Condition *condition, char *source_path, char *destination_path,
                FILE **source_file, FILE **destination_file) {
    if (condition->state != OK) {
        return;
    }

    if ((*source_file = fopen(source_path, "r")) == NULL) {
        condition->state = NO_FILE_FOUND;
        condition->str_info = source_path;
    } else if ((*destination_file = fopen(destination_path, "wb")) == NULL) {
        condition->state = BAD_DESTINATION_PATH;
        condition->str_info = destination_path;
    }
}

void close_files(Condition *condition, FILE *source_file,
                 FILE *destination_file) {
    if (condition->state != OK) {
        return;
    }

    int source_res = fclose(source_file);
    int destination_res = fclose(destination_file);

    if (source_res != 0 || destination_res != 0) {
        condition->state = ERROR_WHEN_CLOSING;
    }
}

void write_command(Condition *condition, uint8_t *buff, FILE *destination) {
    if (condition->state != OK) {
        return;
    }

    if (fwrite(buff, sizeof(*buff), 3, destination) != 3) {
        condition->state = ERROR_WHEN_WRITING;
    }
}