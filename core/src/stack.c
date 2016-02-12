#include <stdlib.h>
#include <time.h>

#include "cylvion/log.h"
#include "cylvion/stack.h"

struct cyl_stack {
    cyl_card ** pp_cards;
    size_t count;
    size_t size;
};

cyl_stack *
cyl_stack_new(size_t size)
{
    cyl_stack * p_stack = malloc(sizeof(cyl_stack));
    if (p_stack == NULL) {
        return NULL;
    }
    p_stack->pp_cards = calloc(size, sizeof(cyl_card *));
    if (p_stack->pp_cards == NULL) {
        cyl_stack_free(p_stack);
        return NULL;
    }
    p_stack->count = 0;
    p_stack->size = size;
    return p_stack;
}

void
cyl_stack_free(cyl_stack * p_stack)
{
    if (p_stack == NULL) {
        return;
    }
    if (p_stack->pp_cards != NULL) {
        free(p_stack->pp_cards);
    }
    free(p_stack);
}

cyl_error
cyl_stack_count(cyl_stack * p_stack, size_t * p_count)
{
    if (p_stack == NULL || p_count == NULL) {
        return CYL_BAD_PARAM;
    }

    *p_count = p_stack->count;
    return CYL_OK;
}

cyl_error
cyl_stack_size(cyl_stack * p_stack, size_t * p_size)
{
    if (p_stack == NULL || p_size == NULL) {
        return CYL_BAD_PARAM;
    }

    *p_size = p_stack->size;
    return CYL_OK;
}

cyl_error
cyl_stack_push(cyl_stack * p_stack, cyl_card * p_card)
{
    if (p_stack == NULL || p_card == NULL) {
        cyl_log_error("null ptr");
        return CYL_BAD_PARAM;
    }
    if (p_stack->count >= p_stack->size) {
        cyl_log_error("count >= size");
        return CYL_BAD_STATE;
    }

    p_stack->pp_cards[p_stack->count++] = p_card;
    return CYL_OK;
}

cyl_error
cyl_stack_pop(cyl_stack * p_stack)
{
    if (p_stack == NULL) {
        return CYL_BAD_PARAM;
    }
    if (p_stack->count <= 0) {
        return CYL_BAD_STATE;
    }

    p_stack->count--;
    return CYL_OK;
}

cyl_error
cyl_stack_top(cyl_stack * p_stack, cyl_card ** pp_card)
{
    if (p_stack == NULL) {
        return CYL_BAD_PARAM;
    }
    if (p_stack->count <= 0) {
        return CYL_BAD_STATE;
    }

    *pp_card = p_stack->pp_cards[p_stack->count - 1];
    return CYL_OK;
}

cyl_error
cyl_stack_shuffle(cyl_stack * p_stack)
{
    size_t i = 0;

    if (p_stack == NULL) {
        return CYL_BAD_PARAM;
    }

    srand(time(NULL));
    for (i = 0; i < p_stack->count; ++i) {
        size_t new_place = rand() % (i + 1);
        if (new_place == i) {
            continue;
        }
        cyl_card * p_card_tmp = p_stack->pp_cards[new_place];
        p_stack->pp_cards[new_place] = p_stack->pp_cards[i];
        p_stack->pp_cards[i] = p_card_tmp;
    }
    return CYL_OK;
}
