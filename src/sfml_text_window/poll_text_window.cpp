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

    /* Check if a key was pressed */
    } else if (event.type == sf::Event::KeyPressed){
        /* Are we in focus */
        fflush(stdout);
        if(is_in_focus){
            /* Get the key and append it to the string */
            switch(event.key.code){
                case sf::Keyboard::Num0:
                case sf::Keyboard::Numpad0:
                    text_string.append("0");
                    break;
                case sf::Keyboard::Num1:
                case sf::Keyboard::Numpad1:
                    text_string.append("1");
                    break;
                case sf::Keyboard::Num2:
                case sf::Keyboard::Numpad2:
                    text_string.append("2");
                    break;
                case sf::Keyboard::Num3:
                case sf::Keyboard::Numpad3:
                    text_string.append("3");
                    break;
                case sf::Keyboard::Num4:
                case sf::Keyboard::Numpad4:
                    text_string.append("4");
                    break;
                case sf::Keyboard::Num5:
                case sf::Keyboard::Numpad5:
                    text_string.append("5");
                    break;
                case sf::Keyboard::Num6:
                case sf::Keyboard::Numpad6:
                    text_string.append("6");
                    break;
                case sf::Keyboard::Num7:
                case sf::Keyboard::Numpad7:
                    text_string.append("7");
                    break;
                case sf::Keyboard::Num8:
                case sf::Keyboard::Numpad8:
                    text_string.append("8");
                    break;
                case sf::Keyboard::Num9:
                case sf::Keyboard::Numpad9:
                    text_string.append("9");
                    break;
                case sf::Keyboard::BackSpace:
                    /* Don't delete a character unless there is something there */
                    if(text_string.length() != 0){
                        text_string.pop_back();
                    }
                default:
                    break;
            }
        }
    }
}