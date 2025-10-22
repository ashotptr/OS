# Process Scheduling Algorithms

fcfs_sjf program takes user input for the number of processes, their arrival times, and their burst times. 

For each algorithm, it displays:
1)A Gantt chart showing the order of execution.
2)A table with PID, AT(Arrival time), BT(Burst time), WT(Waiting time), TAT(Turnaround time), and RT(Response time).
3)The average Waiting Time, Turnaround Time, and Response Time.

## How to Compile and Run

1.  Clone the repository and open the directory "process_scheduling"
2.  **Compile the C code:**
    ```bash
    gcc fcfs_sjf.c -o fcfs_sjf 
    ```
3.  **Run the executable:**
    ```bash
    ./fcfs_sjf
    ```

## Example

### Input
Enter the number of processes: 4
Enter the arrival time and burst time for process 1: 0 8
Enter the arrival time and burst time for process 2: 1 4
Enter the arrival time and burst time for process 3: 2 9
Enter the arrival time and burst time for process 4: 3 5

### Output
=== First Come First Served (FCFS) ===
Gantt Chart: | P1 | P2 | P3 | P4 |

PID   AT    BT    WT    TAT   RT
1     0     8     0     8     0
2     1     4     7     11    7
3     2     9     10    19    10
4     3     5     18    23    18

Average Waiting Time: 8.75
Average Turnaround Time: 15.25
Average Response Time: 8.75

=== Shortest Job First (SJF) ===
Gantt Chart: | P1 | P2 | P4 | P3 |

PID   AT    BT    WT    TAT   RT
1     0     8     0     8     0
2     1     4     7     11    7
3     2     9     15    24    15
4     3     5     9     14    9

Average Waiting Time: 7.75
Average Turnaround Time: 14.25
Average Response Time: 7.75
