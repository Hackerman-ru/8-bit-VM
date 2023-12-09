#pragma once

#include "../condition.h"
#include <stdio.h>

void open_file(Condition *condition, char *source_path, FILE **file);
void close_file(Condition *condition, FILE *file);