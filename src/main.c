#define MEMORY_MAX_SIZE 67
#define FIND_ERRORS_BEFORE_EXECUTING 1

#include "brainfuck.h"


int main() {
    brainfuck_run_from_file("../brainfuck.bf");
    return 0;
}