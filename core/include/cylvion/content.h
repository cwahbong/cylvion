#ifndef CYLVION_CONTENT_H
#define CYLVION_CONTENT_H

#include <stdlib.h>

#include "cylvion/error.h"

typedef struct cyl_card cyl_card;
typedef struct cyl_field cyl_field;
typedef struct cyl_stack cyl_stack;
typedef struct cyl_hand cyl_hand;
typedef struct cyl_content cyl_content;

cyl_content *
cyl_content_new(size_t card_num);
void
cyl_content_free(cyl_content *);

cyl_error
cyl_content_manage_card(cyl_content * p_content, cyl_card * p_card);

unsigned
cyl_content_get_edge(cyl_content * p_content);
cyl_error
cyl_content_set_edge(cyl_content * p_content, unsigned edge);

unsigned
cyl_content_get_mana(cyl_content * p_content);
cyl_error
cyl_content_set_mana(cyl_content * p_content, unsigned mana);

cyl_field *
cyl_content_get_field(cyl_content * p_content);
cyl_hand *
cyl_content_get_hand(cyl_content * p_content);
cyl_stack *
cyl_content_get_discarded(cyl_content * p_content);
cyl_stack *
cyl_content_get_undrawn(cyl_content * p_content);

#endif /* CYLVION_CONTENT_H */
