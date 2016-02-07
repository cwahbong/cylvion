#include <stdlib.h>

#include "cylvion/defender.h"

typedef struct cyl_card cyl_card;

struct cyl_defender {
    cyl_card ** pp_undrawn;
    int undrawn_count;
    cyl_card ** pp_discarded;
    int discarded_count;
    int size;
};

cyl_defender *
cyl_defender_new(int size)
{
    cyl_defender * p_defender = calloc(1, sizeof(cyl_defender));
    if (p_defender == NULL) {
        return NULL;
    }
    p_defender->pp_undrawn = calloc(size, sizeof(cyl_card *));
    if (p_defender->pp_undrawn == NULL) {
        cyl_defender_free(p_defender);
        return NULL;
    }
    p_defender->undrawn_count = 0;
    p_defender->pp_discarded = calloc(size, sizeof(cyl_card *));
    if (p_defender->pp_discarded == NULL) {
        cyl_defender_free(p_defender);
        return NULL;
    }
    p_defender->discarded_count = 0;
    p_defender->size = size;
    return p_defender;
}

void
cyl_defender_free(cyl_defender * p_defender)
{
    if (p_defender == NULL) {
        return;
    }
    if (p_defender->pp_undrawn != NULL) {
        free(p_defender->pp_undrawn);
    }
    if (p_defender->pp_discarded != NULL) {
        free(p_defender->pp_discarded);
    }
    free(p_defender);
}

int
cyl_defender_shuffle(cyl_defender * p_defender)
{
}

int
cyl_defender_draw(cyl_defender * p_defender, cyl_card ** pp_card)
{
    if (p_defender == NULL) {
        return CYL_BAD_PARAM;
    }
    if (p_defender->undrawn_count <= 0) {
        return CYL_BAD_STATE;
    }
    *pp_card = p_defender->pp_undrawn[p_defender->undrawn_count--];
    return CYL_OK;
}

int
cyl_defender_discard(cyl_defender *p_defender, cyl_card * p_card)
{
}
