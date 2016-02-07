#include <stdio.h>

#include <cylvion/error.h>
#include <cylvion/game.h>

int main()
{
    cyl_game * p_game = cyl_game_new(NULL, NULL);
    cyl_result result = CYL_UNKNOWN;
    if (cyl_game_run(p_game, &result) != CYL_OK) {
        printf("Game run error.");
    } else {
        printf("Game ended successfully. win=%d", (int) result);
    }
    return 0;
}
