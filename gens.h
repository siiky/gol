#include "gol.h"

#define MAP_CFG_MAP gens
#define MAP_CFG_PREFIX gens__
#define MAP_CFG_KEY_DATA_TYPE struct bs *
#define MAP_CFG_VALUE_DATA_TYPE char
#include <utils/map.h>

bool gens_add       (struct gens * self, struct gol * gol);
bool gens_contains  (struct gens * self, struct gol * gol);
bool gens_free      (struct gens * self);
bool gens_with_size (struct gens * self, unsigned int size);
