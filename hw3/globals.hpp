
#include <iostream>
#include <iomanip>

using namespace std;
const int trials = 1;           // -- number of trials need to run. Change to 5 per assignment requirement
const double max_run_time = 4.9;
const int arrival_range = 20;   // -- Time range of cpu access. No process should run if it does not get cpu time. 
                                // -- Every process that gets cpu time should complete
const int quanta = arrival_range + 10;   // -- quanta time line. Only processes that get cpu time should be in the quanta
const int MAX_PROCESSES = 10;    // -- number of processes to be generated
char id[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T'};
char timeline[quanta];     // -- array to hold processes that ran on CPU


struct process{
    char name;
    float arrival_time;
    float run_time;
    int priority;
};

process *generateSchedule()
{
    static process schedule[MAX_PROCESSES];
    for(int i=0; i<MAX_PROCESSES; i++){   
        // Name process
        schedule[i].name = id[i];

        // Generate arrival time
        schedule[i].arrival_time = rand()%arrival_range;

        // Generate runtime
        schedule[i].run_time = (float)rand()/(RAND_MAX)*max_run_time+.1;

        // Generate priority
        schedule[i].priority = rand()%5;
    }
    // -- Sorts by arrival time
    for( size_t i = 1; i < MAX_PROCESSES; i++){
        process key = schedule[i];
        int j=i-1;
        while(j>=0 && schedule[j].arrival_time>key.arrival_time) {    // -- for non increasing order: a[j]<key
            schedule[j+1]=schedule[j];
            j-=1;
        }
        schedule[j+1]=key;
    }
    return schedule;
}

void printQuantaArray( int offset)
{
    // -- 
    cout << "CPU access time in quantum: " << arrival_range << "\n";
    cout << "Quanta range: 0 - " <<  arrival_range-1 << "\n";
    // -- Processes in quanta
    cout << setw(20) << "Scheduling Timeline:";
    for( int i=0; i<arrival_range+offset; i++){
        cout << setw(2) << right << timeline[i] <<"|";
    }
    // -- Quanta labels
    cout << "\n" << setw(20) << right <<"Quanta:";
    for(int i=0; i<arrival_range+offset; i++){
        cout << setw(2) << right << i <<"|";
    }
    cout << "\n\n";
}

void printSchedule( process schedule[]){
    for( int i=0; i<MAX_PROCESSES; i++){
		cout << "process "<< schedule[i].name << " | ";

        cout << "arrival time "<< setw(4) << right << schedule[i].arrival_time << " | ";

        cout << "run time "<< setw(8) << left << schedule[i].run_time << " | ";

        cout << "priority " << schedule[i].priority << "\n";
    }
    cout << "\n";
}