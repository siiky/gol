#include <stdio.h>
#include <stdlib.h>

#include <utils/ifjmp.h>

#include "gol.h"

/*
 * 1. Any live cell with fewer than two live neighbours
 *     dies, as if caused by underpopulation.
 * 2. Any live cell with two or three live neighbours lives
 *     on to the next generation.
 * 3. Any live cell with more than three live neighbours
 *     dies, as if by overpopulation.
 * 4. Any dead cell with exactly three live neighbours
 *     becomes a live cell, as if by reproduction.
 */

static inline enum gol_state gol_fate (gol_cell cell, unsigned char neighbours)
{
    return
        (cell >= GOL_STATE_INVALID) ?
        GOL_STATE_DEAD :
        (cell == GOL_STATE_ALIVE && neighbours < 2) ?
        GOL_STATE_DEAD :
        (cell == GOL_STATE_ALIVE && (neighbours == 2 || neighbours == 3)) ?
        GOL_STATE_ALIVE :
        (cell == GOL_STATE_ALIVE && neighbours > 3) ?
        GOL_STATE_DEAD :
        (cell == GOL_STATE_DEAD && neighbours == 3) ?
        GOL_STATE_ALIVE :
        cell ;
}

static inline unsigned char gol_neighbours (const gol_board board, unsigned int BL, unsigned int BC, unsigned int CL, unsigned int CC)
{
    if (board == NULL)
        return 2; /* doesnt change state */

    /* doesnt work for boards with (BL < 2) or (BC < 2) */
    unsigned int ML = min(CL, BL - 2) + 2;
    unsigned int MC = min(CC, BC - 2) + 2;
    unsigned int ml = max(CL, 1) - 1;
    unsigned int mc = max(CC, 1) - 1;

    unsigned char neighbours = 0;

    for (unsigned int l = ml; l < ML; l++)
        for (unsigned int c = mc; c < MC; c++)
            if (l != CL && c != CC && board[l][c] == GOL_STATE_ALIVE)
                neighbours++;

    return neighbours;
}

void gol_iterate (gol_board board, gol_board neighbours, unsigned int L, unsigned int C, unsigned int N)
{
    if (board == NULL || neighbours == NULL)
        return;

    for (unsigned int n = 0; n < N; n++) {
        for (unsigned l = 0; l < L; l++)
            for (unsigned c = 0; c < C; c++)
                neighbours[l][c] = gol_neighbours(board, L, C, l, c);

        for (unsigned l = 0; l < L; l++)
            for (unsigned c = 0; c < C; c++)
                board[l][c] = gol_fate(board[l][c], neighbours[l][c]);
    }
}

void gol_random (gol_board board, unsigned int L, unsigned int C)
{
    if (board == NULL)
        return;

    for (unsigned l = 0; l < L; l++)
        for (unsigned c = 0; c < C; c++)
            board[l][c] = (unsigned char) (random() % 2);
}

void gol_print (gol_board board, unsigned int L, unsigned int C)
{
    if (board == NULL)
        return;

    //putchar(' ');
    //putchar(' ');
    //for (unsigned c = 0; c < C; c++)
    //    printf("%X", c);
    //putchar('\n');

    for (unsigned l = 0; l < L; l++) {
        //printf("%X ", l);

        for (unsigned c = 0; c < C; c++)
            putchar((board[l][c] == GOL_STATE_ALIVE) ?
                    'X' :
                    (board[l][c] == GOL_STATE_DEAD) ?
                    ' ' :
                    '?'
                   );

        putchar('\n');
    }
}
