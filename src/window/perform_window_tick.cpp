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
        test_button.poll(event);
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