# Process Scheduling Simulator
This project is a Process Scheduling Simulator that mimics a simplified operating system process management. It uses multiple scheduling algorithms to manage processes based on their priorities and resource requirements.

## Features
Queue-based Scheduling:

-FCFS (First Come, First Serve): High-priority processes are handled using a straightforward queue.

-SJF (Shortest Job First): Optimized for low-priority processes to reduce average waiting time.

-Round Robin (RR): Time-sharing for processes with quantum values of 8 ms and 16 ms.

## Resource Management

-RAM and CPU usage are dynamically allocated and deallocated.

-Processes requiring more resources than available are queued or marked as "impossible."

## Process Management

-Processes are read from an input file (input.txt) and include attributes such as arrival time, priority, burst time, RAM, and CPU rate.

-The system continuously schedules processes until all are completed or marked as "impossible."

## How It Works

### Input: Processes are read from input.txt in the format:
process_id,arrival_time,priority,burst_time,ram,cpu_rate

### Scheduling: Processes are assigned to CPUs based on their priority:

### CPU-1 handles high-priority processes (FCFS).

### CPU-2 handles lower-priority processes (SJF and RR).

###Output: Execution logs and final process states are saved in output.txt.

## Key Functions

-readFile(): Reads processes from the input file and initializes them.
-scheduleProcesses(): Assigns processes to the appropriate scheduling queue based on priority and resource availability.
-CPU1() and CPU2(): Execute processes based on the assigned CPU.
-displayQueue(): Outputs the current state of a queue.

## How to Use

-Clone this repository.

### Compile the code using a C compiler:
-bash:

 gcc -o scheduler scheduler.c
 
 ### Run the executable:
-bash:

 ./scheduler

-Provide an input.txt file in the working directory containing process details.

-Example Input

input.txt:
1,0,0,5,100,20
2,1,1,10,200,30
3,2,2,8,150,25
4,3,3,12,180,35

Example Output:
Check output.txt for detailed execution logs and final process states.
