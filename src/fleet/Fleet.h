#pragma once

#include <stdint.h>
#include "Location.h"

#define HIT_PROBABILITY	0.75
#define SHIP_SPEED		3

class Fleet {
private:
	Position source;
	Position target;
	Position current_position;
	uint64_t traversal_time_left;
	uint64_t traversal_time;
	uint64_t ship_count;
	uint64_t next_ship_count;
	uint16_t owner_id;

public:
	Fleet();
	Fleet(Position p, uint64_t size, uint16_t oid);
	~Fleet();

	void perform_fleet_tick();
	bool engage_fleet(Fleet &attackers);
	void travel_to(Position t);
	void add_ships(uint64_t count);
	void subtract_ships(uint64_t count);
	void stage_ships(uint64_t count);
	void shore_fleet();
	void commit_fleet();

	inline Position get_source() {
		return source;
	}

	inline Position get_target() {
		return target;
	}

	inline Position get_pos(){
		return current_position;
	}

	inline uint16_t get_owner() {
		return owner_id;
	}

	inline uint64_t get_travel_time_left() {
		return traversal_time_left;
	}

	inline uint64_t get_size() {
		return ship_count;
	}

	inline void set_owner(uint16_t oid) {
		owner_id = oid;
	}

};