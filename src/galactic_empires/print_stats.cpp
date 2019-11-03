#include <galactic_empires.h>

void Galactic_Empires::print_stats() {
	uint64_t w,d;
	printf("World  Owner  Ships  Capacity\n");
	for (w = 0; w < all_worlds.size(); w++) {
		uint64_t	fleet_size;
		uint16_t	oid;
		uint64_t	build_cap;
		/* Make sure that the world has a owner*/
		if (all_worlds[w].get_owner() == DEFAULT_OWNER) {
			printf("%5lu      ?      ?         ?\n",w);
			continue;
		}
		/* Populate World Data */
		
		/* Find the fleet that is stationed here */
		d = fleet_stationed(w);

		fleet_size = all_fleets[d].get_size();
		oid = all_worlds[w].get_owner();
		build_cap = all_worlds[w].get_ship_building_capacity();
		printf("%5lu  %5d  %5lu  %8lu\n", w, oid, fleet_size, build_cap);
	}
}