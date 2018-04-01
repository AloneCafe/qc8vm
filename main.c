#include "kernel.h"


int main(int argc, char **argv) {

    if (init(argv) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    quit();

    return 0;
}