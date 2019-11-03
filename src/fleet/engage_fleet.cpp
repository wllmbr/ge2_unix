#include <Fleet.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

void battle_engine(uint64_t &atk, uint64_t &def){
	uint64_t i;
	for(i = 0; i < atk; i++){
		double roll = ((double)rand()) / RAND_MAX;
		if(roll < 0.06) {
			def--;
		} else {
			/* Calculate collateral damage */
			double collateral = 0.41 * ((double)def / (def + atk));
			if(roll < collateral){
				def--;
			}
		}
		if(def == 0){
			return;
		}
	}
}

bool Fleet::engage_fleet(Fleet &attackers) {
	/* Reseed the random number generator */
	srand(time(0));
	printf("Fleet Admiral %d attacks with %lu ships!\n", attackers.owner_id, attackers.ship_count);
	printf("Fleet Admiral %d defends with %lu ships!\n", owner_id, ship_count);
	/* Can the fleets actually battle eachother? */
	while ((ship_count != 0) && (attackers.ship_count != 0)) {
		/* Have the defenders fire first */
		battle_engine(ship_count, attackers.ship_count);
		/* Check if they lost */
		if(attackers.ship_count == 0){
			break;
		}

		/* Next up, the Attackers */
		battle_engine(attackers.ship_count, ship_count);
		/* Check if we lost */
		if(ship_count == 0){
			break;
		}
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