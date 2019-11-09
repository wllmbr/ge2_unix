#include "galactic_empires.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

Galactic_Empires::Galactic_Empires() {
	num_loaded_players = 0;
	year = 0;

	/* Test Universe */

	/* Make 50 worlds */
	srand(time(0));
	uint64_t i,w;
	for (i = 0; i < 20; i++) {
		Position new_pos;
		bool valid_spot = true;
		do{
			valid_spot = true;
			new_pos.set_position(
				(double)(rand() % MAP_DIMENSIONS_X),
				(double)(rand() % MAP_DIMENSIONS_Y)
			);
			/* Check to make sure no existing worlds have these coordinates */
			for (w = 0; w < all_worlds.size(); w++) {
				if (new_pos == all_worlds[w].get_position()) {
					valid_spot = false;
					break;
				}
			}
		} while (!valid_spot);
		World new_world(new_pos, DEFAULT_OWNER);
		/* Make a new fleet for this world */
		Fleet new_fleet(new_pos, 10, DEFAULT_OWNER);

		all_worlds.push_back(new_world);
		all_fleets.push_back(new_fleet);
	}

	exit_game = false;
}

Galactic_Empires::~Galactic_Empires()
{
	printf("Galaxy being destroyed\n");
	fflush(stdout);
}