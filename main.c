#include "gol.h"

#include <utils/ifjmp.h>

#include <stdlib.h>
#include <time.h>

int usage (const char * cmd)
{
    printf(
            "Usage:\n"
            "\t%s NLINES NCOLS\n"
            "Hit 'q' to quit, or any other character\n"
            "to see the following iteration\n",
            cmd);
    return EXIT_FAILURE;
}

static const bool glider[3][3] = {
    { 0, 0, 1 },
    { 1, 0, 1 },
    { 0, 1, 1 },
};

int main (int argc, char ** argv)
{
    ifjmp(argc < 3, usage);

    srand((unsigned int) time(NULL));

    struct gol gol[1] = {0};
    unsigned nlines = (unsigned) atoi(argv[1]);
    unsigned ncols = (unsigned) atoi(argv[2]);
    if (nlines >= 10 && ncols >= 10 && gol_new(gol, nlines, ncols)) {
        gol_set_board(gol, 0, 0, 3, 3, glider);

        do {
            gol_print(gol);
        } while (getc(stdin) != 'q' && gol_next(gol));

        gol_free(gol);
    }

    return EXIT_SUCCESS;

usage:
    return usage(argv[0]);
}
