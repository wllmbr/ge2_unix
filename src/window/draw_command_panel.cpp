#include <window.h>
#include <string.h>
#include <sfml_button.h>
#include <stdio.h>

void Window::draw_command_panel(){

    source_world_entry.draw();
    target_world_entry.draw();
    fleet_size_entry.draw();

    source_world_text.draw();
    target_world_text.draw();
    fleet_size_text.draw();

    relay_command_button.draw();
    next_year_button.draw();
}