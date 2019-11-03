#include <Fleet.h>
#include <Location.h>

void Fleet::travel_to(Position t) {
	target = t;
	//printf("Sending Fleet to position %f %f\n", target.get_x(), target.get_y());
	double distance = source.calc_distance_to(target);
	traversal_time_left = (uint64_t)distance;
	//printf("Calculated distance of %f, saving distance of %lu\n", distance, traversal_time_left);
}