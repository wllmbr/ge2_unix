#include <window.h>
#include <string.h>
#include <sfml_button.h>
#include <stdio.h>

void test_callback(void){
    printf("Clicked!\n");
}

void Window::draw_command_panel(){

    /* Start drawing the panel off to the right */
    const uint16_t panel_left_aligned = PANEL_LEFT_ALIGNED;

    sf::Text source_world_tx;
    sf::Text target_world_tx;
    sf::Text fleet_size_tx;

    test_button.draw();

    source_world_tx.setFont(jeffries);
    source_world_tx.setString("Source\nWorld");
    source_world_tx.setPosition(panel_left_aligned, 10);
    source_world_tx.setCharacterSize(20);

    target_world_tx.setFont(jeffries);
    target_world_tx.setString("Target\nWorld");
    target_world_tx.setPosition(panel_left_aligned + 150 , 10);
    target_world_tx.setCharacterSize(20);

    fleet_size_tx.setFont(jeffries);
    fleet_size_tx.setString("Fleet\nSize");
    fleet_size_tx.setPosition(panel_left_aligned + 300, 10);
    fleet_size_tx.setCharacterSize(20);

    screen.draw(source_world_tx);
    screen.draw(target_world_tx);
    screen.draw(fleet_size_tx);

}