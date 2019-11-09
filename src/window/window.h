#ifndef WINDOW_ENGINE_H
#define WINDOW_ENGINE_H

#include <SFML/Graphics.hpp>
#include <galactic_empires.h>
#include <SFML_Button.h>
#include <sfml_text_window.h>
#include <sfml_text.h>


#define GAME_WINDOW_WIDTH       1066
#define GAME_WINDOW_HEIGHT      600
#define RENDER_POSITION_SCALE   30
#define RENDER_WINDOW_BORDER    20
#define RENDER_TEXT_OFFSET      10
#define PANEL_LEFT_ALIGNED      ((MAP_DIMENSIONS_X * RENDER_POSITION_SCALE) + RENDER_WINDOW_BORDER)
#define PANEL_MARGIN            20
#define PANEL_COLUMN_WIDTH      130
#define PANEL_ROW_HEIGHT        30

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

    SFML_Text           source_world_text;
    SFML_Text           target_world_text;
    SFML_Text           fleet_size_text;

    SFML_Text_Window    source_world_entry;
    SFML_Text_Window    target_world_entry;
    SFML_Text_Window    fleet_size_entry;

    SFML_Button         relay_command_button;
    SFML_Button         next_year_button;

    Galactic_Empires    *galaxy;

};

void    *window_thread(void *var);
void    *input_thread(void *var);

#endif