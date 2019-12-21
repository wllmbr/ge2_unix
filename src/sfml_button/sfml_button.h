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
                int16_t hgt
                );

    void configure(sf::RenderWindow *scr,
                   sf::Font *lf,
                   int16_t x,
                   int16_t y,
                   int16_t len,
                   int16_t hgt
                   );

    void poll(sf::Event event);
    void draw();

    inline void set_string(std::string s){
        text_string = s;
    }

    inline bool check_pressed(void){

        /* If the button was pressed but that hasn't been relayed, relay it */
        if(is_pressed && !last_read_state){
            last_read_state = true;
            return true;

        /* If its still pressed, return false but don't update */
        } else {
            last_read_state = false;
            return false;
        }
    }

private:
    sf::RenderWindow    *screen;
    sf::Font            *loaded_font;

    int16_t x_pos;
    int16_t y_pos;
    int16_t length;
    int16_t height;

    bool is_pressed;
    bool is_hovered;
    int  has_rendered_pressed;
    bool last_read_state;

    std::string text_string;

};

#endif