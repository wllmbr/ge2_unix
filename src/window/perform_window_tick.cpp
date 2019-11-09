#include <window.h>

bool    Window::perform_window_tick(){

    /* Check if the game is still alive */

    if(galaxy->exit_game){
        printf("Game is done, closing window\n");
        return false;
    }

    sf::Event event;
    while( screen.pollEvent(event)){
        // printf("Event!\n");
        if (event.type == sf::Event::Closed){
            screen.close();
        }

        source_world_entry.poll(event);
        target_world_entry.poll(event);
        fleet_size_entry.poll(event);

        relay_command_button.poll(event);
        next_year_button.poll(event);

    }

    /* Send anything relevant over to the game */

    /* Check if we're trying to commit a fleet */
    if(relay_command_button.check_pressed() == true){
        enum GE_Error_Codes ec;
        /* Try to commit the fleet */
        ec = galaxy->send_command(
            0,
            source_world_entry.get_value(),
            target_world_entry.get_value(),
            fleet_size_entry.get_value()
        );

        /* If it worked, clear the fields */
        if(ec == GE_SUCCESS){
            source_world_entry.clear_string();
            target_world_entry.clear_string();
            fleet_size_entry.clear_string();
        }
    }

    if(next_year_button.check_pressed() == true){
        galaxy->perform_year = true;
    }

    /* Prep the screen for drawing the map */
    screen.clear();

    if(galaxy == NULL){
        printf("Galaxy not initialized\n");
        return true; 
    } else {
        draw_planets();
        draw_fleets();
        draw_command_panel();
    }
    screen.display();

    return true;
}