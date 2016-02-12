#include <stdlib.h>

#include "cylvion/card.h"
#include "cylvion/content.h"
#include "cylvion/field.h"
#include "cylvion/hand.h"


struct cyl_card {
    int cost;
    int strength;
    int vitality;
    int on_field;
    cyl_error (*on_before_move)(cyl_card * p_this, cyl_content * p_content, cyl_actor actor);
    cyl_error (*on_effect)(cyl_card * p_this, cyl_content * p_content, cyl_actor actor);
};

static cyl_error
cyl_card_field_put_effect(cyl_card * p_this, cyl_content * p_content, cyl_actor actor, cyl_question question)
{
    if (actor.fn_question == NULL) {
        return CYL_ERR;
    }
    cyl_location_answer answer;
    if (actor.fn_question(p_content, question, actor.data, &answer) != CYL_OK) {
        return CYL_ERR;
    }
    if (answer.row >= CYL_FIELD_ROW_SIZE || answer.col >= CYL_FIELD_COL_SIZE) {
        return CYL_BAD_STATE;
    }
    cyl_field * p_field = cyl_content_get_field(p_content);
    if (p_field == NULL) {
        return CYL_ERR;
    }
    if (cyl_field_put_card(p_field, answer.row, answer.col, p_this) != CYL_OK) {
        return CYL_ERR;
    }
    return CYL_OK;
}

static cyl_error
cyl_card_fountain_on_effect(cyl_card * p_this, cyl_content * p_content, cyl_actor actor)
{
    return cyl_card_field_put_effect(p_this, p_content, actor, CYL_QUES_LOCATION_FOUNTAIN);
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

static cyl_error
cyl_card_tree_on_effect(cyl_card * p_this, cyl_content * p_content, cyl_actor actor)
{
    return cyl_card_field_put_effect(p_this, p_content, actor, CYL_QUES_LOCATION_TREE);
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
    p_card->on_effect = cyl_card_tree_on_effect;
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

int
cyl_card_get_cost(const cyl_card * p_card)
{
    return p_card->cost;
}

int
cyl_card_get_strength(const cyl_card * p_card)
{
    return p_card->strength;
}

int
cyl_card_get_vitality(const cyl_card * p_card)
{
    return p_card->vitality;
}

int
cyl_card_is_cylvan(const cyl_card * p_card)
{
    return 0;
}

int
cyl_card_is_ravage(const cyl_card * p_card)
{
    return 0;
}

cyl_error
cyl_card_on_before_move(cyl_card * p_card, cyl_content * p_content, cyl_actor actor)
{
    if (p_card == NULL) {
        return CYL_BAD_PARAM;
    }
    if (p_card->on_before_move == NULL) {
        return CYL_OK;
    }
    return p_card->on_before_move(p_card, p_content, actor);
}

cyl_error
cyl_card_on_use(cyl_card * p_card, cyl_content * p_content, cyl_actor actor)
{
    if (p_card == NULL) {
        return CYL_BAD_PARAM;
    }

    int mana = cyl_content_get_mana(p_content);
    if (mana < p_card->cost) {
        return CYL_BAD_STATE;
    }
    mana -= p_card->cost;
    if (cyl_content_set_mana(p_content, mana) != CYL_OK) {
        return CYL_ERR;
    }

    if (p_card->on_effect == NULL) {
        return CYL_OK;
    }
    return p_card->on_effect(p_card, p_content, actor);
}

