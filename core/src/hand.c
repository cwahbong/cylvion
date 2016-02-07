#include "cylvion/hand.h"

struct cyl_hand {
    cyl_card ** pp_cards;
    size_t count;
    size_t size;
};

cyl_hand *
cyl_hand_new(size_t size)
{
    cyl_hand * p_hand = malloc(sizeof(cyl_hand));
    if (p_hand == NULL) {
        return NULL;
    }
    if ((p_hand->pp_cards = calloc(size, sizeof(cyl_card *))) == NULL) {
        free(p_hand);
        return NULL;
    }
    p_hand->count = 0;
    p_hand->size = size;
    return p_hand;
}

void
cyl_hand_free(cyl_hand * p_hand)
{
    if (p_hand == NULL) {
        return;
    }
    if (p_hand->pp_cards != NULL) {
        free(p_hand->pp_cards);
    }
    free(p_hand);
}

cyl_error
cyl_hand_get_count(cyl_hand * p_hand, size_t * p_count)
{
    if (p_hand == NULL || p_count == NULL) {
        return CYL_BAD_PARAM;
    }

    *p_count = p_hand->count;
    return CYL_OK;
}

cyl_error
cyl_hand_get_size(cyl_hand * p_hand, size_t * p_size)
{
    if (p_hand == NULL || p_size == NULL) {
        return CYL_BAD_PARAM;
    }

    *p_size = p_hand->size;
    return CYL_OK;
}

cyl_error
cyl_hand_add_card(cyl_hand * p_hand, cyl_card * p_card)
{
    if (p_hand == NULL || p_card == NULL) {
        return CYL_BAD_PARAM;
    }
    if (p_hand->count >= p_hand->size) {
        return CYL_BAD_STATE;
    }
    p_hand->pp_cards[p_hand->count++] = p_card;
    return CYL_OK;
}

cyl_error
cyl_hand_get_card(cyl_hand * p_hand, size_t nth, cyl_card ** pp_card)
{
    if (p_hand == NULL || pp_card == NULL) {
        return CYL_BAD_PARAM;
    }
    if (nth >= p_hand->count) {
        return CYL_BAD_PARAM;
    }
    *pp_card = p_hand->pp_cards[nth];
    return CYL_OK;
}

cyl_error
cyl_hand_remove_card(cyl_hand * p_hand, size_t nth)
{
    if (p_hand == NULL) {
        return CYL_BAD_PARAM;
    }
    if (nth >= p_hand->count) {
        return CYL_BAD_PARAM;
    }
    p_hand->pp_cards[nth] = p_hand->pp_cards[p_hand->count - 1];
    p_hand->count -= 1;
    return CYL_OK;
}
