#include <galactic_empires.h>

void Galactic_Empires::perform_game_tick() {
	year++;
	printf("Acting on year %lu\n", year);

	/* Get input from all players */

	uint16_t i;
	for (i = 0; i < num_loaded_players; i++) {
		perform_player(i);
	}

	/* Commit player actions */

	uint64_t d, a, w;
	/* Move all fleets */
	//printf("Moving Fleets\n");
	//fflush(stdout);
	for (d = 0; d < all_fleets.size(); d++) {
		//printf("Moving fleet %llu\n", d);
		all_fleets[d].perform_fleet_tick();
	}

	/* Have each world build up its fleet */
	//printf("Building Fleets\n");
	for (w = 0; w < all_worlds.size(); w++) {
		//printf("Looking at World %llu\n", w);
		//fflush(stdout);

		/* Special case for planets that can't build */
		if(all_worlds[w].get_ship_building_capacity() == 0){
			continue;
		}

		/* Find the fleet that is stationed here */
		d = fleet_stationed(w);
		all_fleets[d].add_ships(all_worlds[w].get_ship_building_capacity());
	}

	// print_stats();

	/* Have Fleets Battle */
	/* Look at every world */
	//printf("Checking for Battles\n");
	//fflush(stdout);
	for (w = 0; w < all_worlds.size(); w++) {
		//printf("Looking at World %llu\n", w);
		//fflush(stdout);
		/* Find the fleet that is stationed here */
		d = fleet_stationed(w);

		/* Find any incoming attacking fleet */
		for (a = 0; a < all_fleets.size(); a++) {
			//printf("Looking at Attacking Fleet %llu\n", a);
			//fflush(stdout);
			//printf("Owner %d TT %llu\n World %d\n", all_fleets[d].get_owner(), all_fleets[d].get_travel_time_left(), all_worlds[w].get_owner());
			if ((all_fleets[a].get_target() == all_worlds[w].get_position()) &&
				(all_fleets[a].get_owner() != all_worlds[w].get_owner()) && 
				(all_fleets[a].get_travel_time_left() == 0)) {
				/* Battle! */
				if (!all_fleets[d].engage_fleet(all_fleets[a])) {
					/* If the defending fleet lost change the world owner */
					all_worlds[w].set_owner(all_fleets[a].get_owner());
					/* Shore the attacking fleet */
					all_fleets[a].shore_fleet();
					/* Update the defending fleet index */
					d = a;
				}
			}
		}
	}

	/* Update Fleet Status */
	for (d = 0; d < all_fleets.size(); d++) {
		/* If the fleet has stopped moving, set its target to source */
		if (all_fleets[d].get_travel_time_left() == 0) {
			all_fleets[d].shore_fleet();
		}

		/* If two fleets are in the same world, merge them */
		for(w = 0; w < all_worlds.size(); w++){
			uint64_t first_stationed;
			first_stationed = fleet_stationed(w);
			if ((all_fleets[d].get_source() == all_worlds[w].get_position()) &&
				(all_fleets[d].get_owner() == all_worlds[w].get_owner()) &&
				(all_fleets[d].get_travel_time_left() == 0)
			) {
				/* D is also stationed at w */
				if(first_stationed != d){
					printf("Reinforcing world %ld with %ld ships\n", w, all_fleets[d].get_size());
					/* Merge d into first_stationed */
					all_fleets[first_stationed].add_ships(all_fleets[d].get_size());
					all_fleets[d].subtract_ships(all_fleets[d].get_size());
				}
			}
		}

		/* If the fleet size is 0, destroy the reference to the fleet */
		if (all_fleets[d].get_size() == 0){
			all_fleets.erase(all_fleets.begin()+d);
			d--;
		}
	}

	/* Check if the game should end */
	is_galactic_empire();
}