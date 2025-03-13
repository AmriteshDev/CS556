#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <cmath>

// Function to generate exponential random number 
inline double expRandom(double lambda) {
    return -log(1.0 - ((double)rand() / RAND_MAX)) / lambda;
}

#endif // UTILS_H
