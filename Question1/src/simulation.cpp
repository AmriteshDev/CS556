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
    double closing_time = 8 * 60; // Bank operates for 8 hours (480 minutes)
    queue<Customer> customer_queue; // Queue to hold waiting customers
    vector<double> teller_available_time(4, 0); // Next available time for each teller (max 4 tellers)

    double customer_arrival_rate = 40.0 / 60.0; // 40 customers per hour → per minute
    double service_rate = 1.0 / 4.0;       // 4 minutes per customer → service rate

    double next_customer_arrival = expRandom(customer_arrival_rate); // Time when next customer arrives
    int active_tellers = 2; // Start with 2 tellers
    int time_period = 0; // Track which time period (morning, peak, evening)

    while (current_time < closing_time) {
        // Step 1: Adjust Teller Count Based on Time
        if (current_time < 120) { // 9:00 AM - 11:00 AM → 2 tellers
            time_period = 0;
            active_tellers = 2;
        } else if (current_time < 180) { // 11:00 AM - 2:00 PM → 4 tellers (peak hours)
            time_period = 1;
            active_tellers = 4;
        } else { // 2:00 PM - 5:00 PM → 3 tellers
            time_period = 2;
            active_tellers = 3;
        }

        // Step 2: Find the earliest available teller
        double earliest_teller_free_time = teller_available_time[0];
        int earliest_teller_index = 0;

        for (int i = 1; i < active_tellers; i++) { // Check only the working tellers
            if (teller_available_time[i] < earliest_teller_free_time) {
                earliest_teller_free_time = teller_available_time[i];
                earliest_teller_index = i;
            }
        }

        // Step 3: Check if a new customer arrives before any teller is free
        if (next_customer_arrival < earliest_teller_free_time) {
            // A new customer arrives before any teller is available
            current_time = next_customer_arrival;
            Customer new_customer;
            new_customer.arrival_time = current_time;
            new_customer.service_time = expRandom(service_rate);
            customer_queue.push(new_customer);
            next_customer_arrival = current_time + expRandom(customer_arrival_rate);
        } else {
            // A teller becomes free
            current_time = earliest_teller_free_time;

            if (!customer_queue.empty()) {
                Customer current_customer = customer_queue.front();
                customer_queue.pop();
                current_customer.service_start = current_time;
                teller_available_time[earliest_teller_index] = current_time + current_customer.service_time;

                // Step 4: Update statistics
                double wait_time = current_customer.service_start - current_customer.arrival_time;
                waiting_time[time_period] += wait_time;
                busy_time_periods[time_period] += current_customer.service_time;
                total_customers_period[time_period]++;
            }
        }

        // Step 5: Update queue statistics
        total_queue_length_period[time_period] += customer_queue.size();
        max_queue_length_period[time_period] = max(max_queue_length_period[time_period], (int)customer_queue.size());

        if ((int)customer_queue.size() >= active_tellers)
            all_tellers_busy[time_period]++;
    }

    // Step 6: Compute final statistics
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
