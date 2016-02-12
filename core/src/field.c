#include <stdlib.h>

#include "cylvion/field.h"
#include "cylvion/stack.h"


struct cyl_field {
    cyl_card * cell[CYL_FIELD_ROW_SIZE][CYL_FIELD_COL_SIZE];
    cyl_stack * ravage[CYL_FIELD_ROW_SIZE];
};

cyl_field *
cyl_field_new()
{
    cyl_field * const p_field = calloc(1, sizeof(cyl_field));
    if (p_field == NULL) {
        return NULL;
    }
    size_t r = 0;
    for (r = 0; r < CYL_FIELD_ROW_SIZE; ++r) {
        if ((p_field->ravage[r] = cyl_stack_new(50)) == NULL) {
            cyl_field_free(p_field);
            return NULL;
        }
    }
    return p_field;
}

void
cyl_field_free(cyl_field * p_field)
{
    size_t r = 0;
    for (r = 0; r < CYL_FIELD_ROW_SIZE; ++r) {
        if (p_field->ravage[r] != NULL) {
            cyl_stack_free(p_field->ravage[r]);
        }
    }
    free(p_field);
}

cyl_error
cyl_field_peek_card(cyl_field * p_field, size_t row, size_t col, cyl_card ** pp_card)
{
    if (p_field == NULL || pp_card == NULL) {
        return CYL_BAD_PARAM;
    }
    if (row >= CYL_FIELD_ROW_SIZE || col >= CYL_FIELD_COL_SIZE) {
        return CYL_BAD_PARAM;
    }
    *pp_card = p_field->cell[row][col];
    return CYL_OK;
}

cyl_error
cyl_field_put_card(cyl_field * p_field, size_t row, size_t col, cyl_card * p_card)
{
    if (p_field == NULL || p_card == NULL) {
        return CYL_BAD_PARAM;
    }
    if (row >= CYL_FIELD_ROW_SIZE || col >= CYL_FIELD_COL_SIZE) {
        return CYL_BAD_PARAM;
    }
    if (p_field->cell[row][col] != NULL) {
        return CYL_BAD_STATE;
    }
    p_field->cell[row][col] = p_card;
    return CYL_OK;
}

cyl_error
cyl_field_move_card(cyl_field * p_field, size_t from_row, size_t from_col, size_t to_row, size_t to_col)
{
    if (p_field == NULL) {
        return CYL_BAD_PARAM;
    }
    if (from_row >= CYL_FIELD_ROW_SIZE || from_col >= CYL_FIELD_COL_SIZE ||
            to_row >= CYL_FIELD_ROW_SIZE || to_col >= CYL_FIELD_COL_SIZE) {
        return CYL_BAD_PARAM;
    }
    if (p_field->cell[from_row][from_col] == NULL ||
            p_field->cell[to_row][to_col] != NULL) {
        return CYL_BAD_STATE;
    }
    p_field->cell[to_row][to_col] = p_field->cell[from_row][from_col];
    p_field->cell[from_row][from_col] = NULL;
    return CYL_OK;
}

cyl_error
cyl_field_remove_card(cyl_field * p_field, size_t row, size_t col)
{
    if (p_field == NULL) {
        return CYL_BAD_PARAM;
    }
    if (row >= CYL_FIELD_ROW_SIZE || col >= CYL_FIELD_COL_SIZE) {
        return CYL_BAD_PARAM;
    }
    if (p_field->cell[row][col] != NULL) {
        return CYL_BAD_STATE;
    }
    p_field->cell[row][col] = NULL;
    return CYL_OK;
}

cyl_stack *
cyl_field_get_ravage(cyl_field * p_field, size_t row)
{
    if (p_field == NULL) {
        return NULL;
    }
    if (row >= CYL_FIELD_ROW_SIZE) {
        return NULL;
    }
    return p_field->ravage[row];
}
