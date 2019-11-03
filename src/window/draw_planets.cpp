#include <window.h>
#include <galactic_empires.h>
#include <world.h>
#include <Location.h>

void Window::draw_planets(){

    float planet_size = 8.f;

    /* Load font */

    /* Iterate across all of the worlds */
    uint16_t i;
    for(i = 0; i < galaxy->all_worlds.size(); i++){
        /* Get the coordinates of the world and scale up by 20 */
        Position pos = galaxy->all_worlds[i].get_position();

        sf::CircleShape shape(planet_size);

        /* Build the color */

        switch(galaxy->all_worlds[i].get_owner()){
            case 0:
                shape.setOutlineColor(sf::Color(0,0,255));
                break;
            case 1:
                shape.setOutlineColor(sf::Color(112,36,64));
                break;
            case 2:
                shape.setOutlineColor(sf::Color(68,43,126));
                break;
            case 3:
                shape.setOutlineColor(sf::Color(228,0,253));
                break;
            case 4:
                shape.setOutlineColor(sf::Color(21,90,64));
                break;
            case 5:
                shape.setOutlineColor(sf::Color(128,128,128));
                break;
            case 6:
                shape.setOutlineColor(sf::Color(69,146,253));
                break;
            case 7:
                shape.setOutlineColor(sf::Color(194,174,254));
                break;
            case 8:
                shape.setOutlineColor(sf::Color(63,78,4));
                break;
            case 9:
                shape.setOutlineColor(sf::Color(222,103,18));
                break;
            case 10:
                shape.setOutlineColor(sf::Color(128,255,128));
                break;
            case 11:
                shape.setOutlineColor(sf::Color(238,164,191));
                break;
            case 12:
                shape.setOutlineColor(sf::Color(35,208,20));
                break;
            case 13:
                shape.setOutlineColor(sf::Color(189,207,130));
                break;
            case 14:
                shape.setOutlineColor(sf::Color(145,218,191));
                break;
            case 15:
                shape.setOutlineColor(sf::Color(255,255,255));
                break;
            default:
                shape.setOutlineColor(sf::Color::Red);
        }



        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineThickness(1.0);
        shape.setPosition((pos.get_x() * RENDER_POSITION_SCALE) - (planet_size) + RENDER_WINDOW_BORDER,
                          (pos.get_y() * RENDER_POSITION_SCALE) - (planet_size) + RENDER_WINDOW_BORDER);

                          
        sf::Text text;
        text.setFont(jeffries);

        text.setString(std::to_string(i));
        text.setPosition((pos.get_x() * RENDER_POSITION_SCALE) - (planet_size) + RENDER_WINDOW_BORDER + (RENDER_TEXT_OFFSET * 2),
                         (pos.get_y() * RENDER_POSITION_SCALE) - (planet_size) + RENDER_WINDOW_BORDER);
        text.setCharacterSize(10);
        text.setFillColor(sf::Color::White);

        screen.draw(text);
        screen.draw(shape);
    }
}