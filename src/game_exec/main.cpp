#include <stdlib.h>
#include <Fleet.h>
#include <galactic_empires.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <window.h>

int main(void) {

    pthread_t window_thread_handle;
    Window game_screen;
    
    /* Create game */
    Galactic_Empires game;
    srand(time(0));
    game.print_map();
    //game.print_stats();
    game.add_player("wllmbr");

    game_screen.install_galaxy(&game);

    pthread_create(&window_thread_handle,NULL,window_thread,(void*)&game_screen);

    do {
        game.perform_game_tick();
    } while (!(game.exit_game));
    
    printf("Press return to exit\n");
    char dummy = getchar();
    /* Make GCC shut the fuck up about unused variables */
    dummy++;

}