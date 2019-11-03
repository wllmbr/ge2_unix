#include <sfml_button.h>
#include <stdlib.h>

SFML_Button::SFML_Button(){
    
}

SFML_Button::SFML_Button(sf::RenderWindow *scr,
                         sf::Font *lf,
                         int16_t x,
                         int16_t y,
                         int16_t len,
                         int16_t hgt,
                         void (*fh)())
{
    configure(
        scr,
        lf,
        x,
        y,
        len,
        hgt,
        fh
    );
}

void SFML_Button::configure(sf::RenderWindow *scr,
                            sf::Font *lf,
                            int16_t x,
                            int16_t y,
                            int16_t len,
                            int16_t hgt,
                            void (*fh)())
{
    x_pos       = x;
    y_pos       = y;
    callback    = fh;
    length      = len;
    height      = hgt;
    is_pressed  = false;
    is_hovered  = false;

    screen      = scr;
    loaded_font = lf;
}