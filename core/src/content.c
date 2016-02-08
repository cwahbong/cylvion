#include "cylvion/content.h"

#include "cylvion/hand.h"
#include "cylvion/field.h"
#include "cylvion/stack.h"

struct cyl_content {
    int edge;
    cyl_field * p_field;
    cyl_hand * p_hand;
    cyl_stack * p_ravages[CYL_FIELD_ROW_SIZE];
    cyl_stack * p_discarded;
    cyl_stack * p_undrawn;
};

cyl_content *
cyl_content_new()
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
    int i = 0;
    for (i = 0; i < CYL_FIELD_ROW_SIZE; ++i) {
        if ((p_content->p_ravages[i] = cyl_stack_new(50)) == NULL) {
            cyl_content_free(p_content);
            return NULL;
        }
    }
    if ((p_content->p_discarded = cyl_stack_new(50)) == NULL) {
        cyl_content_free(p_content);
        return NULL;
    }
    if ((p_content->p_undrawn = cyl_stack_new(50)) == NULL) {
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
    int i = 0;
    for (i = 0; i < CYL_FIELD_ROW_SIZE; ++i) {
        cyl_stack_free(p_content->p_ravages[i]);
    }
    cyl_stack_free(p_content->p_discarded);
    cyl_stack_free(p_content->p_undrawn);
    free(p_content);
}

cyl_error
cyl_content_get_edge(cyl_content *p_content, int * p_edge)
{
    if (p_content == NULL || p_edge == NULL) {
        return CYL_BAD_PARAM;
    }
    *p_edge = p_content->edge;
    return CYL_OK;
}

cyl_error
cyl_content_set_edge(cyl_content *p_content, int edge)
{
    if (p_content == NULL) {
        return CYL_BAD_PARAM;
    }
    p_content->edge = edge;
    return CYL_OK;
}

cyl_error
cyl_content_get_field(cyl_content * p_content, cyl_field ** pp_field)
{
    if (p_content == NULL || pp_field == NULL) {
        return CYL_BAD_PARAM;
    }

    *pp_field = p_content->p_field;
    return CYL_OK;
}

cyl_error
cyl_content_get_ravage_stack(cyl_content *p_content, size_t row, cyl_stack ** pp_stack)
{
    if (p_content == NULL || pp_stack == NULL) {
        return CYL_BAD_PARAM;
    }
    if (row >= CYL_FIELD_ROW_SIZE) {
        return CYL_BAD_PARAM;
    }

    *pp_stack = p_content->p_ravages[row];
    return CYL_OK;
}

cyl_error
cyl_content_get_hand(cyl_content * p_content, cyl_hand ** pp_hand)
{
    if (p_content == NULL || pp_hand == NULL) {
        return CYL_BAD_PARAM;
    }

    *pp_hand = p_content->p_hand;
    return CYL_OK;
}

cyl_error
cyl_content_get_discarded(cyl_content *p_content, cyl_stack ** pp_stack)
{
    if (p_content == NULL || pp_stack == NULL) {
        return CYL_BAD_PARAM;
    }

    *pp_stack = p_content->p_discarded;
    return CYL_OK;
}

cyl_error
cyl_content_get_undrawn(cyl_content *p_content, cyl_stack ** pp_stack)
{
    if (p_content == NULL || pp_stack == NULL) {
        return CYL_BAD_PARAM;
    }

    *pp_stack = p_content->p_undrawn;
    return CYL_OK;
}
