#include <stdio.h>

#include <cylvion/error.h>
#include <cylvion/game.h>

int main()
{
    cyl_actor actor;
    cyl_observer observer;
    cyl_game * p_game = cyl_game_new(actor, observer);
    if (p_game == NULL) {
        printf("Game init error.");
        /* TODO do cleanup for actor and observer */
    }
    cyl_result result = CYL_UNKNOWN;
    if (cyl_game_run(p_game, &result) != CYL_OK) {
        printf("Game run error.");
    } else {
        printf("Game ended successfully. win=%d", (int) result);
    }
    cyl_game_free(p_game);
    return 0;
}
