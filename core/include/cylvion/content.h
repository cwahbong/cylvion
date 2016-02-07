#ifndef CYLVION_CONTENT_H
#define CYLVION_CONTENT_H

#include <stdlib.h>

#include "cylvion/error.h"

typedef struct cyl_field cyl_field;
typedef struct cyl_stack cyl_stack;
typedef struct cyl_hand cyl_hand;
typedef struct cyl_content cyl_content;

cyl_error
cyl_content_get_edge(cyl_content * p_content, int * p_edge);
cyl_error
cyl_content_set_edge(cyl_content * p_content, int edge);

cyl_error
cyl_content_get_field(cyl_content * p_content, cyl_field ** pp_field);
cyl_error
cyl_content_get_ravage_stack(cyl_content * p_content, size_t row, cyl_stack ** p_stack);
cyl_error
cyl_content_get_hand(cyl_content * p_content, cyl_hand ** p_hand);
cyl_error
cyl_content_get_discarded(cyl_content * p_content, cyl_stack ** pp_stack);
cyl_error
cyl_content_get_undrawn(cyl_content * p_content, cyl_stack ** pp_stack);

#endif /* CYLVION_CONTENT_H */
