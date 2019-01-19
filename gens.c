#include <utils/bs.h>
#define MAP_CFG_KEY_DTOR bs_free
#define MAP_CFG_HASH_FUNC bs_hash
#define MAP_CFG_KEY_CMP bs_cmp
#define MAP_CFG_IMPLEMENTATION
#include "gens.h"

bool gens_add (struct gens * self, struct gol * gol)
{
    struct bs * clone = malloc(sizeof(struct bs));
    return clone != NULL
        && (bs_clone(gol->current, clone) || (free(clone), false))
        && gens__add(self, clone, 0);
}

inline bool gens_contains (struct gens * self, struct gol * gol)
{
    return gens__contains(self, gol->current);
}

inline bool gens_free (struct gens * self)
{
    *self = gens__free(*self);
    return true;
}

inline bool gens_with_size (struct gens * self, unsigned int size)
{
    return gens__with_size(self, size);
}
