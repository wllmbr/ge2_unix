#include "Location.h"
#include <math.h>
#include <stdio.h>

Position::Position() {
	coordinates[0] = 0;
	coordinates[1] = 0;
}

Position::Position(double x, double y) {
	coordinates[0] = x;
	coordinates[1] = y;
}

void Position::set_position(double x, double y) {
	coordinates[0] = x;
	coordinates[1] = y;
}

double Position::calc_distance_to(const Position target) {
	double delta_x, delta_y;
	delta_x = target.coordinates[0] - coordinates[0];
	delta_y = target.coordinates[1] - coordinates[1];

	return sqrt((delta_x * delta_x) + (delta_y * delta_y));
}

Position& Position::operator= (const Position &p) {
	coordinates[0] = p.coordinates[0];
	coordinates[1] = p.coordinates[1];

	return *this;
}

bool Position::operator==(const Position &rhs) {
	bool is_equal = true;
	
	if (coordinates[0] != rhs.coordinates[0]) {
		is_equal = false;
	}
	if (coordinates[1] != rhs.coordinates[1]) {
		is_equal = false;
	}

	return is_equal;
}

bool Position::operator!=(const Position &rhs) {
	return !(*this == rhs);
}