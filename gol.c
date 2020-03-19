#include "gol.h"

#include <utils/common.h>
#include <utils/ifjmp.h>

#include <stdlib.h>

#define gol_coord2idx(gol, l, c) (((l) * (gol)->ncols) + (c))

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
static inline bool _gol_cell_fate (bool cell, unsigned char neighbours)
{
    return (!cell && neighbours == 3) ? /* (4) */
        true:
        (cell && (neighbours < 2 || neighbours > 3)) ? /* (1) & (3) */
        false:
        cell; /* (2) */
}

static inline bool _gol_clean (struct gol * self)
{
    *self = (struct gol) {0};
    return true;
}

/*
 *      lc   uc
 *   ll  - - -
 *      | | | |
 *       - - -
 *      | |c| |
 *       - - -
 *      | | | |
 *   ul  - - -
 */
static inline unsigned char _gol_cell_neighbours (struct gol * self, unsigned l, unsigned c)
{
    unsigned lc = max(c, 1) - 1;
    unsigned ll = max(l, 1) - 1;
    unsigned uc = min(c, self->ncols  - 2) + 2;
    unsigned ul = min(l, self->nlines - 2) + 2;

    unsigned char ret = 0;

    for (unsigned i = ll; i < ul; i++)
        for (unsigned j = lc; j < uc; j++)
            if ((i != l || j != c) && bs_get(self->current, gol_coord2idx(self, i, j)))
                ret++;

    return ret;
}

bool gol_cell_get (struct gol * self, unsigned l, unsigned c)
{
    return self != NULL
        && bs_get(self->current, gol_coord2idx(self, l, c));
}

bool gol_cell_kill (struct gol * self, unsigned l, unsigned c)
{
    return gol_cell_set(self, l, c, false);
}

bool gol_cell_revive (struct gol * self, unsigned l, unsigned c)
{
    return gol_cell_set(self, l, c, true);
}

bool gol_cell_set (struct gol * self, unsigned l, unsigned c, bool val)
{
    return bs_set(self->current, gol_coord2idx(self, l, c), val);
}

bool gol_eprint (struct gol * self)
{
    return gol_fprint(self, stderr);
}

bool gol_fprint (struct gol * self, FILE * outf)
{
    if (self == NULL || outf == NULL)
        return false;
    for (unsigned i = 0; i < self->nlines; i++) {
        for (unsigned j = 0; j < self->ncols; j++)
            fputc(bs_get(self->current, gol_coord2idx(self, i, j)) ? '#' : '.', outf);
        fputc('\n', outf);
    }
    return true;
}

bool gol_free (struct gol * self)
{
    if (self != NULL) {
        bs_free(self->current);
        bs_free(self->next);
        _gol_clean(self);
    }
    return true;
}

bool gol_iter (struct gol * self, unsigned niter)
{
    if (self == NULL)
        return  false;
    bool ret = true;
    for (unsigned i = 0; ret && i < niter; i++)
        ret = gol_next(self);
    return ret;
}

bool gol_new (struct gol * self, unsigned nlines, unsigned ncols)
{
    unsigned ncells = nlines * ncols;
    return self != NULL
        && bs_init(self->current, ncells)
        && bs_init(self->next, ncells)
        && ((self->nlines = nlines), (self->ncols = ncols), true);
}

bool gol_next (struct gol * self)
{
    if (self == NULL)
        return false;

    for (unsigned i = 0; i < self->nlines; i++) {
        for (unsigned j = 0; j < self->ncols; j++) {
            unsigned idx = gol_coord2idx(self, i, j);
            bool cur = bs_get(self->current, idx);
            bool next = _gol_cell_fate(cur, _gol_cell_neighbours(self, i, j));
            bool res = bs_set(self->next, idx, next);
            if (!res)
                return false;
        }
    }

    /* dead end */
    if (bs_cmp(self->current, self->next) == 0)
        return false;

    void * tmp = self->current->bytes;
    self->current->bytes = self->next->bytes;
    self->next->bytes = tmp;

    return true;
}

bool gol_print (struct gol * self)
{
    return gol_fprint(self, stdout);
}

bool gol_random (struct gol * self)
{
    if (self == NULL)
        return false;

    for (unsigned i = 0; i < self->nlines; i++) {
        for (unsigned j = 0; j < self->ncols; j++) {
            unsigned idx = gol_coord2idx(self, i, j);
            bool alive = (rand() % 2);
            bool res = bs_set(self->current, idx, alive);
            if (!res)
                return false;
        }
    }

    return true;
}

bool gol_set_board (struct gol * self, unsigned ol, unsigned oc, unsigned L, unsigned C, const bool board[L][C])
{
    if (self == NULL || board == NULL)
        return false;
    bool ret = true;
    for (unsigned i = 0; ret && i < L; i++)
        for (unsigned j = 0; ret && j < C; j++)
            ret = gol_cell_set(self, ol + i, oc + j, board[i][j]);
    return ret;
}
