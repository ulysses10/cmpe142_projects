// 
// -- Process Scheduling Algorithms
// 

#include "globals.hpp"

// --First Come First Serve
void fcfs()//process schedule[])
{
    /*
     * 
     * This section is only needed for testing since the assignment only asks to output the readyQ
     * 
    // -- Setup Random Process schedule
    process *schedule=generateSchedule();
    cout << "Processes generated:\n";
    printSchedule(schedule);            
    cout << "\n";
 
    // Setup ready Queue
    process readyQ[MAX_PROCESSES];
    for(int i=0; i<MAX_PROCESSES; i++)
    {
        readyQ[i]=schedule[i];
    }
    */ // uncomment this^ section and comment out the next line of code to print the random schedule first and then setup readyQ
    
    process *readyQ=generateSchedule();  // comment out this line if needed ^

    // -- Sorts by arrival time
    for( size_t i = 1; i < MAX_PROCESSES; i++)
    {
        process key = readyQ[i];
        int j=i-1;
        while(j>=0 && readyQ[j].arrival_time>key.arrival_time) // -- for non increasing order: a[j]<key
        {
            readyQ[j+1]=readyQ[j];
            j-=1;
        }
        readyQ[j+1]=key;
    }
    cout << "\nSorted Schedule by Arrival Time:\n";
    printSchedule(readyQ);

    // -- Algorithm for FCFS
    int t=0;
    for(int i=0; i<MAX_PROCESSES; i++)
    {
        while(readyQ[i].run_time>0)
        {
            quanta[t] = readyQ[i].name;
            readyQ[i].run_time--;
            t++;
        }
    }
    // -- Fill unused quanta with hyphens
    while(t<quanta_length)
    {
        quanta[t]='-';
        t++;
    }

    // -- Print results
    printQuantaArray();
}