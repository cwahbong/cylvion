#ifndef CYLVION_GAME_H
#define CYLVION_GAME_H

#include "cylvion/actor.h"
#include "cylvion/observer.h"

typedef struct cyl_game cyl_game;

cyl_game *
cyl_game_new(cyl_actor actor, cyl_observer observer);
void
cyl_game_free(cyl_game * p_game);

cyl_error
cyl_game_run(cyl_game * p_game, cyl_result * p_result);

#endif /* CYLVION_GAME_H */
