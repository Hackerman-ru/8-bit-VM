#pragma once

#include "../condition.h"
#include <stdio.h>

void open_file(Condition *condition, char **argv, FILE **file);
void close_file(Condition *condition, FILE *file);