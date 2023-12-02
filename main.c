#include "builder.h"
#include "interpretator.h"
#include "print.h"
#include "vm_condition.h"
#include "vm_mode.h"

int main(int argc, char **argv) {
    vm_mode mode = get_mode(argv);
    vm_condition condition = OK;

    switch (mode) {
    case BUILD:
        condition = build(argc, argv);
        break;
    case RUN:
        condition = interpret(argv);
        break;
    case UNKNOWN:
        print_unknown_mode(argv);
    default:
        print_help();
        break;
    }

    react_on_condition(condition);
}