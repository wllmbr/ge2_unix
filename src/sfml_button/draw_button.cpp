#include <sfml_button.h>
#include <string.h>

void SFML_Button::draw(){
    sf::Text button_string;

    sf::RectangleShape outline;

    outline.setFillColor(sf::Color::Transparent);
    outline.setSize(sf::Vector2f(length,height));
    outline.setPosition(x_pos,y_pos);
    outline.setOutlineThickness(2);

    button_string.setFont(*loaded_font);
    button_string.setString(text_string);
    button_string.setPosition(x_pos,y_pos);
    button_string.setCharacterSize(20);

    /* Adjust the string position */
    sf::FloatRect bs_rect   = button_string.getLocalBounds();
    float real_length       = bs_rect.width;

    /* Build and apply padding */
    float x_padding = (length - real_length) / 2;

    button_string.setPosition(x_pos + x_padding, y_pos);

    sf::Color draw_color(0,0,0);

    if((has_rendered_pressed > 0) || (is_pressed)){
        /* Clicked */
        draw_color.r = 255;
        draw_color.g = 255;
        draw_color.b = 255;
        draw_color.a = 128;

        /* Also move the whole button */
        button_string.move(1,1);
        outline.move(1,1);
        if((has_rendered_pressed > 0) && (!is_pressed)){
            has_rendered_pressed--;
        }

    } else if(is_hovered){
        /* Highlight */
        draw_color.r = 255;
        draw_color.g = 255;
        draw_color.b = 255;
        draw_color.a = 255;
    } else {
        /* Normal color */
        draw_color.r = 192;
        draw_color.g = 192;
        draw_color.b = 192;
        draw_color.a = 128;
        draw_color.a = 255;
    }

    button_string.setFillColor(draw_color);
    outline.setOutlineColor(draw_color);

    screen->draw(outline);
    screen->draw(button_string);
}