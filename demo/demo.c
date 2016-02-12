#include <stdio.h>

#include <cylvion/error.h>
#include <cylvion/lib.h>
#include <cylvion/intro.h>

int main()
{
    cyl_lib_init();
    cyl_actor actor = {NULL, NULL, NULL, NULL, NULL};
    cyl_observer observer = {NULL, NULL};
    cyl_game * p_game = cyl_game_new_intro(actor, observer);
    if (p_game == NULL) {
        printf("Game init error.\n");
        /* TODO do cleanup for actor and observer */
        return -1;
    }
    cyl_error err = CYL_OK;
    cyl_result result = CYL_UNKNOWN;
    if ((err = cyl_game_run(p_game, &result)) != CYL_OK) {
        printf("Game run error, err=%d.\n", err);
    } else {
        printf("Game ended successfully. win=%d\n", (int) result);
    }
    cyl_game_free(p_game);
    cyl_lib_free();
    return 0;
}
