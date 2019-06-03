#include <stdio.h>
#include <stdlib.h>
#include "Fleet.h"
#include "galactic_empires.h"
#include <time.h>
#include <stdio.h>

int main(void) {
	/* Create game */
	srand(time(0));
	Galactic_Empires game;
	game.print_map();
	//game.print_stats();
	game.add_player("wllmbr");

	do {
		game.perform_game_tick();
	} while (!(game.is_galactic_empire()));
	
	printf("Press return to exit\n");
	char dummy = getchar();
	/* Make GCC shut the fuck up about unused variables */
	dummy++;

}