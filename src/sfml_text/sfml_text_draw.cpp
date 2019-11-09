#include <sfml_text.h>
#include <string.h>

void SFML_Text::draw(){
    sf::RectangleShape  outline;
    sf::Text            ts;
    
    outline.setFillColor(sf::Color::Transparent);
    outline.setSize(sf::Vector2f(length,height));
    outline.setPosition(x_pos,y_pos);
    outline.setOutlineThickness(1);

    ts.setFillColor(sf::Color::White);
    ts.setFont(*loaded_font);
    ts.setPosition(x_pos, y_pos);
    ts.setCharacterSize(20);
    ts.setString(text_string);

    // screen->draw(outline);
    screen->draw(ts);
}