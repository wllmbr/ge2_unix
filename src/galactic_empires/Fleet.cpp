#include "Fleet.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

Fleet::Fleet() {
	source = Position(0, 0);
	target = Position(0, 0);
	traversal_time_left = 0;
	ship_count = 10;
	owner_id = 0;
}

Fleet::Fleet(Position p, uint64_t size, uint16_t oid) {
	source = p;
	target = p;
	traversal_time_left = 0;
	ship_count = size;
	owner_id = oid;
}

Fleet::~Fleet()
{
}

void Fleet::perform_fleet_tick() {
	/* If the fleet is moving, count down the travel counter*/
	//printf("Fleet Tick\n");
	if (traversal_time_left > 0) {
		traversal_time_left--;
		//printf("Fleet is %lu ticks away\n", traversal_time_left);
	}
}


bool Fleet::engage_fleet(Fleet &attackers) {
	/* Reseed the random number generator */
	srand(time(0));
	printf("Fleet Admiral %d attacks with %lu ships!\n", attackers.owner_id, attackers.ship_count);
	printf("Fleet Admiral %d defends with %lu ships!\n", owner_id, ship_count);
	/* Can the fleets actually battle eachother? */
	while ((ship_count != 0) && (attackers.ship_count != 0)) {
		uint64_t i;
		double roll;
		/* Let the defenders attack first */
		for (i = 0; i < ship_count; i++) {
			uint64_t r = rand();
			roll = ((double)r) / RAND_MAX;
			if (roll < HIT_PROBABILITY) {
				/* We had a hit! */
				if (attackers.ship_count > 0) {
					attackers.ship_count--;
					printf("X");
				}
			}
			if (attackers.ship_count == 0) {
				break;
			}
		}
		printf("\n");
		/* Now for the attacker's turn */
		for (i = 0; i < attackers.ship_count; i++) {
			uint64_t r = rand();
			double roll = ((double)r) / RAND_MAX;
			if (roll < HIT_PROBABILITY) {
				/* We had a hit! */
				if (ship_count > 0) {
					ship_count--;
					printf("+");
				}
			}
			if (ship_count == 0) {
				break;
			}
			/* Fuck you Windows */
			#ifdef __WIN32
			Sleep(100);
			#else
			sleep(100);
			#endif
		}
		printf("\n");
	}

	/* Check who won */
	if (ship_count == 0) {
		printf(
			"Fleet Admiral %d Wins!\n%lu Ships Remain\n",
			attackers.owner_id,
			attackers.ship_count
		);
		return false;
	} else {
		printf(
			"Fleet Admiral %d Wins!\n%lu Ships Remain\n",
			owner_id,
			ship_count
		);
		return true;
	}

}


void Fleet::travel_to(Position t) {
	target = t;
	//printf("Sending Fleet to position %f %f\n", target.get_x(), target.get_y());
	double distance = source.calc_distance_to(target);
	traversal_time_left = (uint64_t)distance;
	//printf("Calculated distance of %f, saving distance of %lu\n", distance, traversal_time_left);
}


void Fleet::add_ships(uint64_t count) {
	ship_count += count;
}

void Fleet::subtract_ships(uint64_t count) {
	ship_count -= count;
}

void Fleet::shore_fleet() {
	source = target;
}