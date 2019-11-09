#include <sfml_text_window.h>
#include <string.h>

void SFML_Text_Window::draw(){
    sf::RectangleShape  outline;
    sf::Text            ts;
    
    outline.setFillColor(sf::Color::Transparent);
    outline.setSize(sf::Vector2f(length,height));
    outline.setPosition(x_pos,y_pos);
    outline.setOutlineThickness(2);

    /* Change the outline color */

    sf::Color draw_color(0,0,0);

    if(is_in_focus){
        draw_color.r = 255;
        draw_color.g = 255;
        draw_color.b = 255;
        draw_color.a = 255;
    } else if (is_hovered){
        draw_color.r = 192;
        draw_color.g = 192;
        draw_color.b = 192;
        draw_color.a = 255;
    } else {
        draw_color.r = 128;
        draw_color.g = 128;
        draw_color.b = 128;
        draw_color.a = 255;
    }

    outline.setOutlineColor(draw_color);

    ts.setFillColor(sf::Color::White);
    ts.setFont(*loaded_font);
    ts.setPosition(x_pos, y_pos);
    ts.setCharacterSize(20);
    ts.setString(text_string);

    screen->draw(outline);
    screen->draw(ts);
}