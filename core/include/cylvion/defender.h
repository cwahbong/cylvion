#ifndef CYLVION_DEFENDER_H
#define CYLVION_DEFENDER_H

#include "cylvion/error.h"

typedef struct cyl_defender cyl_defender;

cyl_defender * cyl_defender_new(int size);
void cyl_defender_free(cyl_defender *);

#endif /* CYLVION_DEFENDER_H */
