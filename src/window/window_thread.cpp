#include <window.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>

void    *window_thread(void *var){

    Window *screen;
    screen = (Window*)var;
    
    struct timespec time;
    int64_t wake_time_ms;
    int64_t cur_time_ms;

    clock_gettime(CLOCK_REALTIME, &time);
    wake_time_ms = ((time.tv_sec * 1000) + (time.tv_nsec / 1000000)) + FRAME_PERIOD_MS;

    /* Loop window tick at 60 fps */
    do{
        /* Sleep the remainder of frame period */
        clock_gettime(CLOCK_REALTIME, &time);
        cur_time_ms = (time.tv_sec * 1000) + (time.tv_nsec / 1000000);

        /* How long do we need to sleept for? */
        int64_t sleep_time = wake_time_ms - cur_time_ms;
        if(sleep_time > 1){
            usleep(sleep_time * 1000);
        }
        wake_time_ms += FRAME_PERIOD_MS;

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