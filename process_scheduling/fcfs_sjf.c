#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;

    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;

    int completed;
} Process;

int comparePID(const void* a, const void* b) {
    Process* p1 = (Process*)a;
    Process* p2 = (Process*)b;
    return p1->pid - p2->pid;
}

int compareArrival(const void* a, const void* b) {
    Process* p1 = (Process*)a;
    Process* p2 = (Process*)b;

    if (p1->arrival_time != p2->arrival_time) {
        return p1->arrival_time - p2->arrival_time;
    }
    
    return p1->pid - p2->pid;
}

void print_results(const char* title, Process p[], int n, int gantt_order[]) {
    printf("=== %s ===\n", title);

    printf("Gantt Chart: |");
    for (int i = 0; i < n; i++) {
        printf(" P%d |", gantt_order[i]);
    }
    printf("\n\n");

    qsort(p, n, sizeof(Process), comparePID);

    printf("%-5s %-5s %-5s %-5s %-5s %-5s\n", "PID", "AT", "BT", "WT", "TAT", "RT");

    double total_wt = 0, total_tat = 0, total_rt = 0;
    for (int i = 0; i < n; i++) {
        printf("%-5d %-5d %-5d %-5d %-5d %-5d\n",
               p[i].pid,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].waiting_time,
               p[i].turnaround_time,
               p[i].response_time);

        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
        total_rt += p[i].response_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Response Time: %.2f\n", total_rt / n);
    printf("\n");
}

void fcfs(Process p[], int n) {
    int current_time = 0;
    int gantt_order[n];
    
    qsort(p, n, sizeof(Process), compareArrival);

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival_time) {
            current_time = p[i].arrival_time;
        }

        p[i].start_time = current_time;
        p[i].completion_time = p[i].start_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        
        p[i].response_time = p[i].waiting_time; 
        
        current_time = p[i].completion_time;

        gantt_order[i] = p[i].pid;
    }
    
    print_results("First Come First Served (FCFS)", p, n, gantt_order);
}

void sjf(Process p[], int n) {
    int current_time = 0;
    int processes_completed = 0;
    int gantt_order[n];

    for (int i = 0; i < n; i++) {
        p[i].completed = 0;
    }

    while (processes_completed < n) {
        int shortest_job_index = -1;
        int shortest_burst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].completed == 0) {
                if (p[i].burst_time < shortest_burst) {
                    shortest_burst = p[i].burst_time;
                    shortest_job_index = i;
                }
                else if (p[i].burst_time == shortest_burst) {
                    if (p[i].arrival_time < p[shortest_job_index].arrival_time) {
                        shortest_job_index = i;
                    }
                }
            }
        }
        
        if (shortest_job_index == -1) {
            current_time++;
        } 
        else {
            int i = shortest_job_index;

            p[i].start_time = current_time;
            p[i].completion_time = p[i].start_time + p[i].burst_time;
            p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
            p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
            
            p[i].response_time = p[i].waiting_time;

            p[i].completed = 1;
            current_time = p[i].completion_time;
            
            gantt_order[processes_completed] = p[i].pid;
            processes_completed++;
        }
    }

    print_results("Shortest Job First (SJF)", p, n, gantt_order);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("No processes to schedule.\n");
        return 1;
    }

    Process processes_fcfs[n];
    Process processes_sjf[n];

    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes_fcfs[i].arrival_time, &processes_fcfs[i].burst_time);
        
        processes_fcfs[i].pid = i + 1;

        processes_sjf[i] = processes_fcfs[i];
    }

    printf("\n");
    
    fcfs(processes_fcfs, n);
    sjf(processes_sjf, n);

    return 0;
}
