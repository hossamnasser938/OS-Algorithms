#include <stdio.h>

struct Process {
	int id;
	int arrival_time;
	int burst_time;
	int priority;
	int completion_time;
	int waiting_time;
	int turnaround_time;
};

void priorityScheduling(struct Process processes[], int n);

int main(void) {
	struct Process processes[] = { { 1, 0, 10, 2 },{ 2, 0, 5, 0 },{ 3, 0, 8, 1 } };
	int n = sizeof processes / sizeof processes[0];
	priorityScheduling(processes, n);
	return 0;
}

void priorityScheduling(struct Process processes[], int n) {
	int i, priority[n], ordered_processes[n];
	int highest_priority_process, highest_priority;
	int least_arrival;

	for (i = 0; i < n; i++) {
		priority[i] = processes[i].priority;
	}

	//Order processes based on priority. If two processes have the same priority just implement FCFS 
	for (i = 0; i < n; i++) {
		highest_priority_process = 0, highest_priority = priority[0];
		int least_arrival = processes[0].arrival_time;
		int j;
		for (j = 1; j < n; j++) {
			if (priority[j] > highest_priority) {
				highest_priority_process = j;
				highest_priority = priority[j];
				least_arrival = processes[j].arrival_time;
			}
			else if (priority[j] == highest_priority) {
				if (processes[j].arrival_time < least_arrival) {
					highest_priority_process = j;
					highest_priority = priority[j];
					least_arrival = processes[j].arrival_time;
				}
			}
		}
		priority[highest_priority_process] = -1;
		ordered_processes[i] = highest_priority_process;
	}

	//Calculate for each process completion_time, turnaround_time, and waiting_time
	int last_completion_time = 0;        //time of completion for last executed process
	int start_execution_time = 0;       //time for current process to start execution
	int process_order;
	for (i = 0; i < n; i++) {
		process_order = ordered_processes[i];
		if (processes[process_order].arrival_time <= last_completion_time) {
			start_execution_time = last_completion_time;
		}
		else {
			start_execution_time = processes[process_order].arrival_time;
		}
		last_completion_time = processes[process_order].completion_time = start_execution_time + processes[process_order].burst_time;
		processes[process_order].turnaround_time = processes[process_order].completion_time - processes[process_order].arrival_time;
		processes[process_order].waiting_time = processes[process_order].turnaround_time - processes[process_order].burst_time;
	}

	//Calculate average_waiting_time, average_turnaround_time
	double average_waiting_time, average_turnaround_time;
	for (i = 0; i < n; i++) {
		average_waiting_time += processes[i].waiting_time;
		average_turnaround_time += processes[i].turnaround_time;
	}
	average_waiting_time /= n;
	average_turnaround_time /= n;

	//Print results
	printf("Order in which process gets executed\n");
	for (i = 0; i < n; i++) {
		printf("%d ", ordered_processes[i] + 1);
	}

	printf("\n%-20s", "Processes");
	printf("%-20s", "Arrival time");
	printf("%-20s", "Burst time");
	printf("%-20s", "Waiting time");
	printf("%-20s\n", "Turn around time");

	for (i = 0; i < n; i++) {
		process_order = ordered_processes[i];
		printf("%-20d", processes[process_order].id);
		printf("%-20d", processes[process_order].arrival_time);
		printf("%-20d", processes[process_order].burst_time);
		printf("%-20d", processes[process_order].waiting_time);
		printf("%-20d\n", processes[process_order].turnaround_time);
	}

	printf("Average waiting time = %f\n", average_waiting_time);
	printf("Average turn around time = %f\n", average_turnaround_time);
}

