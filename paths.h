#pragma once

#include "vm_condition.h"

vm_condition get_build_paths(int argc, char **argv, char **file_path,
                             char **bin_path);