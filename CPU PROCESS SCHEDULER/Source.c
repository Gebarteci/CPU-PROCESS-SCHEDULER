#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PROCESSES 26
#define RAM_SIZE 2048
#define HIGH_PRIORITY_RAM 512
#define USER_PROCESS_RAM (RAM_SIZE - HIGH_PRIORITY_RAM)
#define QUANTUM_TIME_2 8
#define QUANTUM_TIME_3 16
#define MAX_CPU0 100
#define MAX_CPU1 100

int count = 0; //ms clock

static int am = 0;


// c = current
int cProcesses, cUser, cHigh, cCPU0,cCPU1, cRam = 0;





typedef struct {
    char process_id[2];
    int arrival_time;
    int priority;
    int burst_time;
    int ram;
    int cpu_rate;
    int r_time; //remaining time
} Process;

Process processes[MAX_PROCESSES];
int n = 0; //Process number,for assigning the variables into processes[]

Process one;
Process two;


// Structure for a queue node
typedef struct Node {
    Process data;
    struct Node* next;
} Node;

// Structure for the queue
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

Queue q_fcfs;
Queue q_sjf;
Queue q_rr8;
Queue q_rr16;

//queue functions
void initializeQueue(Queue* queue);
int isEmpty(Queue* queue);
void enqueue(Queue* queue, Process process);
Process dequeue(Queue* queue);
void displayQueue(Queue* queue);



// Functions
int readFile(char* filename);
void scheduleProcesses();
void fcfsAlgorithm(Process process);
void sjfAlgorithm(Queue* queue);
void roundRobinAlgorithm(Process process, int quantum_time);
bool checkResources(Process process);
void CPU1();
void CPU2();
void printOutputFile();


int main(int argc, char* argv[]) {

    initializeQueue(&q_fcfs);
    initializeQueue(&q_sjf);
    initializeQueue(&q_rr8);
    initializeQueue(&q_rr16);

    one.burst_time = 0;
    two.burst_time = 0;

    
    readFile("input.txt");


    while (count<80) {

        
        scheduleProcesses();

        CPU1();
        CPU2();
        count++;
        
    }
    

    

    return 0;
}

bool checkResources(Process process) {

    if (process.priority == 0) {

        if ((cHigh + process.ram) <= HIGH_PRIORITY_RAM && (cCPU0 + process.cpu_rate) <= MAX_CPU0) {
            
            printf("resources are enough\n" );
            return 1;
        }
        else {
            printf("resources are not enough\n");

            return 0;
        }

    }
    else {

        if (cUser + process.ram <= USER_PROCESS_RAM && cCPU1 + process.cpu_rate <= MAX_CPU1) {
           
            printf("resources are enough\n");
            return 1;
        }
        else {
            printf("resources are not enough\n");
            return 0;
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
        processes[n].r_time = processes[n].burst_time;


        for (int i = 0; i < 2; i++) {
            processes[n].process_id[i] = processName[i]; // Format process ID as P1, P2, etc.
        }

        n++;

           
        


        
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

        if (processes[i].arrival_time == count) {

            switch (processes[i].priority)
            {
            case 0:

                if (checkResources(processes[i]) == 1) {

                    printf("high\n");
                    cHigh = cHigh + processes[i].ram;
                    cCPU0 = cCPU0 + processes[i].cpu_rate;

                    enqueue(&q_fcfs, processes[i]);
                    printf("Process %d is queued to be assigned to CPU-1.\n\n", processes[i].process_id[0]);
                }
                else {
                    processes[i].arrival_time++;
                    printf("high\n");
                    printf("arrival time delayed\n\n");
                }

                
                break;
            case 1:
                if (checkResources(processes[i]) == 1) {

                    printf("sjf\n");
                    cUser = cUser + processes[i].ram;
                    cCPU1 = cCPU1 + processes[i].cpu_rate;

                    enqueue(&q_sjf, processes[i]);
                    printf("Process %d is queued to be assigned to CPU-2.\n\n", processes[i].process_id[0]);
                }
                else {
                    processes[i].arrival_time++;
                    printf("sjf\n");
                    printf("arrival time delayed\n\n");
                }
                break;
            case 2:
                if (checkResources(processes[i]) == 1) {
                    printf("robin8\n");
                    cUser = cUser + processes[i].ram;
                    cCPU1 = cCPU1 + processes[i].cpu_rate;

                    enqueue(&q_rr8, processes[i]);
                    printf("Process %d is queued to be assigned to CPU-2.\n\n", processes[i].process_id[0]);
                }
                else {
                    processes[i].arrival_time++;
                    printf("robin8\n");
                    printf("arrival time delayed\n\n");
                }
                break;
            case 3:

                if (checkResources(processes[i]) == 1) {
                    printf("robin16\n");
                    cUser = cUser + processes[i].ram;
                    cCPU1 = cCPU1 + processes[i].cpu_rate;

                    enqueue(&q_rr16, processes[i]);
                    printf("Process %d is queued to be assigned to CPU-2.\n\n", processes[i].process_id[0]);
                }
                else {
                    processes[i].arrival_time++;
                    printf("robin16\n");
                    printf("arrival time delayed\n\n");
                }

                break;
            default:
                break;
            }

        }


    }

    cRam = cUser + cHigh;

    sjfAlgorithm(&q_sjf);
    //roundRobinAlgorithm(&q_rr8);
    //roundRobinAlgorithm(&q_rr16);
    displayQueue(&q_sjf);
    
    //Scheduling code using FCFS, SJF, and Round Robin algorithms----------------------------------
}


void fcfsAlgorithm(Process process) {
};

void sjfAlgorithm(Queue* queue) {
    int n = 0; // Number of elements in the queue (can be calculated dynamically)
    Node* current, * min, * temp;

    // Count the number of elements in the queue 
    current = queue->front;
    while (current != NULL) {
        n++;
        current = current->next;
    }

    // Selection Sort implementation
    for (int i = 0; i < n - 1; i++) {
        min = &queue->front[i];

        for (int j = i + 1; j < n; j++) {
            temp = &queue->front[j];
            if (temp->data.burst_time < min->data.burst_time) {
                min = temp;
            }
        }

        // Swap the elements (data within the nodes)
        Process tempData = min->data;
        min->data = queue->front[i].data;
        queue->front[i].data = tempData;
    }
}

void roundRobinAlgorithm(Process process,int quantum_time) {

    
};



void CPU1() {
    
    if (one.burst_time != 0) {
        
        one.burst_time--; //completing 1ms of process

        if (one.burst_time == 0 && isEmpty(&q_fcfs) == 0) {

            printf("Process %d is completed and terminated in CPU1.\n\n", one.process_id[0]);
            
            am++;
            printf("%d \n", am);
            cHigh = cHigh - one.ram;
            cCPU0 = cCPU0 - one.cpu_rate;

            one = dequeue(&q_fcfs);

        }
    }
    else {

        if (isEmpty(&q_fcfs) == 0) {
            one = dequeue(&q_fcfs);//for first assignment
        }
    }

};

void CPU2() {


};
void printOutputFile() {};



//-------------------------queue functions

void initializeQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

void enqueue(Queue* queue, Process process) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = process;
    newNode->next = NULL;

    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    }
    else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

Process dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        exit(1);  // Or handle the error appropriately
    }

    Node* temp = queue->front;
    Process process = temp->data;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    return process;
}

void displayQueue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }

    Node* temp = queue->front;
    while (temp != NULL) {
        printf("Process ID: %s, Arrival Time: %d, Priority: %d, Burst Time: %d, RAM: %d, CPU Rate: %d, Remaining Time: %d\n",
            temp->data.process_id, temp->data.arrival_time, temp->data.priority, temp->data.burst_time,
            temp->data.ram, temp->data.cpu_rate, temp->data.r_time);
        temp = temp->next;
    }
    printf("\n");
}

