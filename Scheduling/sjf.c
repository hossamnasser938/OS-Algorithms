#include <stdio.h>

#define NUMBER_OF_PROCESSES 4

int processes_ids[NUMBER_OF_PROCESSES];
int processes_execution_order[NUMBER_OF_PROCESSES];

int arrival_time[NUMBER_OF_PROCESSES];
int completion_time[NUMBER_OF_PROCESSES];
int burst_time[NUMBER_OF_PROCESSES];
int turnaround_time[NUMBER_OF_PROCESSES];
int waiting_time[NUMBER_OF_PROCESSES];

double average_turnaround_time;
double average_waiting_time;

int find_process_with_least_arrival_time(int _arrival_time[], int n);
int find_shortest_job_process(int _arrival_time[], int _burst_time[], int n, int last_completion_time);
void calculate_completion_time();
void calculate_turnaround_time();
void calculate_waiting_time();
void calculate_average_turnaround_time();
void calculate_average_waiting_time();
void calculate_and_print();

int main(void){
    processes_ids[0] = 1;
    processes_ids[1] = 2;
    processes_ids[2] = 3;
    processes_ids[3] = 4;
    
    arrival_time[0] = arrival_time[1] = arrival_time[2] = arrival_time[3] = 0;
    
    burst_time[0] = 6;
    burst_time[1] = 8;
    burst_time[2] = 7;
    burst_time[3] = 3;
    
    average_turnaround_time = 0;
    average_waiting_time = 0;
    calculate_and_print();
    return 0;
}

int find_process_with_least_arrival_time(int _arrival_time[], int n) {
	int i, position = 0, least = _arrival_time[0];
	for (i = 1; i < n; i++) {
		if (_arrival_time[i] < least) {
			least = _arrival_time[i];
			position = i;
		}
	}
	return position;
}

int find_shortest_job_process(int _arrival_time[], int _burst_time[], int n, int last_completion_time){
    int i, j, position = 0, shortest = _burst_time[0];
    for(i = 1; i < n; i++){
        if(_arrival_time[i] <= last_completion_time){
            for(j = 1; j < n; j++){
                if(_arrival_time[j] <= last_completion_time && _burst_time[j] < shortest){
                    shortest = _burst_time[j];
                    position = j;
                }
            }
        }
        else{
            int least = find_process_with_least_arrival_time(_arrival_time , NUMBER_OF_PROCESSES);
            for(j = 1; j < n; j++){
                if(_arrival_time[j] == least && _burst_time[j] < shortest){
                    shortest = _burst_time[j];
                    position = j;
                }
            }
        }
    }
    
    return position;
}

void calculate_completion_time(){
    int _burst_time[NUMBER_OF_PROCESSES];
    int _arrival_time[NUMBER_OF_PROCESSES];
    
    int i;
    for(i = 0; i < NUMBER_OF_PROCESSES; i++){
        _burst_time[i] = burst_time[i]; 
        _arrival_time[i] = arrival_time[i];
    }
    
    int shortest_position = 0;        //position of shortest job process
    int last_completion_time = 0;     //time of completion for last executed process
    int start_execution_time = 0;       //time for current process to start execution
    for(i = 0; i < NUMBER_OF_PROCESSES; i++){
        shortest_position = find_shortest_job_process(_arrival_time, _burst_time, NUMBER_OF_PROCESSES, last_completion_time);
        processes_execution_order[i] = shortest_position + 1;
        
        if(last_completion_time > arrival_time[shortest_position]){
            start_execution_time = last_completion_time;
        }
        else{
            start_execution_time = arrival_time[shortest_position];
        }
        
        last_completion_time = completion_time[shortest_position] = start_execution_time + burst_time[shortest_position];
        _burst_time[shortest_position] = 2147483647;       //Use a big number to prevent choosing this process again as least arrival time
        _arrival_time[shortest_position] = 2147483647;
    }
}

void calculate_turnaround_time(){
    int i;
    for(i = 0; i < NUMBER_OF_PROCESSES; i++){
        turnaround_time[i] = completion_time[i] - arrival_time[i];
    }
}

void calculate_waiting_time(){
    int i;
    for(i = 0; i < NUMBER_OF_PROCESSES; i++){
        waiting_time[i] = turnaround_time[i] - burst_time[i];
    }
}

void calculate_average_turnaround_time(){
    int i;
    for(i = 0; i < NUMBER_OF_PROCESSES; i++){
        average_turnaround_time += turnaround_time[i];    
    }
    average_turnaround_time /= NUMBER_OF_PROCESSES;  
}

void calculate_average_waiting_time(){
    int i;
    for(i = 0; i < NUMBER_OF_PROCESSES; i++){
        average_waiting_time += waiting_time[i];    
    }
    average_waiting_time /= NUMBER_OF_PROCESSES;
}

void calculate_and_print(){
    calculate_completion_time();
    calculate_turnaround_time();
    calculate_waiting_time();
    calculate_average_turnaround_time();
    calculate_average_waiting_time();
    
    printf("Order in which process gets executed\n");
    int i;
    for(i = 0; i < NUMBER_OF_PROCESSES; i++){
        printf("%d ", processes_execution_order[i]);
    }
    
    printf("\n%-20s", "Processes");
    printf("%-20s", "Arrival time");
    printf("%-20s", "Burst time");
    printf("%-20s", "Waiting time");
    printf("%-20s\n", "Turn around time");
    
    int process_order;
    for(i = 0; i < NUMBER_OF_PROCESSES; i++){
        process_order = processes_execution_order[i] - 1;
        printf("%-20d", processes_ids[process_order]);
        printf("%-20d", arrival_time[process_order]);
        printf("%-20d", burst_time[process_order]);
        printf("%-20d", waiting_time[process_order]);
        printf("%-20d\n", turnaround_time[process_order]);
    }
    
    printf("Average waiting time = %f\n", average_waiting_time);
    printf("Average turn around time = %f\n", average_turnaround_time);
}

