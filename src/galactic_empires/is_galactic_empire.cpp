#include <galactic_empires.h>
#include <stdio.h>

void Galactic_Empires::is_galactic_empire() {
    /* Look at the owner of every world, if they're all the same, the game is over*/
    bool has_won = true;
    uint16_t winner_id = all_worlds[0].get_owner();
    for (uint16_t i = 0; i < all_worlds.size(); i++) {
        if (all_worlds[i].get_owner() != winner_id) {
            has_won = false;
        }
    }

    if (has_won) {
        printf("Fleet Admiral %d controls the Galaxy!\n", winner_id);
        exit_game = true;
    }

    return;
}
