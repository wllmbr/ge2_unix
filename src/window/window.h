#ifndef WINDOW_ENGINE_H
#define WINDOW_ENGINE_H

#include <SFML/Graphics.hpp>
#include <galactic_empires.h>
#include <SFML_Button.h>

#define RENDER_POSITION_SCALE   30
#define RENDER_WINDOW_BORDER    20
#define RENDER_TEXT_OFFSET      10
#define PANEL_LEFT_ALIGNED      ((MAP_DIMENSIONS_X * RENDER_POSITION_SCALE) + RENDER_WINDOW_BORDER)

class Window{
public:
    Window();
    ~Window();

    void    install_galaxy(Galactic_Empires *empire);

    bool perform_window_tick();
    bool perform_input_tick();
    inline bool is_screen_up(){
        return screen.isOpen();
    }

    inline void close_window(){
        galaxy->exit_game = true;
    }

private:

    uint8_t mouse_x;
    uint8_t mouse_y;

    void draw_fleets();
    void draw_planets();
    void draw_command_panel();

    sf::RenderWindow    screen;
    sf::Font            jeffries;

    SFML_Button         test_button;

    Galactic_Empires    *galaxy;

};

void    *window_thread(void *var);
void    *input_thread(void *var);

#endif