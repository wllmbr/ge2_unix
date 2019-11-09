#include <sfml_text_window.h>
#include <string.h>

uint16_t SFML_Text_Window::get_value(void){
    uint16_t value = 0;
    try{
        value =  (uint16_t) std::stoi(text_string,nullptr);
    } catch(...){
        value =  0;
    }

    return value;
}