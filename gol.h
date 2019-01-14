#ifndef _GOL_H
#define _GOL_H

#define VEC_CFG_DATA_TYPE unsigned char
#include <utils/vec.h>
#include <utils/bs.h>

#include <stdio.h>

struct gol {
    struct bs  current[1];
    struct bs  next[1];
    struct vec neighbours[1];
    unsigned   nlines;
    unsigned   ncols;
};

bool gol_cell_kill   (struct gol * self, unsigned l, unsigned c);
bool gol_cell_revive (struct gol * self, unsigned l, unsigned c);
bool gol_cell_set    (struct gol * self, unsigned l, unsigned c, bool val);
bool gol_eprint      (struct gol * self);
bool gol_fprint      (struct gol * self, FILE * outf);
bool gol_free        (struct gol * self);
bool gol_iter        (struct gol * self, unsigned niter);
bool gol_new         (struct gol * self, unsigned nlines, unsigned ncols);
bool gol_next        (struct gol * self);
bool gol_print       (struct gol * self);
bool gol_random      (struct gol * self);
bool gol_set_board   (struct gol * self, unsigned ol, unsigned oc, unsigned L, unsigned C, const bool board[L][C]);

#endif /* _GOL_H */
