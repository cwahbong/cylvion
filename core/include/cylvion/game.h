#ifndef CYLVION_GAME_H
#define CYLVION_GAME_H

typedef struct cyl_game cyl_game;
typedef struct cyl_actor cyl_actor;
typedef struct cyl_observer cyl_observer;

cyl_game *
cyl_game_new(cyl_actor * p_actor, cyl_observer * p_observer);
void
cyl_game_free(cyl_game * p_game);

cyl_error
cyl_game_run(cyl_game * p_game, cyl_result * p_result);

#endif /* CYLVION_GAME_H */
