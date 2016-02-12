#ifndef CYLVION_ACTOR_H
#define CYLVION_ACTOR_H

#include "cylvion/error.h"

typedef struct cyl_content cyl_content;
typedef struct cyl_action cyl_action;

typedef struct cyl_actor {
    void * data;
    void (* fn_free_data)(void * data);
    cyl_error (* fn_select_cost)(cyl_content * p_content, int * hand_idx);
    cyl_error (* fn_reveal_action)(cyl_content * p_content, cyl_action * p_action, void * data);
    cyl_error (* fn_defend_action)(cyl_content * p_content, cyl_action * p_action, void * data);
} cyl_actor;

#endif /* CYLVION_ACTOR_H */
