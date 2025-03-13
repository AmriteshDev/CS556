#include "simulation.h"
#include "utils.h"
#include <iostream>
#include <queue>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct Customer {
    double arrival_time;
    double service_start;
    double service_time;
};

void BankSimulation::runSimulation() {
    double current_time = 0.0;
    double closing_time = 8 * 60; // 8-hour workday in minutes
    queue<Customer> queue;
    vector<double> next_service(4, 0); // Maximum 4 tellers

    double lambda = 40.0 / 60.0; // 40 customers per hour → per minute
    double mu = 1.0 / 4.0;       // 4 minutes per customer → service rate

    double next_arrival = expRandom(lambda);
    int tellers = 2; // Start with 2 tellers

    int period = 0;

    while (current_time < closing_time) {
        // Update teller count based on time
        if (current_time < 120) 
            period = 0, tellers = 2;
        else if (current_time < 180) 
            period = 1, tellers = 4;
        else 
            period = 2, tellers = 3;

        if (next_arrival < *min_element(next_service.begin(), next_service.begin() + tellers)) {
            // New customer arrives
            current_time = next_arrival;
            Customer c;
            c.arrival_time = current_time;
            c.service_time = expRandom(mu);
            queue.push(c);
            next_arrival = current_time + expRandom(lambda);
        } else {
            // Serve a customer
            int teller_idx = distance(next_service.begin(), min_element(next_service.begin(), next_service.begin() + tellers));
            current_time = next_service[teller_idx];
            
            if (!queue.empty()) {
                Customer c = queue.front();
                queue.pop();
                c.service_start = current_time;
                next_service[teller_idx] = current_time + c.service_time;

                // Update statistics
                double wait_time = c.service_start - c.arrival_time;
                double time_in_system = wait_time + c.service_time;

                waiting_time[period] += wait_time;
                busy_time_periods[period] += c.service_time;
                total_customers_period[period]++;
            }
        }

        total_queue_length_period[period] += queue.size();
        max_queue_length_period[period] = max(max_queue_length_period[period], (int)queue.size());
        
        if ((int)queue.size() >= tellers) 
            all_tellers_busy[period]++;
    }

    // Store final statistics
    total_waiting_time = waiting_time[0] + waiting_time[1] + waiting_time[2];
    total_time_in_system = total_waiting_time + busy_time_periods[0] + busy_time_periods[1] + busy_time_periods[2];
    total_customers_all = total_customers_period[0] + total_customers_period[1] + total_customers_period[2];
    total_queue_length_all = total_queue_length_period[0] + total_queue_length_period[1] + total_queue_length_period[2];
    max_queue_length_all = max({max_queue_length_period[0], max_queue_length_period[1], max_queue_length_period[2]});
}

void BankSimulation::displayResults() {
    cout << "Simulation Results:\n";
    cout << "-----------------------------\n";
    for (int i = 0; i < 3; i++) {
        cout << "Period " << i + 1 << ":\n";
        cout << "  Avg Waiting Time: " << (total_customers_period[i] > 0 ? waiting_time[i] / total_customers_period[i] : 0) << " minutes\n";
        cout << "  Teller Utilization: " << (busy_time_periods[i] / (120.0 * (i == 1 ? 4 : 3))) * 100 << "%\n";
        cout << "  Max Queue Length: " << max_queue_length_period[i] << "\n";
        cout << "  Probability All Tellers Busy: " << (all_tellers_busy[i] / 120.0) * 100 << "%\n";
        cout << "-----------------------------------\n";
    }

    cout << "\nOverall Simulation Statistics:\n";
    cout << "-----------------------------------\n";
    cout << "Total Customers Served: " << total_customers_all << "\n";
    cout << "Avg Time in System: " << (total_customers_all > 0 ? total_time_in_system / total_customers_all : 0) << " minutes\n";
    cout << "Max Queue Length Overall: " << max_queue_length_all << "\n";
}
