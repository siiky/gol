#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gol.h"

int main (void)
{
    srand((unsigned int) time(NULL));

    gol_board board;
    gol_board neighbours;

    gol_random(board, GOL_BOARD_L, GOL_BOARD_C);
    gol_print(board, GOL_BOARD_L, GOL_BOARD_C);

    for (unsigned int i = 0; i < 100000; i++) {
        gol_iterate(board, neighbours, GOL_BOARD_L, GOL_BOARD_C, 1);
        puts("----------------------------------------------------------------------------------------------------");
        gol_print(board, GOL_BOARD_L, GOL_BOARD_C);
    }

    return 0;
}
