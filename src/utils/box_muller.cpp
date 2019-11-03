#include <box_muller.h>

#include <math.h>
#include <stdlib.h>
#include <time.h>


double gaussian(double mu, double sigma){

    /* Reseed RNG */
    // srand(time(0));

    double u1, u2, z;
    u1 = ((double)rand()) / RAND_MAX;
    u2 = ((double)rand()) / RAND_MAX;

    z = sqrt( -2.0 * log(u1)) * cos(2.0 *3.14159 * u2);

    return (z * sigma) + mu;

}