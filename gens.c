#include <utils/bs.h>

#define MAP_CFG_HASH_FUNC(self)      (bs_hash(&(self)))
#define MAP_CFG_KEY_CMP(self, other) (bs_cmp(&(self), &(other)))
#define MAP_CFG_KEY_DTOR(self)       (bs_free(&(self)))
#define MAP_CFG_IMPLEMENTATION
#include "gens.h"

bool gens_add (struct gens * self, const struct gol * gol)
{
    struct bs clone = {0};
    return bs_clone(gol->current, &clone)
        && gens__add(self, clone, 0);
}

inline bool gens_contains (struct gens * self, const struct gol * gol)
{
    return gens__contains(self, *gol->current);
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
