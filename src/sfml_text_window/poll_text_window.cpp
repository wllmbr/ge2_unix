#include <sfml_text_window.h>

void SFML_Text_Window::poll(sf::Event event)
{
    /* If the button was pressed, lets see if we're now in focus */
    if (event.type == sf::Event::MouseButtonPressed){
        /* Check if the cursor is within the box */
        if( (event.mouseButton.button   == sf::Mouse::Button::Left) &&
            (is_hovered                 == true)
        ){
            is_in_focus = true;
        } else {
            is_in_focus = false;
        }

    /* If the mouse is hovering over the box, mark that */
    } else if (event.type == sf::Event::MouseMoved){

        /* The event holder for mouse position is kinda broken,
            so use the mouse interface directly
        */
        sf::Vector2i global_pos = sf::Mouse::getPosition();
        sf::Vector2i window_pos = screen->getPosition();
        sf::Vector2i in_window = window_pos - global_pos;
        in_window *= -1;

        /* Check if the cursor is within the box */
        if( (in_window.x        >= x_pos) &&
            (in_window.x        <= (x_pos + length)) &&
            (in_window.y        >= y_pos) &&
            (in_window.y        <= (y_pos + height))
        ){
            is_hovered = true;
        } else {
            /* Reset hover */
            is_hovered = false;
        }
    } else if (event.type == sf::Event::KeyPressed)
}