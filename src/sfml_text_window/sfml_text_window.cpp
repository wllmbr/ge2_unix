#include <sfml_text_window.h>

SFML_Text_Window::SFML_Text_Window(){
}

SFML_Text_Window::SFML_Text_Window(sf::RenderWindow *scr,
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

void SFML_Text_Window::configure(sf::RenderWindow *scr,
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

    is_in_focus = false;
    text_string = "";
}