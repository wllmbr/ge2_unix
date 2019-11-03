#include <window.h>
#include <galactic_empires.h>
#include <world.h>
#include <Fleet.h>
#include <string.h>

void Window::draw_fleets(){

    float fleet_size = 2.f;

    /* Iterate across all of the worlds */
    uint16_t i;
    for(i = 0; i < galaxy->all_fleets.size(); i++){

        /* If the source and current position are the same, but the target is different
            the fleet has just been commited, so don't draw 
        */
        if((galaxy->all_fleets[i].get_source() == galaxy->all_fleets[i].get_pos()) &&
            (galaxy->all_fleets[i].get_source() != galaxy->all_fleets[i].get_target()))
        {
            continue;
        }

        /* Get the coordinates of the world and scale up by 20 */
        Position pos = galaxy->all_fleets[i].get_pos();

        sf::CircleShape shape(fleet_size);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition((pos.get_x() * RENDER_POSITION_SCALE) - (fleet_size) + RENDER_WINDOW_BORDER,
                          (pos.get_y() * RENDER_POSITION_SCALE) - (fleet_size) + RENDER_WINDOW_BORDER);

        sf::Text text;
        text.setFont(jeffries);

        text.setString(std::to_string(galaxy->all_fleets[i].get_size()));
        text.setPosition((pos.get_x() * RENDER_POSITION_SCALE) - (fleet_size) + RENDER_WINDOW_BORDER + RENDER_TEXT_OFFSET,
                         (pos.get_y() * RENDER_POSITION_SCALE) - (fleet_size) + RENDER_WINDOW_BORDER - (RENDER_TEXT_OFFSET * 2));
        text.setCharacterSize(10);
        text.setFillColor(sf::Color::Red);

        screen.draw(text);
        screen.draw(shape);
    }
}