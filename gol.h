#ifndef _GOL_H
#define _GOL_H

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

#define GOL_BOARD_L (40U)
#define GOL_BOARD_C (100U)

typedef unsigned char gol_cell;
typedef gol_cell gol_board[GOL_BOARD_L][GOL_BOARD_C];

enum gol_state {
    GOL_STATE_DEAD  = 0,
    GOL_STATE_ALIVE = 1,
    GOL_STATE_INVALID = 2,
};

/**
 * @brief Iterate @a N times on @a board
 * @param board The board to iterate over
 * @param neighbours A temporary board to keep neighbours count
 * @param L Number of lines @a board and @a neighbours have
 * @param C Number of columns @a board and @a neighbours have
 * @param N Number of times to iterate over @a board
 */
void gol_iterate (gol_board board, gol_board neighbours, unsigned int L, unsigned int C, unsigned int N);

/**
 * @brief Randomize @a board
 * @param board The board to randomize
 * @param L Number of lines @a board has
 * @param C Number of columns @a board has
 */
void gol_random  (gol_board board, unsigned int L, unsigned int C);

/**
 * @brief Print @a board
 * @param board The board to print
 * @param L Number of lines @a board has
 * @param C Number of columns @a board has
 */
void gol_print (gol_board board, unsigned int L, unsigned int C);

#endif /* _GOL_H */
