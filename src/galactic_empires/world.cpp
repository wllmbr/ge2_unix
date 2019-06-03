#include "world.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

World::World() {
	pos = Position(0, 0);
	//srand(time(0));
	ship_building_capacity = (rand() % (MAX_DEFAULT_SHIP_BUILDING - MIN_DEFAULT_SHIP_BUILDING)) + MIN_DEFAULT_SHIP_BUILDING;
	//printf("World has capacity %lld\n", ship_building_capacity);
}

World::World(Position p, uint16_t oid) {
	pos = p;
	owner_id = oid;
	//srand(time(0));
	ship_building_capacity = (rand() % (MAX_DEFAULT_SHIP_BUILDING - MIN_DEFAULT_SHIP_BUILDING)) + MIN_DEFAULT_SHIP_BUILDING;
	//printf("World has capacity %lld\n", ship_building_capacity);
}