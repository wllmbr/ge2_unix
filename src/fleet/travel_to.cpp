#include <Fleet.h>
#include <Location.h>

void Fleet::travel_to(Position t) {
	target = t;
	double distance 	= source.calc_distance_to(target);
	traversal_time_left = (uint64_t)(distance / SHIP_SPEED);
	traversal_time 		= traversal_time_left;
}