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

Process processes[MAX_PROCESSES];




// Functions
int readFile(char* filename);
void scheduleProcesses();
void fcfsAlgorithm();
void sjfAlgorithm();
void roundRobinAlgorithm(int quantum_time);
void checkResources();
void assignToCPU1(Process* process);
void assignToCPU2(Process* process);
void printOutputFile();
// simdilik bunlar var

int main(int argc, char* argv[]) {

   
    printf("yessir");

   
    int count = 0;

    readFile("input.txt");

    scheduleProcesses();
    
    

    

    return 0;
}



// Function to read processes from file
int readFile(char* filename) {

    int n = 0; //for assigning the variables into processes[]

    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening file: %s\n", filename);
        return 1;
    }

    char line[100]; // input uzunluguna gore ayarlanir

    while (fgets(line, sizeof(line), fp) != NULL) {
        
        if (n == -1) {
            n++;
            continue;
        }

        char processName[2]; //ilk elemanı doğru okumuyor
        char* token = strtok(line, ",");
        if (token != NULL) {
            strncpy(processName, token, sizeof(processName) - 1);
            processName[sizeof(processName) - 1] = '\0'; // Ensure null termination????????
        }
        
        int arrivalTime = atoi(strtok(NULL, ","));
        int priority = atoi(strtok(NULL, ","));
        int burstTime = atoi(strtok(NULL, ","));
        int memoryRequired = atoi(strtok(NULL, ","));
        int cpu = atoi(strtok(NULL, ","));


        for (int i = 0; i < 2; i++) {
            processes[n].process_id[i] = processName[i]; // Format process ID as P1, P2, etc.
        }
        processes[n].arrival_time = arrivalTime;
        processes[n].priority = priority;
        processes[n].burst_time = burstTime;
        processes[n].ram = memoryRequired;
        processes[n].cpu_rate = cpu;

           
        


        
        //printf("%d", cpu); //deneme icin

       /* for (int i = 0; i < 2; ++i) {
            printf("processName[%d] = %c\n", i, processName[i]);
        }*/
        

        
    }

    fclose(fp);

    return 0;
}



void scheduleProcesses() {

    processes[1];
    //Scheduling code using FCFS, SJF, and Round Robin algorithms
}


void fcfsAlgorithm() {};
void sjfAlgorithm() {};
void roundRobinAlgorithm(int quantum_time) {};
void checkResources() {};
void assignToCPU1(Process* process) {};
void assignToCPU2(Process* process) {};
void printOutputFile() {};

