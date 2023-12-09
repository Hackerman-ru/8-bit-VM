#include "../builder.h"

#include "../condition.h"
#include "../paths.h"
#include "file_manager.h"
#include "instruction_parser.h"

Condition build(int argc, char **argv) {
    char *source_path, *destination_path;
    FILE *source_file, *destination_file;
    Condition condition;
    condition.state = OK;

    get_build_paths(&condition, argc, argv, &source_path, &destination_path);
    open_files(&condition, source_path, destination_path, &source_file,
               &destination_file);
    parse_instructions(&condition, source_file, destination_file);
    close_files(&condition, source_file, destination_file);

    return condition;
}
