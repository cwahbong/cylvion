#include <stdlib.h>

#include "cylvion/field.h"


struct cyl_field {
    cyl_card * cell[CYL_FIELD_ROW_SIZE][CYL_FIELD_COL_SIZE];
};

cyl_field *
cyl_field_new()
{
    return calloc(1, sizeof(cyl_field));
}

void
cyl_field_free(cyl_field * p_cyl_field)
{
    free(p_cyl_field);
}

cyl_error
cyl_field_get_card(cyl_field * p_field, size_t row, size_t col, cyl_card ** pp_card)
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
