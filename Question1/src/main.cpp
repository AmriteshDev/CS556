#include "simulation.h"
#include <iostream>

int main() {
    BankSimulation sim;  // initializes a BankSimulation object
    sim.runSimulation();   //to execute the queue model.

    sim.displayResults();  //to print the results.
    return 0;
}