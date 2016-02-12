#ifndef CYLVION_STACK_H
#define CYLVION_STACK_H

#include "cylvion/error.h"

typedef struct cyl_card cyl_card;
typedef struct cyl_stack cyl_stack;

cyl_stack * cyl_stack_new(size_t size);
void cyl_stack_free(cyl_stack * p_stack);

size_t cyl_stack_get_count(cyl_stack * p_stack);
size_t cyl_stack_get_size(cyl_stack * p_stack);
cyl_card * cyl_stack_get_top(cyl_stack * p_stack);

cyl_error cyl_stack_push(cyl_stack * p_stack, cyl_card * p_card);
cyl_error cyl_stack_pop(cyl_stack * p_stack);

cyl_error cyl_stack_shuffle(cyl_stack * p_stack);

#endif /* CYLVION_STACK_H */
