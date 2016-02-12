#include <stdlib.h>

#include "cylvion/card.h"

#include "cylvion/hand.h"


struct cyl_card {
    int cost;
    int strength;
    int vitality;
    int on_field;
    cyl_error (*on_before_move)(cyl_content * p_content);
    cyl_error (*on_effect)(cyl_content * p_content);
};

cyl_error
cyl_card_fountain_on_effect(cyl_content * p_content)
{
    /* TODO */
    return CYL_ERR;
}

cyl_card *
cyl_card_new_fountain(int cost, int strength)
{
    cyl_card * p_card = malloc(sizeof(cyl_card));
    if (p_card == NULL) {
        return NULL;
    }
    p_card->cost = cost;
    p_card->strength = strength;
    p_card->vitality = 0;
    p_card->on_field = 1;
    p_card->on_before_move = NULL;
    p_card->on_effect = cyl_card_fountain_on_effect;
    return p_card;
}

cyl_error
cyl_card_tree_on_effect(cyl_content * p_content)
{
    /* TODO*/
    return CYL_ERR;
}

cyl_card *
cyl_card_new_tree(int cost, int vitality)
{
    cyl_card * p_card = malloc(sizeof(cyl_card));
    if (p_card == NULL) {
        return NULL;
    }
    p_card->cost = cost;
    p_card->strength = 0;
    p_card->vitality = vitality;
    p_card->on_field = 1;
    p_card->on_before_move = NULL;
    p_card->on_effect = cyl_card_fountain_on_effect;
    return p_card;
}

cyl_card *
cyl_card_new_elemental(int strength)
{
    cyl_card * p_card = malloc(sizeof(cyl_card));
    if (p_card == NULL) {
        return NULL;
    }
    p_card->strength = strength;
    p_card->vitality = 0;
    p_card->on_field = 1;
    p_card->on_before_move = NULL;
    p_card->on_effect = NULL;
    return p_card;
}

void
cyl_card_free(cyl_card * p_card)
{
    free(p_card);
}

cyl_error
cyl_card_on_before_move(const cyl_card * p_card, cyl_content * p_content)
{
    if (p_card == NULL) {
        return CYL_BAD_PARAM;
    }
    if (p_card->on_before_move == NULL) {
        return CYL_OK;
    }
    return p_card->on_before_move(p_content);
}

cyl_error
cyl_card_on_use(const cyl_card * p_card, cyl_content * p_content)
{
    if (p_card == NULL) {
        return CYL_BAD_PARAM;
    }

    int mana = 0;
    if (cyl_content_get_mana(p_content, &mana) != CYL_OK) {
        return CYL_ERR;
    }
    if (mana < p_card->cost) {
        return CYL_BAD_STATE;
    }
    mana -= p_card->cost;

    if (p_card->on_effect == NULL) {
        return CYL_OK;
    }
    return p_card->on_effect(p_content);
}

