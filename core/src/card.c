#include "cylvion/card.h"

#include <stdlib.h>

struct cyl_card {
    int strength;
};

void
cyl_card_free(cyl_card * p_card)
{
    free(p_card);
}

