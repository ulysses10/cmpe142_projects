
#include "psa.hpp"

#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    srand(time(0)); // -- While debugging, set srand seed to 0

    // -- Run FCFS algorithm
    for(int i=0; i<trials; i++){
        fcfs();
    }
    // -- Run SJF algorithm
    // sjf(schedule);

    // -- Run SRT algorithm
    // srt(schedule);


    return 0;
}