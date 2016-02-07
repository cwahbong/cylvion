#ifndef CYLVION_OBSERVER_H
#define CYLVION_OBSERVER_H

#include "cylvion/error.h"

typedef struct cyl_observer {
    void * data;
    void (* fn_free_data)(void * data);
} cyl_observer;

#endif /* CYLVION_OBSERVER_H */
