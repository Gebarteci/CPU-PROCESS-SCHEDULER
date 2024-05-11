#include <stddef.h>
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
    char process_id[2];
    int arrival_time;
    int priority;
    int burst_time;
    int ram;
    int cpu_rate;
} Process;




// Functions
int readAndSchedule(char* filename);
void scheduleProcesses(char processName[], int priority, int arrivalTime, int burstTime, int memoryRequired, int deadline, int count);
void fcfsAlgorithm();
void sjfAlgorithm();
void roundRobinAlgorithm(int quantum_time);
void checkResources();
void assignToCPU1(Process* process);
void assignToCPU2(Process* process);
void printOutputFile();
// simdilik bunlar var

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }//bu kısım sıkıntı yaratıyor 

    printf("yessir");

    Process processes[MAX_PROCESSES];
    int count = 0;

    readAndSchedule("input.txt");
    

    

    return 0;
}



// Function to read processes from file
int readAndSchedule(char* filename) {

    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening file: %s\n", filename);
        return 1;
    }

    char line[100]; // input uzunluguna gore ayarlanir

    while (fgets(line, sizeof(line), fp) != NULL) {
        
        char processName[2];
        char* token = strtok(line, ",");
        if (token != NULL) {
            strncpy(processName, token, sizeof(processName) - 1);
            processName[sizeof(processName) - 1] = '\0'; // Ensure null termination????????
        }
        int priority = atoi(strtok(NULL, ","));
        int arrivalTime = atoi(strtok(NULL, ","));
        int burstTime = atoi(strtok(NULL, ","));
        int memoryRequired = atoi(strtok(NULL, ","));
        int deadline = atoi(strtok(NULL, ","));

        printf("%d", priority);//deneme icin

        


        scheduleProcesses(processName, priority, arrivalTime, burstTime, memoryRequired, deadline, 0);
    }

    fclose(fp);
    return 0;
}

/

void scheduleProcesses(char processName[], int priority, int arrivalTime, int burstTime, int memoryRequired, int deadline, int count) {
    //Scheduling code using FCFS, SJF, and Round Robin algorithms
}


void fcfsAlgorithm() {};
void sjfAlgorithm() {};
void roundRobinAlgorithm(int quantum_time) {};
void checkResources() {};
void assignToCPU1(Process* process) {};
void assignToCPU2(Process* process) {};
void printOutputFile() {};

