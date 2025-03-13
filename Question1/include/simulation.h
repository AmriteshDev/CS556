#ifndef SIMULATION_H     // Prevent multiple inclusions
#define SIMULATION_H

class BankSimulation {
private:
    double total_waiting_time = 0;
    double total_time_in_system = 0;
    double total_customers_all = 0;
    double total_queue_length_all = 0;
    int max_queue_length_all = 0;
    
    double waiting_time[3] = {0}; 
    double busy_time_periods[3] = {0}; 
    double total_customers_period[3] = {0};
    double total_queue_length_period[3] = {0};
    int max_queue_length_period[3] = {0};
    int all_tellers_busy[3] = {0};

public:
    void runSimulation();   // Function to run the simulation
    void displayResults();  // Function to display results
};

#endif   //End of header guard
