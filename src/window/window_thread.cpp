#include <window.h>
#include <time.h>
#include <stdint.h>

void    *window_thread(void *var){

    Window *screen;
    screen = (Window*)var;
    
    struct timespec time;
    uint64_t last_time_ms;
    uint64_t cur_time_ms;

    clock_gettime(CLOCK_REALTIME, &time);
    last_time_ms = (time.tv_sec * 1000) + (time.tv_nsec / 1000000);

    /* Loop window tick at 60 fps */
    do{
        /* Block while 16 milliseconds haven't passed yet */
        while(1){
            clock_gettime(CLOCK_REALTIME, &time);
            cur_time_ms = (time.tv_sec * 1000) + (time.tv_nsec / 1000000);
            if(cur_time_ms > (last_time_ms + 16)){
                last_time_ms = cur_time_ms;
                break;
            }
        }

        /* Update the screen for the game, and check if its dead */
        if(screen->perform_window_tick() == false){
            /* Game is dead, let the thread die */
            break;
        }
    }while(screen->is_screen_up());

    
    printf("Exiting Thread\n");
    fflush(stdout);
    

    /* Ask the main thread to also die */
    printf("Closing screen\n");
    screen->close_window();

    /* Destory screen */
    // screen->~Window();

    return var;
}