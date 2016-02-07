#include "cylvion/content.h"

struct cyl_content {
    int edge;
    cyl_field * p_field;
    cyl_hand * p_hand;
    cyl_stack * p_discarded;
    cyl_stack * p_undrawn;
};

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
