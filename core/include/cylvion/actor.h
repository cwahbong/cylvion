#ifndef CYLVION_ACTOR_H
#define CYLVION_ACTOR_H

#include <stdlib.h>

#include "cylvion/error.h"

typedef struct cyl_content cyl_content;
typedef struct cyl_action cyl_action;

typedef enum cyl_question {
    CYL_QUES_IDX_DISCARDED,
    CYL_QUES_LOCATION_FOUNTAIN,
    CYL_QUES_LOCATION_TREE,
} cyl_question;

struct cyl_idx_answer {
    size_t idx;
};

typedef struct cyl_idx_answer cyl_discard_idx_answer;

typedef struct cyl_location_answer {
    size_t row;
    size_t col;
} cyl_location_answer;

typedef struct cyl_location_answer cyl_fountain_location_answer;
typedef struct cyl_location_answer cyl_tree_location_answer;

typedef struct cyl_actor {
    void * data;
    void (* fn_free_data)(void * data);
    cyl_error (* fn_question)(cyl_content * p_content, cyl_question question, void * data, void * solution);
    cyl_error (* fn_reveal_action)(cyl_content * p_content, cyl_action * p_action, void * data);
    cyl_error (* fn_defend_action)(cyl_content * p_content, cyl_action * p_action, void * data);
} cyl_actor;

#endif /* CYLVION_ACTOR_H */
