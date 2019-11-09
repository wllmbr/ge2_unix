#ifndef SFML_TEXT_H
#define SFML_TEXT_H

#include <SFML/Graphics.hpp>
#include <galactic_empires.h>
#include <string>

class SFML_Text{
public:

    SFML_Text();
    SFML_Text(sf::RenderWindow *scr,
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

    void draw();

    inline void set_string(std::string s){
        text_string = s;
    }

    inline void clear_string(){
        text_string = "";
    }

private:
    sf::RenderWindow    *screen;
    sf::Font            *loaded_font;

    int16_t x_pos;
    int16_t y_pos;
    int16_t length;
    int16_t height;

    std::string text_string;

};

#endif