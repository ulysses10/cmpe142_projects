// 
// -- Process Scheduling Algorithms
// 

#include "globals.hpp"

// --First Come First Serve
void fcfs(){   
    process *readyQ=generateSchedule();  // a schedule sorted by arrival time is generated

    cout << "\nSorted Schedule by Arrival Time:\n";
    printSchedule(readyQ);

    // -- Algorith for FCFS (actual)
    int p=0;
    int offset=0;
    // -- CPU time
    for( int i=0; i<arrival_range; i++){
        if(readyQ[p].arrival_time <= i && p<MAX_PROCESSES){ // -- p cant exceed MAX_PROCESSES (readyQ length)
            for(int j=0; j< readyQ[p].run_time; j++){
                timeline[i]=readyQ[p].name;
                i++;
            }
            offset = i - arrival_range; // -- offset to accomadate processes completed outside cpu time
            i--;
            p++;
        }
        else{
            timeline[i]='-';
        }
    }

    if(offset<0) offset=0;
    // -- Print results
    printQuantaArray(offset);
}

// -- Shortest Job First
void sjf(){

    process *readyQ=generateSchedule();  // a schedule sorted by arrival time is generated

    // -- Sorts by shortest job
    int j=0;
    for( int i=0; i<MAX_PROCESSES; i++){
        j=i;
        while(readyQ[i].arrival_time == readyQ[j+1].arrival_time) // -- get the index range of processes with same arrival time
            j++;
        if(j!=i){
            j++;
            // sort by run time from i to j-1
            for( size_t k = i+1; k < j; k++){
                process key = readyQ[k];
                int p=k-1;
                while(p>=i && readyQ[p].run_time>key.run_time) {    // -- for non increasing order: a[j]<key
                 readyQ[p+1]=readyQ[p];
                 p-=1;
            }
            readyQ[p+1]=key;
            }
        }
    }

    cout << "\nSorted Schedule by Arrival and Run Time:\n";
    printSchedule(readyQ);

    // -- Algorith for FCFS (actual)
    int p=0;
    int offset=0;
    // -- CPU time
    for( int i=0; i<arrival_range; i++){
        if(readyQ[p].arrival_time <= i && p<MAX_PROCESSES){ // -- p cant exceed MAX_PROCESSES (readyQ length)
            for(int j=0; j< readyQ[p].run_time; j++){
                timeline[i]=readyQ[p].name;
                i++;
            }
            offset = i - arrival_range; // -- offset to accomadate processes completed outside cpu time
            i--;
            p++;
        }
        else{
            timeline[i]='-';
        }
    }

    if(offset<0) offset=0;
    // -- Print results
    printQuantaArray(offset);

}

// -- Shortest Remaining Time
void srt(){
    process *readyQ=generateSchedule();  // a schedule sorted by arrival time is generated
    cout << "\nSorted Schedule by Arrival Time:\n";
    printSchedule(readyQ);

    // -- Sorts by shortest job ( shortest remaining time )
    int j=0;
    for( int i=0; i<MAX_PROCESSES; i++){
        j=i;
        while(readyQ[i].arrival_time == readyQ[j+1].arrival_time) // -- get the index range of processes with same arrival time
            j++;
        if(j!=i){
            j++;
            // sort by run time from i to j-1 
            for( size_t k = i+1; k < j; k++){
                process key = readyQ[k];
                int p=k-1;
                while(p>=i && readyQ[p].run_time>key.run_time) {    // -- for non increasing order: a[j]<key
                 readyQ[p+1]=readyQ[p];
                 p-=1;
                }
            readyQ[p+1]=key;
            }
        }
    }

    // -- Run like sjf but check every quanta if new process comes in. 
        // if new process has shorter remaining run time, push to front of q ( halt current process and start new process on next quantum)
        // keep track of current run time for a process to calculate remaining time for comparison
        // 

}