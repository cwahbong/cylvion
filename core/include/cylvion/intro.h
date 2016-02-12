#ifndef CYLVION_INTRO_H
#define CYLVION_INTRO_H

#include "cylvion/game.h"

typedef struct cyl_game cyl_game;

cyl_game *
cyl_game_new_intro(cyl_actor actor, cyl_observer observer);

#endif /* CYLVION_INTRO_H */
