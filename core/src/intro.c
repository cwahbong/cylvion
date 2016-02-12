#include "cylvion/intro.h"

#include "cylvion/card.h"
#include "cylvion/content.h"
#include "cylvion/field.h"
#include "cylvion/log.h"
#include "cylvion/stack.h"

static cyl_error
cyl_content_stack_add_card(cyl_content * p_content, cyl_stack * p_stack, cyl_card * p_card)
{
    if (cyl_content_manage_card(p_content, p_card) != CYL_OK) {
        cyl_log_error("Manage failed.");
        cyl_card_free(p_card);
        return CYL_ERR;
    }
    if (cyl_stack_push(p_stack, p_card) != CYL_OK) {
        cyl_log_error("Push failed.");
        return CYL_ERR;
    }
    return CYL_OK;
}

static cyl_error
cyl_content_init_intro_ravage_elemental(cyl_content * p_content, cyl_stack * p_ravage)
{
    int strength = 1;
    for (strength = 1; strength <= 4; ++strength) {
        size_t copies = 0;
        for (copies = 0; copies < 4; ++copies) {
            cyl_card * p_card = cyl_card_new_elemental(strength);
            if (cyl_content_stack_add_card(p_content, p_ravage, p_card) != CYL_OK) {
                cyl_log_error("Failed to init ravage elemental.");
                return CYL_ERR;
            }
        }
    }
    return CYL_OK;
}

static cyl_error
cyl_content_init_intro_ravage(cyl_content * p_content)
{
    cyl_stack * p_ravage = cyl_stack_new(1000);
    if (cyl_content_init_intro_ravage_elemental(p_content, p_ravage) != CYL_OK) {
        cyl_stack_free(p_ravage);
        return CYL_ERR;
    }
    if (cyl_stack_shuffle(p_ravage) != CYL_OK) {
        cyl_stack_free(p_ravage);
        return CYL_ERR;
    }

    cyl_field * p_field = cyl_content_get_field(p_content);
    if (p_field == NULL) {
        return CYL_ERR;
    }
    int row = 0;
    while (1) {
        size_t count = cyl_stack_get_count(p_ravage);
        if (count == 0) {
            break;
        }
        for (row = 0; row < 4; ++row) {
            cyl_stack * p_row_ravage = cyl_field_get_ravage(p_field, row);
            if (p_row_ravage == NULL) {
                cyl_stack_free(p_ravage);
                return CYL_BAD_STATE;
            }
            cyl_card * p_card = cyl_stack_get_top(p_ravage);
            if (p_card == NULL) {
                cyl_stack_free(p_ravage);
                return CYL_BAD_STATE;
            }
            if (cyl_stack_push(p_row_ravage, p_card) != CYL_OK) {
                cyl_stack_free(p_ravage);
                return CYL_BAD_STATE;
            }
            if (cyl_stack_pop(p_ravage) != CYL_OK) {
                cyl_stack_free(p_ravage);
                return CYL_ERR;
            }
        }
    }

    cyl_stack_free(p_ravage);
    return CYL_OK;
}

static cyl_error
cyl_content_init_intro_undrawn_fountain(cyl_content * p_content, cyl_stack * p_undrawn)
{
    int strength = 1;
    for (strength = 1; strength <= 4; ++strength) {
        const int cost = strength - 1;
        size_t copies = 0;
        for (copies = 0; copies < 4; ++copies) {
            cyl_card * p_card = cyl_card_new_fountain(cost, strength);
            if (cyl_content_stack_add_card(p_content, p_undrawn, p_card) != CYL_OK) {
                return CYL_ERR;
            }
        }
    }
    return CYL_OK;
}

static cyl_error
cyl_content_init_intro_undrawn_tree(cyl_content * p_content, cyl_stack * p_undrawn)
{
    int vitality = 1;
    for (vitality = 1; vitality <= 4; ++vitality) {
        const int cost = vitality - 1;
        size_t copies = 0;
        for (copies = 0; copies < 4; ++copies) {
            cyl_card * p_card = cyl_card_new_tree(cost, vitality);
            if (cyl_content_stack_add_card(p_content, p_undrawn, p_card) != CYL_OK) {
                return CYL_ERR;
            }
        }
    }
    return CYL_OK;
}

static cyl_error
cyl_content_init_intro_undrawn(cyl_content * p_content)
{
    cyl_stack * p_undrawn = cyl_content_get_undrawn(p_content);
    if (p_undrawn == NULL) {
        return CYL_BAD_STATE;
    }
    if (cyl_content_init_intro_undrawn_fountain(p_content, p_undrawn) != CYL_OK) {
        return CYL_ERR;
    }
    if (cyl_content_init_intro_undrawn_tree(p_content, p_undrawn) != CYL_OK) {
        return CYL_ERR;
    }
    return CYL_OK;
}

static cyl_content *
cyl_content_new_intro()
{
    cyl_content * p_content = cyl_content_new(1000);
    if (p_content == NULL) {
        return NULL;
    }
    if (cyl_content_init_intro_ravage(p_content) != CYL_OK) {
        cyl_content_free(p_content);
        return NULL;
    }
    if (cyl_content_init_intro_undrawn(p_content) != CYL_OK) {
        cyl_content_free(p_content);
        return NULL;
    }
    return p_content;
}

cyl_game *
cyl_game_new_intro(cyl_actor actor, cyl_observer observer)
{
    return cyl_game_new(actor, observer, cyl_content_new_intro);
}
