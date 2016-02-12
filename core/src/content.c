#include "cylvion/content.h"

#include "cylvion/card.h"
#include "cylvion/field.h"
#include "cylvion/hand.h"
#include "cylvion/log.h"
#include "cylvion/stack.h"

struct cyl_content {
    int edge;
    int mana;
    cyl_field * p_field;
    cyl_hand * p_hand;
    cyl_stack * p_discarded;
    cyl_stack * p_undrawn;
    cyl_stack * p_cards;
};

cyl_content *
cyl_content_new(size_t card_num)
{
    cyl_content * p_content = calloc(1, sizeof(cyl_content));
    if (p_content == NULL) {
        cyl_content_free(p_content);
        return NULL;
    }
    if ((p_content->p_field = cyl_field_new()) == NULL) {
        cyl_content_free(p_content);
        return NULL;
    }
    if ((p_content->p_hand = cyl_hand_new(10)) == NULL) {
        cyl_content_free(p_content);
        return NULL;
    }
    if ((p_content->p_discarded = cyl_stack_new(card_num)) == NULL) {
        cyl_content_free(p_content);
        return NULL;
    }
    if ((p_content->p_undrawn = cyl_stack_new(card_num)) == NULL) {
        cyl_content_free(p_content);
        return NULL;
    }
    if ((p_content->p_cards = cyl_stack_new(card_num)) == NULL) {
        cyl_content_free(p_content);
        return NULL;
    }
    return p_content;
}

void
cyl_content_free(cyl_content * p_content)
{
    if (p_content == NULL) {
        return;
    }
    cyl_field_free(p_content->p_field);
    cyl_hand_free(p_content->p_hand);
    cyl_stack_free(p_content->p_discarded);
    cyl_stack_free(p_content->p_undrawn);
    cyl_card * p_card = NULL;
    while ((p_card = cyl_stack_get_top(p_content->p_cards)) != NULL) {
        cyl_card_free(p_card);
        if (cyl_stack_pop(p_content->p_cards) != CYL_OK) {
            cyl_log_warn("Failed to free cards since pop failed.");
        }
    }
    cyl_stack_free(p_content->p_cards);
    free(p_content);
}

cyl_error
cyl_content_manage_card(cyl_content * p_content, cyl_card * p_card)
{
    if (p_content == NULL || p_card == NULL) {
        cyl_log_error("null ptr");
        return CYL_BAD_PARAM;
    }

    if (cyl_stack_push(p_content->p_cards, p_card) != CYL_OK) {
        cyl_log_error("push_failed");
        return CYL_ERR;
    }

    return CYL_OK;
}

unsigned
cyl_content_get_edge(cyl_content * p_content)
{
    return p_content->edge;
}

cyl_error
cyl_content_set_edge(cyl_content * p_content, unsigned edge)
{
    if (p_content == NULL) {
        return CYL_BAD_PARAM;
    }
    p_content->edge = edge;
    return CYL_OK;
}

unsigned
cyl_content_get_mana(cyl_content * p_content)
{
    return p_content->mana;
}

cyl_error
cyl_content_set_mana(cyl_content * p_content, unsigned mana)
{
    if (p_content == NULL) {
        return CYL_BAD_PARAM;
    }
    p_content->mana = mana;
    return CYL_OK;
}

cyl_field *
cyl_content_get_field(cyl_content * p_content)
{
    return p_content ? p_content->p_field : NULL;
}

cyl_hand *
cyl_content_get_hand(cyl_content * p_content)
{
    return p_content ? p_content->p_hand : NULL;
}

cyl_stack *
cyl_content_get_discarded(cyl_content *p_content)
{
    return p_content ? p_content->p_discarded : NULL;
}

cyl_stack *
cyl_content_get_undrawn(cyl_content *p_content)
{
    return p_content ? p_content->p_undrawn : NULL;
}
