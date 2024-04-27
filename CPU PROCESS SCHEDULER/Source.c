#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 25
#define RAM_SIZE 2048
#define HIGH_PRIORITY_RAM 512
#define USER_PROCESS_RAM (RAM_SIZE - HIGH_PRIORITY_RAM)
#define QUANTUM_TIME_2 8
#define QUANTUM_TIME_3 16

typedef struct {
    char process_id[3];
    int arrival_time;
    int priority;
    int burst_time;
    int ram;
    int cpu_rate;
} Process;

// Functions
void readProcesses(const char* filename, Process processes[], int* count);
void scheduleProcesses(Process processes[], int count);
void fcfsAlgorithm();
void sjfAlgorithm();
void roundRobinAlgorithm(int quantum_time);
void checkResources();
void assignToCPU1(Process* process);
void assignToCPU2(Process* process);
void printOutputFile();
// þimdilik bunlar var

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    Process processes[MAX_PROCESSES];
    int count = 0;

    readProcesses(argv[1], processes, &count);
    scheduleProcesses(processes, count);

    // buraya örnek kod yazdýrdým

    return 0;
}

// Function to read processes from file
void readProcesses(const char* filename, Process processes[], int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    // ... (Code to read and store processes)

    fclose(file);
}

// Function to schedule processes
void scheduleProcesses(Process processes[], int count) {
    // ... (Scheduling code using FCFS, SJF, and Round Robin algorithms)
}


void fcfsAlgorithm() {};
void sjfAlgorithm() {};
void roundRobinAlgorithm(int quantum_time) {};
void checkResources() {};
void assignToCPU1(Process* process) {};
void assignToCPU2(Process* process) {};
void printOutputFile() {};

