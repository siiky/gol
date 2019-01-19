#include "gol.h"
#include "gens.h"

#include <raylib.h>
#include <utils/ifjmp.h>

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define GOL_RANDOM

#define NELEMS(arr) (sizeof(arr) / sizeof(*arr))

#define GOL_NLINES    100
#define GOL_NCOLS     100
#define CELL_ORIGIN_X 0
#define CELL_ORIGIN_Y 0
#define CELL_WIDTH    11
#define CELL_HEIGHT   11

#define TARGET_FPS 60
#define WIN_HEIGHT (GOL_NLINES * CELL_HEIGHT)
#define WIN_WIDTH  (GOL_NCOLS * CELL_WIDTH)

#ifndef GOL_RANDOM
static const bool glider[3][3] = {
    { 0, 0, 1 },
    { 1, 0, 1 },
    { 0, 1, 1 },
};
#endif

int main (void)
{
    bool should_iter = true;
    struct gol gol[1] = {0};
    struct gens gens[1] = {0};

    gens_with_size(gens, 1013);
    gol_new(gol, GOL_NLINES, GOL_NCOLS);

#ifdef GOL_RANDOM
    srand((unsigned) time(NULL));
    gol_random(gol);
#else
    gol_set_board(gol, 0, 0, NELEMS(glider), NELEMS(*glider), glider);
#endif

    SetExitKey(KEY_ESCAPE);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(TARGET_FPS);

    SetWindowMinSize(WIN_WIDTH, WIN_HEIGHT);
    SetWindowSize(WIN_WIDTH, WIN_HEIGHT);
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "wew lad"); {
        while (!WindowShouldClose()) {
            if (should_iter && !IsKeyDown(KEY_ENTER)) {
                /* Have we seen this iteration? */
                bool elem = gens_contains(gens, gol);

                /* If not, add it to the seen iterations */
                if (!elem)
                    gens_add(gens, gol);

                /* iterate once */
                should_iter = gol_iter(gol, 1)
                    && !elem;
            }

            BeginDrawing(); {
                ClearBackground(BLACK);

                for (unsigned i = 0; i < gol->nlines; i++) {
                    for (unsigned j = 0; j < gol->nlines; j++) {
                        Rectangle cell = {
                            .x = CELL_ORIGIN_X + j * CELL_WIDTH,
                            .y = CELL_ORIGIN_Y + i * CELL_HEIGHT,
                            .width = CELL_WIDTH,
                            .height = CELL_HEIGHT,
                        };

                        DrawRectangleRec(cell, gol_cell_get(gol, i, j) ? DARKGRAY : BLACK);
                    }
                }
                DrawRectangleLines(0, 0, WIN_WIDTH, WIN_HEIGHT, RAYWHITE);
            } EndDrawing();
        }
    } CloseWindow();

    gol_free(gol);
    gens_free(gens);

    return EXIT_SUCCESS;
}
