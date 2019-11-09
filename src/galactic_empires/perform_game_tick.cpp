#include <galactic_empires.h>

void Galactic_Empires::perform_game_tick() {

	/* Check if the game engine needs to run */
	if(perform_year == false){
		return;
	}
	perform_year = false;
	year++;

	uint64_t d, a, w;
	/* Move all fleets */
	for (d = 0; d < all_fleets.size(); d++) {
		all_fleets[d].perform_fleet_tick();
	}

	/* Have each world build up its fleet */
	for (w = 0; w < all_worlds.size(); w++) {

		/* Special case for planets that can't build */
		if(all_worlds[w].get_ship_building_capacity() == 0){
			continue;
		}

		/* Find the fleet that is stationed here */
		d = fleet_stationed(w);
		all_fleets[d].add_ships(all_worlds[w].get_ship_building_capacity());
	}

	/* Have Fleets Battle */
	/* Look at every world */
	for (w = 0; w < all_worlds.size(); w++) {
		/* Find the fleet that is stationed here */
		d = fleet_stationed(w);

		/* Find any incoming attacking fleet */
		for (a = 0; a < all_fleets.size(); a++) {
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