#ifndef CYLVION_CARD_H
#define CYLVION_CARD_H

#include "cylvion/actor.h"
#include "cylvion/error.h"

typedef struct cyl_card cyl_card;
typedef struct cyl_content cyl_content;

cyl_card * cyl_card_new_fountain(int cost, int strength);
cyl_card * cyl_card_new_tree(int cost, int vitality);
cyl_card * cyl_card_new_animal(int cost); /* TODO */
cyl_card * cyl_card_new_elemental(int strength);
cyl_card * cyl_card_new_support(); /* TODO */
void cyl_card_free(cyl_card * p_card);


int cyl_card_is_cylvan(const cyl_card * p_card);
int cyl_card_is_ravage(const cyl_card * p_card);

cyl_error cyl_card_get_strength(const cyl_card * p_card, int * strength);

cyl_error
cyl_card_on_before_move(cyl_card * p_card, cyl_content * p_content, cyl_actor actor);
cyl_error
cyl_card_on_use(cyl_card * p_card, cyl_content * p_content, cyl_actor actor);

#endif /* CYLVION_CARD_H */
