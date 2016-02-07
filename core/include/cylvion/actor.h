#ifndef CYLVION_ACTOR_H
#define CYLVION_ACTOR_H

#include "cylvion/error.h"

typedef struct cyl_content cyl_content;
typedef struct cyl_actions cyl_actions;

typedef struct cyl_actor {
    void * data;
    void (* fn_free_data)(void * data);
    cyl_error (* fn_defend_actions)(cyl_content * p_content, cyl_actions * p_actions, void * data);
} cyl_actor;

#endif /* CYLVION_ACTOR_H */
