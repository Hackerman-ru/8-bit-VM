#include "builder.h"
#include "condition.h"
#include "help.h"
#include "interpretator.h"
#include "mode.h"

int main(int argc, char **argv) {
    Condition condition;
    Mode mode = get_mode(&condition, argc, argv);

    switch (mode) {
    case BUILD:
        condition = build(argc, argv);
        break;
    case RUN:
        condition = interpret(argc, argv);
        break;
    case HELP:
        print_help();
        break;
    default:
        break;
    }

    react_on_condition(condition);
}