#include "utils.h"
#include <cmath>
#include <cstdlib>

// Generates exponentially distributed random numbers 
double expRandom(double rate) {
    double u = (double) rand() / RAND_MAX;
    return -log(1 - u) / rate;
}