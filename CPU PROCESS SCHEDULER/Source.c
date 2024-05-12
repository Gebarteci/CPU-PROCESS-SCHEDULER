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
#define MAX_CPU0 100
#define MAX_CPU1 100


// c =current
int cProcesses, cUser, cHigh, cCPU0,cCPU1 = 0;
int cRam;




typedef struct {
    char process_id[2];
    int arrival_time;
    int priority;
    int burst_time;
    int ram;
    int cpu_rate;
} Process;

Process processes[MAX_PROCESSES];
int n = 0; //for assigning the variables into processes[]




// Functions
int readFile(char* filename);
void scheduleProcesses();
void fcfsAlgorithm(Process process);
void sjfAlgorithm(Process process);
void roundRobinAlgorithm(Process process, int quantum_time);
void checkResources(Process process);
void assignToCPU1(Process process);
void assignToCPU2(Process process);
void printOutputFile();


int main(int argc, char* argv[]) {

   
    

   
    int count = 0;
    


    readFile("input.txt");

    scheduleProcesses();
    
    

    

    return 0;
}

void checkResources(Process process) {

    if (process.priority == 0) {

        if (cHigh + process.ram <= HIGH_PRIORITY_RAM && cCPU0 + process.cpu_rate <= MAX_CPU0) {
            cHigh = cHigh + process.ram;
            cCPU0 = cCPU0 + process.cpu_rate;
        }
        else {
            printf("resources are not enough");

        }

    }
    else {

        if (cUser + process.ram <= USER_PROCESS_RAM && cCPU1 + process.cpu_rate <= MAX_CPU1) {
            cUser = cUser + process.ram;
            cCPU1 = cCPU1 + process.cpu_rate;
        }
        else {
            printf("resources are not enough");
        }

    }


};



// Function to read processes from file
int readFile(char* filename) {

    

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
        
        processes[n].arrival_time = atoi(strtok(NULL, ","));
        processes[n].priority = atoi(strtok(NULL, ","));
        processes[n].burst_time = atoi(strtok(NULL, ","));
        processes[n].ram = atoi(strtok(NULL, ","));
        processes[n].cpu_rate = atoi(strtok(NULL, ","));


        for (int i = 0; i < 2; i++) {
            processes[n].process_id[i] = processName[i]; // Format process ID as P1, P2, etc.
        }
         

           
        


        
        //printf("%d", processes[n].cpu_rate); //deneme icin

       /* for (int i = 0; i < 2; ++i) {
            printf("processName[%d] = %c\n", i, processName[i]);
        }*/
        

        
    }

    fclose(fp);

    return 0;
}



void scheduleProcesses() {

    for (int i = 0; i <= n; i++) {

        switch (processes[i].priority)
        {
        case 0:
            fcfsAlgorithm(processes[i]);
            break;
        case 1:
            sjfAlgorithm(processes[i]);
            break;
        case 2:
            roundRobinAlgorithm(processes[i], QUANTUM_TIME_2);
            break;
        case 3:
            roundRobinAlgorithm(processes[i], QUANTUM_TIME_3);
            break;
        default:
            break;
        }
    }
    
    //Scheduling code using FCFS, SJF, and Round Robin algorithms
}


void fcfsAlgorithm(Process process) {

    checkResources(process);

};

void sjfAlgorithm(Process process) {
    checkResources(process);
    

};

void roundRobinAlgorithm(Process process,int quantum_time) {
    checkResources(process);

};



void assignToCPU1(Process process) {};
void assignToCPU2(Process process) {};
void printOutputFile() {};

