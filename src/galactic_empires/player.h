#pragma once
#include <vector>
#include <stdint.h>

struct player_action {
	uint64_t	source_world;
	uint64_t	num_ships;
	uint64_t	target_world;
};