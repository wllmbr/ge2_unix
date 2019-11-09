#include <window.h>
#include <stdio.h>

void test_button_func(void){
    printf("\n\nClicked!\n\n");
}

Window::Window(){
    screen.create(sf::VideoMode(1066,600), "Galactic Empires");
    galaxy = NULL;

    /* Load font */
    if(!jeffries.loadFromFile("res/jeffries.ttf")){
        printf("Warning! Cannot load font file!\n");
    }

    /* Setup the Text displays */
    uint8_t i;
    SFML_Text           *txt;
    SFML_Text_Window    *ent;
    for(i = 0; i < 3; i++){
        switch(i){
            case 0:
                txt = &source_world_text;
                ent = &source_world_entry;
                break;
            case 1:
                txt = &target_world_text;
                ent = &target_world_entry;
                break;
            case 2:
                txt = &fleet_size_text;
                ent = &fleet_size_entry;
                break;
            default:
                break;
        }

        /* Find left alignment */
        uint16_t left_align = PANEL_LEFT_ALIGNED;
        /* Add in number of margins */
        left_align += i * (PANEL_MARGIN + PANEL_COLUMN_WIDTH);

        txt->configure(
            &screen,
            &jeffries,
            left_align,
            0,
            PANEL_COLUMN_WIDTH,
            PANEL_ROW_HEIGHT * 2
        );

        ent->configure(
            &screen,
            &jeffries,
            left_align,
            (PANEL_ROW_HEIGHT * 2),
            PANEL_COLUMN_WIDTH,
            PANEL_ROW_HEIGHT
        );

    }

    relay_command_button.configure(
        &screen,
        &jeffries,
        PANEL_LEFT_ALIGNED,
        2 * (PANEL_ROW_HEIGHT + PANEL_MARGIN),
        (3 * PANEL_COLUMN_WIDTH) + (2 * PANEL_MARGIN),
        PANEL_ROW_HEIGHT
    );

    next_year_button.configure(
        &screen,
        &jeffries,
        PANEL_LEFT_ALIGNED,
        GAME_WINDOW_HEIGHT - PANEL_ROW_HEIGHT - PANEL_MARGIN,
        (3 * PANEL_COLUMN_WIDTH) + (2 * PANEL_MARGIN),
        PANEL_ROW_HEIGHT
    );

    /* Setup text */
    source_world_text.set_string("Source\nWorld");
    target_world_text.set_string("Target\nWorld");
    fleet_size_text.set_string("Fleet\nSize");
    relay_command_button.set_string("Transmit Orders");
    next_year_button.set_string("CONTINUE TO NEXT YEAR");

}

Window::~Window(){
}
