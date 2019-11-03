#include "Fleet.h"
#include <Location.h>


Fleet::Fleet() {
	source = Position(0, 0);
	target = Position(0, 0);
	current_position = Position(0,0);
	traversal_time_left = 0;
	ship_count = 10;
	owner_id = 0;
}

Fleet::Fleet(Position p, uint64_t size, uint16_t oid) {
	source = p;
	target = p;
	current_position = p;
	traversal_time_left = 0;
	ship_count = size;
	owner_id = oid;
}

Fleet::~Fleet()
{
}






