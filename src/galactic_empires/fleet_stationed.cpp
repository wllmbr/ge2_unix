#include <galactic_empires.h>

uint64_t Galactic_Empires::fleet_stationed(uint64_t world) {
	uint64_t d;
	/* Find the fleet that is stationed here */
	for (d = 0; d < all_fleets.size(); d++) {
		//printf("Looking at Fleet %llu\n", d);
		//fflush(stdout);
		if ((all_fleets[d].get_source() == all_worlds[world].get_position()) &&
			(all_fleets[d].get_owner() == all_worlds[world].get_owner()) &&
			(all_fleets[d].get_travel_time_left() == 0)
			) {
			break;
		}
	}

	if (d == all_fleets.size()) {
		printf("Warning! No fleet is stationed at %lu\n", world);
		printf("Game will now soft lock\n");
		while (1);
	}

	return d;
}