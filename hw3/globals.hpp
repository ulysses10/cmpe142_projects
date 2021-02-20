

#include <iostream>
#include <iomanip>

using namespace std;
const int trials = 2;           // -- number of trials need to run. Change to 5 per assignment requirement
const int quanta_length = 20;   // -- quanta (time slices)
const int MAX_PROCESSES = 3;    // -- number of processes to be generated
char id[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T'};
char quanta[quanta_length];     // -- array to hold processes that ran on CPU


struct process{
    char name;
    float arrival_time;
    float run_time;
    int priority;
};

process *generateSchedule()
{
    static process schedule[MAX_PROCESSES];
    for(int i=0; i<MAX_PROCESSES; i++)
    {   
        // Name process
        schedule[i].name = id[i];

        // Generate arrival time
        schedule[i].arrival_time = rand()%100;

        // Generate runtime
        schedule[i].run_time = (float)rand()/(RAND_MAX)*9.9+.1;

        // Generate priority
        schedule[i].priority = rand()%5;
    }

    return schedule;
}

void printQuantaArray( )
{
    // -- Processes in quanta
    cout << setw(20) << "Scheduling Timeline:";
    for( int i=0; i<quanta_length; i++)
    {
        cout << setw(3) << quanta[i] <<"|";
    }
    // -- Quanta labels
    cout << "\n" << setw(20) <<"Quanta:";
    for(int i=0; i<quanta_length; i++)
    {
        cout << setw(3) << i <<"|";
    }
    cout << "\n\n";
}

void printSchedule( process schedule[])
{
    for( int i=0; i<MAX_PROCESSES; i++)
    {
		cout << "process "<< schedule[i].name << " | ";

        cout << "arrival time "<< setw(4) << schedule[i].arrival_time << " | ";

        cout << "run time "<< setw(8) << schedule[i].run_time << " | ";

        cout << "priority " << schedule[i].priority << "\n";
    }
    cout << "\n";
}