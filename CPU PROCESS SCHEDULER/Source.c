#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//defining const variables
#define MAX_PROCESSES 50
#define RAM_SIZE 2048
#define HIGH_PRIORITY_RAM 512
#define USER_PROCESS_RAM (RAM_SIZE - HIGH_PRIORITY_RAM)
#define QUANTUM_TIME_2 8
#define QUANTUM_TIME_3 16
#define MAX_CPU1 100
#define MAX_CPU2 100


int count = 0; //ms clock

// c = current
int cProcesses, cUser, cHigh, cCPU1,cCPU2, cRam = 0;

int q; //temporary quantum clock for every rr operation



typedef struct {
    int process_id;
    int arrival_time;
    int priority;
    int burst_time;
    int ram;
    int cpu_rate;
    int r_time; //remaining time??????
} Process;




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




//queue functions
void initializeQueue(Queue* queue);
bool isEmpty(Queue* queue);
void enqueue(Queue* queue, Process process);
Process dequeue(Queue* queue);
void displayQueue(Queue* queue);



// Functions
int readFile(char* filename);
void scheduleProcesses();
void sjfAlgorithm(Queue* queue);
bool checkResources(Process process);
void CPU1();
void CPU2();
void CPU2S();

Process processes[MAX_PROCESSES];

int n = 0; //Process number,for assigning the variables into processes[]

Process one; //current process of cpu1
Process two; //current process of cpu2

//defining queues for all algorithms
Queue q_fcfs;
Queue q_sjf;
Queue q_rr8;
Queue q_rr16;

//queues for finishing order
Queue qf_fcfs;
Queue qf_sjf;
Queue qf_rr8;
Queue qf_rr16;



int main(int argc, char* argv[]) {

    //setting up queues
    initializeQueue(&q_fcfs);
    initializeQueue(&q_sjf);
    initializeQueue(&q_rr8);
    initializeQueue(&q_rr16);

    initializeQueue(&qf_fcfs);
    initializeQueue(&qf_sjf);
    initializeQueue(&qf_rr8);
    initializeQueue(&qf_rr16);

    //setting up processes in CPUs
    one.r_time = 0;
    two.r_time = 0;

    one.process_id = 50;
    two.process_id = 51;

    
    readFile("input.txt");


    FILE* output_file = freopen("output.txt", "w", stdout); //output console

    if (output_file == NULL) {
        perror("freopen failed");
        return EXIT_FAILURE;
    }


    while (1) { //infinite loop 

        
        scheduleProcesses(); // schedule processes (everytime because of arrival time)

        //processing 1ms of current process and assignment

        

        CPU1(); 
        CPU2(); 
        
        if (isEmpty(&q_rr16) == 1 && isEmpty(&q_rr8) == 1 && isEmpty(&q_sjf) == 1 && isEmpty(&q_fcfs) == 1 && one.r_time == 0 && two.r_time == 0) {
            break;
        }

        count++; //counting 1ms
        
    }
    

    // info
    printf("All tasks are completed\n");

    printf("CPU-1 que1(priority-0) (FCFS)→\n");
    displayQueue(&qf_fcfs);
    printf("CPU-2 que2(priority-1) (SJF)→\n");
    displayQueue(&qf_sjf);
    printf("CPU-2 que3(priority-2) (RR-q8)→\n");
    displayQueue(&qf_rr8);
    printf("CPU-2 que4(priority-3) (RR-q16)→\n");
    displayQueue(&qf_rr16);

    printf("MS= %d", count);

    fclose(output_file); //close file
    

    return 1; 
    
}




bool checkResources(Process process) {

    if (process.priority == 0) { //checking 2 pool of ram and 2 cpu rates depending on priority

        if ((cHigh + process.ram) <= HIGH_PRIORITY_RAM && (cCPU1 + process.cpu_rate) <= MAX_CPU1) {
            
            printf("resources are enough for P%d\n", process.process_id );
            return 1;
        }
        else {
            printf("resources are not enough for P%d\n", process.process_id);

            return 0;
        }

    }
    else {

        if (cUser + process.ram <= USER_PROCESS_RAM && cCPU2 + process.cpu_rate <= MAX_CPU2) {
           
            printf("resources are enough for P%d\n", process.process_id);
            return 1;
        }
        else {
            printf("resources are not enough for P%d\n", process.process_id);
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

    char line[100]; // for future upgrade for system

    while (fgets(line, sizeof(line), fp) != NULL) {
        
        
        processes[n].process_id = n + 1;

        char* token = strtok(line, ",");
        
        
        processes[n].arrival_time = atoi(strtok(NULL, ","));
        processes[n].priority = atoi(strtok(NULL, ","));
        processes[n].burst_time = atoi(strtok(NULL, ","));
        processes[n].ram = atoi(strtok(NULL, ","));
        processes[n].cpu_rate = atoi(strtok(NULL, ","));
        processes[n].r_time = processes[n].burst_time;


        

        n++;

        
    }
     

    fclose(fp); //close "input.txt"

    return 0;
}



void scheduleProcesses() {

    for (int i = 0; i <= n; i++) { //looping all processes (n is process amount)

        if (processes[i].arrival_time == count && processes[i].process_id != 0) { // checking arrival time (count is current time) and ignore id0 (ghost process because of empty queue)

            switch (processes[i].priority) //enqueue for every priority in current time
            {
            case 0:

                if (checkResources(processes[i]) == 1) {

                    printf("fcfs\n");

                    //allocating resources for chosen process
                    cHigh = cHigh + processes[i].ram; 
                    cCPU1 = cCPU1 + processes[i].cpu_rate;

                    enqueue(&q_fcfs, processes[i]); //enqueue

                    printf("Process P%d is queued to be assigned to CPU-1.\n\n", processes[i].process_id);
                }
                else {

                    processes[i].arrival_time++; 
                    
                    //no resources so delaying arrival time for future queue 
                    printf("fcfs\n");
                    printf("arrival time delayed\n\n");
                }

                
                break;

                //same for every priority

            case 1:
                if (checkResources(processes[i]) == 1) {

                    printf("sjf\n");
                    cUser = cUser + processes[i].ram;
                    cCPU2 = cCPU2 + processes[i].cpu_rate;

                    enqueue(&q_sjf, processes[i]);
                    printf("Process P%d is queued to be assigned to CPU-2.\n\n", processes[i].process_id);
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
                    cCPU2 = cCPU2 + processes[i].cpu_rate;

                    enqueue(&q_rr8, processes[i]);
                    printf("Process P%d is queued to be assigned to CPU-2.\n\n", processes[i].process_id);
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
                    cCPU2 = cCPU2 + processes[i].cpu_rate;

                    enqueue(&q_rr16, processes[i]);
                    printf("Process P%d is queued to be assigned to CPU-2.\n\n", processes[i].process_id);
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

    cRam = cUser + cHigh; //calculating cuurent ram usage (for future features)

    
    
}



//sorting queue
void sjfAlgorithm(Queue* queue) {
    int n = 0; // Number of elements in the queue (can be calculated dynamically) (local n variable)
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




void CPU1() {
    
    if (one.r_time != 0) { //if there is current process in cpu
        
        one.r_time--; //completing 1ms of process

        if (one.r_time == 0 && isEmpty(&q_fcfs) == 0) { //if process is completed and there is a process in queue 

            printf("Process P%d is completed and terminated in CPU1.\n\n", one.process_id);
            
            //deallocating memory and cpu
            cHigh = cHigh - one.ram;
            cCPU1 = cCPU1 - one.cpu_rate;

            enqueue(&qf_fcfs, one); //enqueue finished process in output queue

            one = dequeue(&q_fcfs); //assigning new process in cpu

            printf("Process P%d is assigned in CPU1.\n\n", one.process_id);


        }
        else if(one.r_time == 0){

            printf("Process P%d is completed and terminated in CPU1.\n\n", one.process_id);

            cHigh = cHigh - one.ram;
            cCPU1 = cCPU1 - one.cpu_rate;

            enqueue(&qf_fcfs, one); //enqueue finished process in output queue

        }
    }
    else if(isEmpty(&q_fcfs) == 0){

        
            one = dequeue(&q_fcfs);//for first assignment

            printf("Process P%d is assigned in CPU1.\n\n", one.process_id);
        
    }

};


//CPU2 assignment
void CPU2S() { 

    if (isEmpty(&q_sjf) == 0) { //checking if queues are not empty (for high priority first)

        sjfAlgorithm(&q_sjf); // sorting queue for sjf 

        two = dequeue(&q_sjf); //assigning process in cpu

        printf("Process P%d is assigned in CPU2.\n\n", two.process_id);
    }
    else if (isEmpty(&q_rr8) == 0) {

        q = QUANTUM_TIME_2; //defining quantum time for process

        two = dequeue(&q_rr8);//assigning process in cpu

        printf("Process P%d is assigned in CPU2.\n\n", two.process_id);
    }
    else if (isEmpty(&q_rr16) == 0) {

        q = QUANTUM_TIME_3; //defining quantum time for process

        two = dequeue(&q_rr16);//assigning process in cpu

        printf("Process P%d is assigned in CPU2.\n\n", two.process_id);
    }




};

void CPU2() { 

    if (two.r_time != 0 && two.priority == 1) { //if there is current process in cpu

        two.r_time--; //completing 1ms of process

        if (two.r_time == 0) { //if process is completed 

            printf("Process P%d is completed and terminated in CPU2.\n\n", two.process_id);

            

            //deallocating resources

            cUser = cUser - two.ram;
            cCPU2 = cCPU2 - two.cpu_rate;

            enqueue(&qf_sjf, two); //enqueue finished process in output queue

            CPU2S(); //assign new process

        }
    }
    else if(two.r_time != 0 && two.priority==2) { //if there is current rr8 process in cpu

         two.r_time--;//completing 1ms of process

         q--; //decrease q clock

        if (q==0) { // if process completed by defined q time 

            printf("Process P%d run until the defined quantum time and is queued again because the process is not completed. \n\n", two.process_id);
            enqueue(&q_rr8,two); //requeue process
            CPU2S(); //assign new process 

        }else if (two.r_time == 0){ //if process is completed 

            printf("Process P%d is completed and terminated in CPU2.\n\n", two.process_id);

            //deallocating resources

            cUser = cUser - two.ram;
            cCPU2 = cCPU2 - two.cpu_rate;

            enqueue(&qf_rr8, two); //enqueue finished process in output queue
            CPU2S(); //assign new process

        }

    }
    else if (two.r_time != 0 && two.priority == 3) { // same as rr8 
        
        two.r_time--;
        q--;

        if (q == 0) {

            printf("Process P%d run until the defined quantum time and is queued again because the process is not completed. \n\n", two.process_id);
            enqueue(&q_rr8, two);

            CPU2S();

        }
        else if (two.r_time == 0) {

            printf("Process P%d is completed and terminated in CPU2.\n\n", two.process_id);
            cUser = cUser - two.ram;
            cCPU2 = cCPU2 - two.cpu_rate;

            enqueue(&qf_rr16, two); //enqueue finished process in output queue
            CPU2S();

        }


    }
    else {
        CPU2S(); //for first assignment
    }


};






//-------------------------queue functions

void initializeQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

bool isEmpty(Queue* queue) {
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
        exit(1);
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
        printf("Process ID: P%d, Arrival Time: %d, Priority: %d, Burst Time: %d, RAM: %d, CPU Rate: %d, Remaining Time: %d\n",
            temp->data.process_id, temp->data.arrival_time, temp->data.priority, temp->data.burst_time,
            temp->data.ram, temp->data.cpu_rate, temp->data.r_time);
        temp = temp->next;
    }
    printf("\n");
}

