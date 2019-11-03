#include <window.h>
#include <stdio.h>

void test_button_func(void){
    printf("\n\nClcked!\n\n");
}

Window::Window(){
    screen.create(sf::VideoMode(1066,600), "Galactic Empires");
    galaxy = NULL;

    /* Load font */
    if(!jeffries.loadFromFile("res/jeffries.ttf")){
        printf("Warning! Cannot load font file!\n");
    }

    test_button.configure(
        &screen,
        &jeffries,
        PANEL_LEFT_ALIGNED,
        70,
        430,
        30,
        &test_button_func
    );

    test_button.set_string("Transmit Orders");

}

Window::~Window(){
}
