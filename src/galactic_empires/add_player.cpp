#include <galactic_empires.h>

uint16_t Galactic_Empires::add_player(std::string player_name) {
	if (num_loaded_players >= MAX_PLAYER_COUNT) {
		printf("Waring: The maximum number of players has already been entered\n");
		return 0xffff;
	}
	players[num_loaded_players] = player_name;
	num_loaded_players++;

	/* Assign a world to the player */
	uint64_t d;
	d = fleet_stationed(num_loaded_players - 1);
	all_worlds[num_loaded_players - 1].set_owner(num_loaded_players - 1);
	all_fleets[d].set_owner(num_loaded_players - 1);
	all_worlds[d].set_ship_building_capacity(10);

	return num_loaded_players - 1;
}