#pragma once

#include "condition.h"

void get_build_paths(Condition *condition, int argc, char **argv,
                     char **source_path, char **destination_path);
void get_interpret_path(Condition *condition, int argc, char **argv,
                        char **source_path);