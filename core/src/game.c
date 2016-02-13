#include <stdlib.h>

#include "cylvion/action.h"
#include "cylvion/actor.h"
#include "cylvion/card.h"
#include "cylvion/content.h"
#include "cylvion/error.h"
#include "cylvion/field.h"
#include "cylvion/game.h"
#include "cylvion/hand.h"
#include "cylvion/log.h"
#include "cylvion/stack.h"

struct cyl_game {
    cyl_actor actor;
    cyl_observer observer;
    cyl_content * p_content;
};

cyl_game *
cyl_game_new(cyl_actor actor, cyl_observer observer, cyl_content * (*fn_content_new)())
{
    cyl_game * p_game = calloc(1, sizeof(cyl_game));
    if (p_game == NULL) {
        return NULL;
    }
    if ((p_game->p_content = fn_content_new()) == NULL) {
        cyl_game_free(p_game);
        return NULL;
    }
    p_game->actor = actor;
    p_game->observer = observer;
    return p_game;
}

void
cyl_game_free(cyl_game * p_game)
{
    if (p_game == NULL) {
        return;
    }
    if (p_game->actor.fn_free_data != NULL) {
        p_game->actor.fn_free_data(p_game->actor.data);
    }
    if (p_game->observer.fn_free_data != NULL) {
        p_game->observer.fn_free_data(p_game->observer.data);
    }
    if (p_game->p_content != NULL) {
        cyl_content_free(p_game->p_content);
    }
    free(p_game);
}

cyl_error
cyl_game_has_ravage(cyl_game * p_game, int * has_ravage)
{
    if (p_game == NULL || has_ravage == NULL) {
        return CYL_BAD_PARAM;
    }

    cyl_stack * p_stack = NULL;
    if (cyl_content_get_ravage_stack(p_game->p_content, 0, &p_stack) != CYL_OK) {
        return CYL_ERR;
    }
    size_t count = 0;
    if (cyl_stack_count(p_stack, &count) != CYL_OK) {
        return CYL_ERR;
    }
    *has_ravage = (count > 0);

    return CYL_OK;
}

cyl_error
cyl_field_has_ravage(cyl_field * p_field, int * has_ravage)
{
    if (p_field == NULL || has_ravage == NULL) {
        return CYL_BAD_PARAM;
    }
    *has_ravage = 0;

    cyl_card * p_card = NULL;
    size_t row = 0, col = 0;
    for (row = 0; row < CYL_FIELD_ROW_SIZE; ++row) {
        for (col = 0; col < CYL_FIELD_COL_SIZE; ++col) {
            if (cyl_field_get_card(p_field, row, col, &p_card) != CYL_OK) {
                return CYL_ERR;
            }
            if (p_card == NULL) {
                continue;
            }
            if (cyl_card_is_ravage(p_card)) {
                *has_ravage = 1;
            }
        }
    }
    return CYL_OK;
}

cyl_error
cyl_game_reveal(cyl_game * p_game)
{
    size_t r = 0;

    if (p_game == NULL) {
        return CYL_BAD_PARAM;
    }

    cyl_field * p_field = NULL;
    if (cyl_content_get_field(p_game->p_content, &p_field) != CYL_OK || p_field == NULL) {
        cyl_log_error("get_field");
        return CYL_ERR;
    }

    cyl_stack * p_stack = NULL;
    cyl_card * p_card = NULL;
    for (r = 0; r < CYL_FIELD_ROW_SIZE; ++r) {
        if (cyl_content_get_ravage_stack(p_game->p_content, r, &p_stack) != CYL_OK || p_stack == NULL) {
            cyl_log_error("get ravage stack");
            return CYL_ERR;
        }
        if (cyl_stack_top(p_stack, &p_card) != CYL_OK) {
            cyl_log_error("get stack top");
            return CYL_ERR;
        }
        if (cyl_field_put_card(p_field, r, CYL_FIELD_COL_SIZE - 1, p_card) != CYL_OK) {
            cyl_log_error("field put card");
            return CYL_ERR;
        }
        if (cyl_stack_pop(p_stack) != CYL_OK) {
            cyl_log_error("stack pop");
            return CYL_ERR;
        }
    }
    cyl_error action_ret = CYL_OK;
    cyl_action action;
    while (1) {
        if (p_game->actor.fn_reveal_action == NULL) {
            cyl_log_error("no reveal action");
            return CYL_ERR;
        }
        action_ret = p_game->actor.fn_reveal_action(p_game->p_content, &action, p_game->actor.data);
        if (action_ret == CYL_OK) {
            /* TODO do action. */
            continue;
        } else if (action_ret == CYL_FINISH) {
            break;
        } else {
            return action_ret;
        }
    }
    return CYL_OK;
}

cyl_error
cyl_game_move_battle(cyl_game * p_game)
{
    if (p_game == NULL) {
        return CYL_BAD_PARAM;
    }
    cyl_field * p_field = NULL;
    if (cyl_content_get_field(p_game->p_content, &p_field) != CYL_OK) {
        return CYL_ERR;
    }

    size_t row = 0, col = 0;
    cyl_card * p_card = NULL;
    for (row = 0; row < CYL_FIELD_ROW_SIZE; ++row) {
        for (col = 0; col < CYL_FIELD_COL_SIZE; ++col) {
            if (cyl_field_get_card(p_field, row, col, &p_card) != CYL_OK) {
                return CYL_ERR;
            }
            if (p_card == NULL) {
                continue;
            }
            if (! cyl_card_is_ravage(p_card)) {
                continue;
            }
            if (0/* has non-ravage at left */) {
                /* battle */
            }
            if (0/* ravage is alive */) {
                /* move */
            }
        }
    }
    return CYL_OK;
}

cyl_error
cyl_game_draw(cyl_game * p_game)
{
    if (p_game == NULL) {
        return CYL_BAD_PARAM;
    }

    cyl_hand * p_hand = NULL;
    if (cyl_content_get_hand(p_game->p_content, &p_hand) != CYL_OK) {
        return CYL_ERR;
    }

    cyl_stack * p_undrawn = NULL;
    if (cyl_content_get_undrawn(p_game->p_content, &p_undrawn) != CYL_OK) {
        return CYL_ERR;
    }

    cyl_card * p_card = NULL;
    int i = 0;
    for (; i < 3; ++i) {
        if (cyl_stack_top(p_undrawn, &p_card) != CYL_OK) {
            return CYL_ERR;
        }
        /* TODO handle if hand already has 10 cards. */
        if (cyl_hand_add_card(p_hand, p_card) != CYL_OK) {
            return CYL_ERR;
        }
        if (cyl_stack_pop(p_undrawn) != CYL_OK) {
            return CYL_ERR;
        }
    }

    return CYL_OK;
}

cyl_error
cyl_game_use_card(cyl_game * p_game)
{
    if (p_game == NULL) {
        return CYL_BAD_PARAM;
    }
    if (p_game->actor.fn_defend_action == NULL) {
        return CYL_BAD_STATE;
    }

    cyl_hand * p_hand = NULL;
    if (cyl_content_get_hand(p_game->p_content, &p_hand) != CYL_OK) {
        return CYL_ERR;
    }

    cyl_error action_ret = CYL_OK;
    cyl_action action;
    while (1) {
        action_ret = p_game->actor.fn_defend_action(p_game->p_content, &action, p_game->actor.data);
        if (action_ret == CYL_OK) {
            size_t hand_count = 0;
            if (cyl_hand_get_count(p_hand, &hand_count) != CYL_OK) {
                return CYL_ERR;
            }
            if (action.idx >= hand_count) {
                continue;
            }
            cyl_card * p_card = NULL;
            if (cyl_hand_get_card(p_hand, action.idx, &p_card) != CYL_OK) {
                return CYL_ERR;
            }
            if (cyl_card_on_use(p_card, p_game->p_content, p_game->actor) != CYL_OK) {
                return CYL_ERR;
            }
            continue;
        } else if (action_ret == CYL_FINISH) {
            break;
        } else {
            return action_ret;
        }
    }
    return CYL_OK;
}

cyl_error
cyl_game_last_move(cyl_game * p_game)
{
    cyl_field * p_field = NULL;
    if (cyl_content_get_field(p_game->p_content, &p_field) != CYL_OK) {
        return CYL_ERR;
    }
    int has_ravage = 0;
    while (1) {
        if (cyl_field_has_ravage(p_field, &has_ravage) != CYL_OK) {
            return CYL_ERR;
        }
        if (!has_ravage) {
            break;
        }
        if (cyl_game_move_battle(p_game) != CYL_OK) {
            return CYL_ERR;
        }
    }
    return CYL_OK;
}

cyl_error
cyl_game_run(cyl_game * p_game, cyl_result * p_result)
{
    int has_ravage = 0;

    *p_result = CYL_UNKNOWN;

    if (p_game == NULL) {
        cyl_log_error("null p_game");
        return CYL_BAD_PARAM;
    }

    while (1) {
        cyl_log_debug("Before ravage %d", has_ravage);
        if (cyl_game_has_ravage(p_game, &has_ravage) != CYL_OK) {
            cyl_log_error("has ravage");
            return CYL_ERR;
        }
        cyl_log_debug("After ravage %d", has_ravage);
        if (!has_ravage) {
            break;
        }
        if (cyl_game_reveal(p_game) != CYL_OK) {
            cyl_log_error("reveal");
            return CYL_ERR;
        }
        if (cyl_game_move_battle(p_game) != CYL_OK) {
            cyl_log_error("move battle");
            return CYL_ERR;
        }
        if (cyl_game_draw(p_game) != CYL_OK) {
            cyl_log_error("draw");
            return CYL_ERR;
        }
        if (cyl_game_use_card(p_game) != CYL_OK) {
            cyl_log_error("use card");
            return CYL_ERR;
        }
    }
    if (cyl_game_last_move(p_game) != CYL_OK) {
        cyl_log_error("last move");
        return CYL_ERR;
    }
    if (*p_result == CYL_UNKNOWN) {
        *p_result = CYL_WIN;
    }
    return CYL_OK;
}
