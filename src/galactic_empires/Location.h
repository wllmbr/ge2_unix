#pragma once

class Position {
private:
	double coordinates[2];

public:
	Position();
	Position(double x, double y);
	void set_postition(double x, double y);
	double calc_distance_to(const Position target);

	Position& operator= (const Position &p);
	bool operator==(const Position &rhs);
	bool operator!=(const Position &rhs);

	inline double get_x(void) {
		return coordinates[0];
	}

	inline double get_y(void) {
		return coordinates[1];
	}

};