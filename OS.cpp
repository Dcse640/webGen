#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;               // Process ID
    int burst_time;       // Burst time (execution time)
    int arrival_time;     // Arrival time
    int waiting_time;     // Waiting time
    int turnaround_time;  // Turnaround time
    int compilation_time; // Time when the process starts executing
    int response_time;    // Time from arrival to first execution
};

// Function to calculate waiting time, compilation time, response time, and turnaround time
void calculateTimes(vector<Process>& processes) {
    int current_time = 0; // Track the current time when CPU is available

    for (int i = 0; i < processes.size(); i++) {
        // If the process arrives after the current time, update the current time
        if (processes[i].arrival_time > current_time) {
            current_time = processes[i].arrival_time;
        }

        // Compilation time (start time) is when the process starts executing
        processes[i].compilation_time = current_time;

        // Response time = start time - arrival time
        processes[i].response_time = processes[i].compilation_time - processes[i].arrival_time;

        // Update current time after process finishes
        current_time += processes[i].burst_time;

        // Waiting time is the time before a process starts execution
        processes[i].waiting_time = processes[i].compilation_time - processes[i].arrival_time;

        // Turnaround time = waiting time + burst time
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

// Function to sort processes by arrival time, and then by burst time (Shortest Job First)
bool compareArrivalAndBurstTime(Process a, Process b) {
    if (a.arrival_time == b.arrival_time)
        return a.burst_time < b.burst_time; // If arrival time is the same, use burst time for sorting
    return a.arrival_time < b.arrival_time; // Otherwise, use arrival time
}

int main() {
    int n;
    
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input for each process
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burst_time;
    }

    // Sort processes based on arrival time and burst time (Shortest Job First)
    sort(processes.begin(), processes.end(), compareArrivalAndBurstTime);

    // Calculate waiting time, turnaround time, compilation time, and response time
    calculateTimes(processes);

    // Calculate total time (finish time of the last process)
    int total_time = processes[processes.size() - 1].compilation_time + processes[processes.size() - 1].burst_time;

    // Calculate throughput
    float throughput = (float)n / total_time;

    // Output the results
    cout << "\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompilation Time\tResponse Time\n";
    float total_waiting_time = 0, total_turnaround_time = 0, total_response_time = 0;
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t" << processes[i].arrival_time << "\t\t"
             << processes[i].burst_time << "\t\t" << processes[i].waiting_time << "\t\t"
             << processes[i].turnaround_time << "\t\t" << processes[i].compilation_time << "\t\t\t"
             << processes[i].response_time << endl;
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        total_response_time += processes[i].response_time;
    }

    // Average waiting time, turnaround time, and response time
    cout << "\nAverage Waiting Time: " << (total_waiting_time / n) << endl;
    cout << "Average Turnaround Time: " << (total_turnaround_time / n) << endl;
    cout << "Average Response Time: " << (total_response_time / n) << endl;

    // Throughput
    cout << "\nThroughput: " << throughput << " processes per unit time" << endl;

    return 0;
}

