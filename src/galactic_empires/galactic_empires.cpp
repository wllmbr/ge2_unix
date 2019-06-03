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
			new_pos.set_postition(
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
}

Galactic_Empires::~Galactic_Empires()
{

}

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


	return num_loaded_players - 1;
}

void Galactic_Empires::perform_game_tick() {
	year++;
	printf("Acting on year %lu\n", year);

	/* Get input from all players */

	uint16_t i;
	for (i = 0; i < num_loaded_players; i++) {
		perform_player(i);
	}

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

		/* If the fleet size is 0, destroy the reference to the fleet */
		if (all_fleets[d].get_size() == 0){
			all_fleets.erase(all_fleets.begin()+d);
			d--;
		}
	}
}

void Galactic_Empires::print_map() {
	uint8_t frame_buffer[MAP_DIMENSIONS_X][MAP_DIMENSIONS_Y];
	uint16_t r, c;
	for (r = 0; r < MAP_DIMENSIONS_Y; r++) {
		for (c = 0; c < MAP_DIMENSIONS_X; c++) {
			frame_buffer[c][r] = 0xff;
		}
	}
	uint64_t w;
	for (w = 0; w < all_worlds.size(); w++) {
		uint16_t x, y;
		x = (uint16_t)all_worlds[w].get_position().get_x();
		y = (uint16_t)all_worlds[w].get_position().get_y();

		frame_buffer[x][y] = w;
	}

	printf("\n============================================= STAR MAP =============================================\n");

	for (r = 0; r < MAP_DIMENSIONS_Y; r++) {
		printf("\n");
		for (c = 0; c < MAP_DIMENSIONS_X; c++) {
			if (frame_buffer[c][r] != 0xff) {
				printf("%3d |", frame_buffer[c][r]);
			} else {
				printf("    |");
			}
		}
	}
	printf("\n");
}

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

void Galactic_Empires::perform_player(uint16_t id) {
	char command;
	printf("Player %d\n", id);
	while(1){
		/* Get single key stroke */
		command = getchar();
		switch (command) {
			case '\n':
				printf("Ending Turn");
				return;
				break;
			case 'M':
			case 'm':
				print_map();
				break;
			case 'C':
			case 'c':
				get_command(id);
				break;
			case 'S':
			case 's':
				print_stats();
				break;
			case 'H':
			case 'h':
			default:
				printf("Valid commands are\nh: Get Help\nm: display map\ns: Display Galaxy Stats\nc: create mission\nEnter: End Turn\n");
		}
		/* Clear the newline */
		command = getchar();
	}
}

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

bool Galactic_Empires::is_galactic_empire() {
	/* Look at the owner of every world, if they're all the same, the game is over*/
	bool has_won = true;
	uint16_t winner_id = all_worlds[0].get_owner();
	for (uint16_t i = 0; i < all_worlds.size(); i++) {
		if (all_worlds[i].get_owner() != winner_id) {
			has_won = false;
		}
	}

	if (has_won) {
		printf("Fleet Admiral %d controls the Galaxy!\n", winner_id);
		return true;
	}
	else {
		return false;
	}

}
