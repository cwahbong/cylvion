#ifndef CYLVION_HAND_H
#define CYLVION_HAND_H

#include <stdlib.h>

#include "cylvion/error.h"

typedef struct cyl_hand cyl_hand;
typedef struct cyl_card cyl_card;

cyl_hand *
cyl_hand_new(size_t size);
void
cyl_hand_free(cyl_hand * p_hand);

cyl_error
cyl_hand_get_count(cyl_hand * p_hand, size_t * p_count);
cyl_error
cyl_hand_get_size(cyl_hand * p_hand, size_t * p_size);

cyl_error
cyl_hand_add_card(cyl_hand * p_hand, cyl_card * p_card);
cyl_error
cyl_hand_get_card(cyl_hand * p_hand, size_t nth, cyl_card ** pp_card);
cyl_error
cyl_hand_remove_card(cyl_hand * hand, size_t nth);

#endif /* CYLVION_HAND_H */
