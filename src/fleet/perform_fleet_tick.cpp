#include <Fleet.h>
#include <Location.h>

void Fleet::perform_fleet_tick() {
	/* If the fleet is moving, count down the travel counter*/
	if (traversal_time_left > 0) {
		traversal_time_left--;

		/* We're moving the fleet so update its position */
		double percent_left = ((double)traversal_time - (double)traversal_time_left) / (double)traversal_time;

		double x_travel = ((target.get_x() - source.get_x()) * percent_left);
		double y_travel = ((target.get_y() - source.get_y()) * percent_left);

		current_position.set_position(x_travel + source.get_x(), y_travel + source.get_y());

	}

	next_ship_count = ship_count;
}