#include "world.h"
#include <box_muller.h>
#include <stdio.h>

World::World() {
	pos = Position(0, 0);
	//srand(time(0));
	// ship_building_capacity = (rand() % (MAX_DEFAULT_SHIP_BUILDING - MIN_DEFAULT_SHIP_BUILDING)) + MIN_DEFAULT_SHIP_BUILDING;
	uint8_t r;
	do{
		r = static_cast<uint8_t>(gaussian(RANGE_DEFAULT_SHIP_BUILDING / 4, STD_DEV_DEFAULT_SHIP_BUILDING));
		r += MIN_DEFAULT_SHIP_BUILDING;
		printf("Made capacity %u\n", r);
	}while(r >= MAX_DEFAULT_SHIP_BUILDING);

	ship_building_capacity = r;
	printf("World has capacity %lu\n", ship_building_capacity);
}

World::World(Position p, uint16_t oid) {
	pos = p;
	owner_id = oid;
	//srand(time(0));
	// ship_building_capacity = (rand() % (MAX_DEFAULT_SHIP_BUILDING - MIN_DEFAULT_SHIP_BUILDING)) + MIN_DEFAULT_SHIP_BUILDING;
	uint8_t r;
	do{
		r = static_cast<uint8_t>(gaussian(RANGE_DEFAULT_SHIP_BUILDING / 4, STD_DEV_DEFAULT_SHIP_BUILDING));
		r+= MIN_DEFAULT_SHIP_BUILDING;
	}while(r >= MAX_DEFAULT_SHIP_BUILDING);

	ship_building_capacity = r;
	printf("World has capacity %lu\n", ship_building_capacity);
}