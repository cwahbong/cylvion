#ifndef CYLVION_FIELD_H
#define CYLVION_FIELD_H

#include "cylvion/error.h"

#define CYL_FIELD_ROW_SIZE 4
#define CYL_FIELD_COL_SIZE 5

typedef struct cyl_card cyl_card;
typedef struct cyl_field cyl_field;

cyl_field * cyl_field_new();
void cyl_field_free(cyl_field * p_field);

cyl_error cyl_field_get_card(cyl_field * p_field, size_t row, size_t col, cyl_card ** pp_card);
cyl_error cyl_field_put_card(cyl_field * p_field, size_t row, size_t col, cyl_card * p_card);
cyl_error cyl_field_move_card(cyl_field * p_field, size_t from_row, size_t from_col, size_t to_row, size_t to_col);
cyl_error cyl_field_remove_card(cyl_field * p_field, size_t row, size_t col);

#endif /* CYLVION_FIELD_H */
