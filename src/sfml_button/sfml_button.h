#ifndef SFML_BUTTON_H
#define SFML_BUTTON_H

#include <SFML/Graphics.hpp>
#include <galactic_empires.h>
#include <string>

class SFML_Button{
public:

    SFML_Button();
    SFML_Button(sf::RenderWindow *scr,
                sf::Font *lf,
                int16_t x,
                int16_t y,
                int16_t len,
                int16_t hgt,
                void (*fh)()
                );

    void configure(sf::RenderWindow *scr,
                   sf::Font *lf,
                   int16_t x,
                   int16_t y,
                   int16_t len,
                   int16_t hgt,
                   void (*fh)()
                   );

    void poll(sf::Event event);
    void draw();

    inline void set_string(std::string s){
        text_string = s;
    }

private:
    sf::RenderWindow    *screen;
    sf::Font            *loaded_font;

    int16_t x_pos;
    int16_t y_pos;
    int16_t length;
    int16_t height;

    void (*callback)();

    bool is_pressed;
    bool is_hovered;

    std::string text_string;

};

#endif