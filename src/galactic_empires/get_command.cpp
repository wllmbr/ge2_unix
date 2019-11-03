#include <galactic_empires.h>

void Galactic_Empires::get_command(uint16_t id) {

	uint64_t source_num			= 0xffffffffffffffff;
	uint64_t destination_num	= 0xffffffffffffffff;
	uint64_t size_num			= 0xffffffffffffffff;

	/* Ask for source world */
	printf("Fleet from World: ");
	scanf("%lu", &source_num);

	/* Scrub input */
	if (source_num >= all_worlds.size()) {
		printf("Invalid world number! %lu\n", source_num);
		return;
	}

	if (all_worlds[source_num].get_owner() != id) {
		printf("You don't own that world!\n");
		return;
	}

	/* Ask for destination world */
	printf("Going to World: ");
	scanf("%lu", &destination_num);

	/* Scrub input */
	if (destination_num >= all_worlds.size()) {
		printf("Invalid world number!\n");
		return;
	}

	/* Get the fleet size */
	uint64_t d;
	d = fleet_stationed(source_num);

	printf("Fleet size: ");
	scanf("%lu", &size_num);

	if (size_num > all_fleets[d].get_size()) {
		printf("Not enough ships left!\n");
		return;
	}
	//printf("Sending %llu ships from world %llu to world %llu\n", size_num, source_num, destination_num);

	/* Commit the fleet */
	all_fleets[d].subtract_ships(size_num);

	Fleet new_fleet(
		all_worlds[source_num].get_position(),
		size_num,
		all_worlds[source_num].get_owner()
	);

	new_fleet.travel_to(all_worlds[destination_num].get_position());

	all_fleets.push_back(new_fleet);

}