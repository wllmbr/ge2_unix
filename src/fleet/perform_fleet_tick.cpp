#include <Fleet.h>
#include <Location.h>

void Fleet::perform_fleet_tick() {
	/* If the fleet is moving, count down the travel counter*/
	//printf("Fleet Tick\n");
	if (traversal_time_left > 0) {
		traversal_time_left--;
		//printf("Fleet is %lu ticks away\n", traversal_time_left);

		/* We're moving the fleet so update its position */

		double distance = source.calc_distance_to(target);
		double percent_traveled = (distance - traversal_time_left) / distance;

		double x_travel = ((target.get_x() - source.get_x()) * percent_traveled);
		double y_travel = ((target.get_y() - source.get_y()) * percent_traveled);

		current_position.set_position(x_travel + source.get_x(), y_travel + source.get_y());

	}

	next_ship_count = ship_count;
}