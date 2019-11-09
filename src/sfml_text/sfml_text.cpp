#include <sfml_text.h>

SFML_Text::SFML_Text(){
}

SFML_Text::SFML_Text(sf::RenderWindow *scr,
                     sf::Font *lf,
                     int16_t x,
                     int16_t y,
                     int16_t len,
                     int16_t hgt
                     )
{
    configure(
        scr,
        lf,
        x,
        y,
        len,
        hgt
    );
}

void SFML_Text::configure(sf::RenderWindow *scr,
                        sf::Font *lf,
                        int16_t x,
                        int16_t y,
                        int16_t len,
                        int16_t hgt
                        )
{
    screen      = scr;
    loaded_font = lf;
    x_pos       = x;
    y_pos       = y;
    length      = len;
    height      = hgt;
    text_string = "";
}