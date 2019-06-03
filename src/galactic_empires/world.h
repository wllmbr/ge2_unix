#pragma once
#include "Location.h"
#include "stdint.h"

#define MAX_DEFAULT_SHIP_BUILDING	20
#define MIN_DEFAULT_SHIP_BUILDING	10

class World {
private:
	Position	pos;
	uint64_t	ship_building_capacity;
	uint16_t	owner_id;
public:
	World();
	World(Position p, uint16_t oid);

	inline void set_owner(uint16_t oid) {
		owner_id = oid;
	}

	inline uint16_t get_owner() {
		return owner_id;
	}

	inline uint64_t get_ship_building_capacity() {
		return ship_building_capacity;
	}

	inline Position get_position() {
		return pos;
	}


};