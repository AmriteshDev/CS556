M/M/c Queuing System Simulation

Overview

This project simulates a bank's queuing system with a variable number of tellers throughout the day. Customers arrive based on a Poisson process, and service times follow an exponential distribution. The goal is to analyze system performance and optimize teller allocation.

File Structure

BankQueueSimulation/
│── src/
│   ├── main.cpp         # Main simulation code
│   ├── simulation.cpp   # Contains the queuing system implementation
│   ├── simulation.h     # Header file for simulation functions
│   ├── utils.cpp        # Utility functions (random number generation, etc.)
│   ├── utils.h          # Header file for utility functions
│── include/
│   ├── simulation.h     # Function declarations
│   ├── utils.h          # Utility function declarations
│── results/
│   ├── queue_length_plot.png  # Plot of queue length
│   ├── waiting_time_plot.png  # Plot of waiting times
│   ├── report.pdf      # Analysis and recommendations
│── Makefile            # Compilation instructions
│── README.md           # Project overview and instructions
│── report.md           # Findings and recommendations

Compilation Instructions

To compile the project, navigate to the project directory and run:

make

This will generate an executable named mmc_queue_sim.

Running the Simulation

After compiling, run the simulation using:

./mmc_queue_sim

The program will simulate an 8-hour workday with the following teller schedule:

2 tellers from 9:00 AM to 11:00 AM

4 tellers from 11:00 AM to 2:00 PM

3 tellers from 2:00 PM to 5:00 PM

Output Metrics

The simulation calculates and displays:

Average waiting time in the queue

Average time spent in the system

Teller utilization rate

Average number of customers in the queue

Probability of all tellers being busy

Maximum queue length

Generating Plots

To visualize results, a Python script can be used to generate plots. Install the required library:

pip install matplotlib

Then run:

python plot_results.py

Analysis & Report

After running the simulation, findings and recommendations will be summarized in report.md. This report includes insights on optimizing teller allocation to improve efficiency.

Cleaning Up

To remove compiled files, run:

make clean


