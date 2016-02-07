#ifndef CYLVION_CARD_H
#define CYLVION_CARD_H

typedef struct cyl_card cyl_card;

cyl_card * cyl_card_make_fountain();
cyl_card * cyl_card_make_tree();
cyl_card * cyl_card_make_animal();
cyl_card * cyl_card_make_elemental();
cyl_card * cyl_card_make_support();
void cyl_card_free(cyl_card * p_card);

int cyl_card_get_strength(cyl_card * p_card, int * strength);

#endif /* CYLVION_CARD_H */
