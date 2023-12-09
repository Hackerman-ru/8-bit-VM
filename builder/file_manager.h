#pragma once

#include "../condition.h"

#include <stdint.h>
#include <stdio.h>

void open_files(Condition *condition, char *source_path, char *destination_path,
                FILE **source_file, FILE **destination_file);
void close_files(Condition *condition, FILE *source_file,
                 FILE *destination_file);
void write_command(Condition *condition, uint8_t *buff, FILE *destination);