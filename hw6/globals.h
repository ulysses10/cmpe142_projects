#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <iostream>
#include <iomanip>
using namespace std;

enum algorithm
{
    fifo,
    sc,
    lru,
    lfu,
    mfu,
    rndm,
    opt
};

const int MAX_REF = 100;
int reference_string[MAX_REF];
int physical[3];
int process[8] = {0, 1, 2, 3, 4, 5, 6, 7};
int frequency[8]={0};
int queue[3];
int swap_count;
int hit_count;

int victim_random()
{
    return physical[rand() % 3];
}

int victim_fifo(int page_ref)
{
    int victim = queue[0];
    for (int i = 0; i < 2; i++)
        queue[i] = queue[i + 1];
    queue[2] = page_ref;
    return victim;
}

void second_chance(int page_ref)
{
    if (queue[0] == page_ref)
    {
        queue[0] = queue[1];
        queue[1] = queue[2];
    }
    else if (queue[1] == page_ref)
        queue[1] = queue[2];
    queue[2] = page_ref;
}

int victim_lfu(int page_ref){
    int victim = queue[0];
    if(frequency[victim]>frequency[queue[1]])
        victim=queue[1];
    if(frequency[victim]>frequency[queue[2]])
        victim=queue[2];
    if(victim == queue[0]){
        queue[0]=queue[1];
        queue[1]=queue[2];
        queue[2] = page_ref;
    }
    else if( victim == queue[1]){
        queue[1] = queue[2];
        queue[2] = page_ref;
    }
    else
        queue[2]=page_ref;
    return victim;
}

int victim_mfu(int page_ref){
    int victim = queue[0];
    if(frequency[victim]<frequency[queue[1]])
        victim=queue[1];
    if(frequency[victim]<frequency[queue[2]])
        victim=queue[2];
    if(victim == queue[0]){
        queue[0]=queue[1];
        queue[1]=queue[2];
        queue[2] = page_ref;
    }
    else if( victim == queue[1]){
        queue[1] = queue[2];
        queue[2] = page_ref;
    }
    else
        queue[2]=page_ref;
    return victim;
}

int victim_optimal(int page_ref, int current_index){
    int next_ref[3] = {0};
    int max = 0;
    int victim;
    for(int i=0; i<3; i++){
        int j=current_index;
        while(reference_string[j]!= physical[i]){
            j++;
            next_ref[i]+=1;
        }
    }
    if(next_ref[1]>next_ref[max]){
        max =1;
    }
    if(next_ref[2]>next_ref[max]){
        max =2;
    }
    victim = queue[max];
    queue[max] = page_ref;
    
    return victim;
}

bool not_in_physical(int page_ref)
{
    for (int i = 0; i < 3; i++)
    {
        if (physical[i] == page_ref)
        {
            return false;
        }
    }
    return true;
}

bool physical_empty_frames()
{
    for (int i = 0; i < 3; i++)
    {
        if (physical[i] < 0)
            return true;
    }
    return false;
}

bool replaced(int victim, int page_ref)
{
    bool replacement_status = false;
    for (int i = 0; i < 3; i++)
    {
        if (physical[i] == victim)
        {
            physical[i] = page_ref;
            replacement_status = true;
        }
    }
    swap_count++;

    return replacement_status;
}

void generate_reference_string()
{
    srand(time(0));
    int page = rand() % 8;
    reference_string[0] = page;
    for (int i = 1; i < MAX_REF; i++)
    {
        int page_plus = page + 1;
        int page_minus = page - 1;
        if (page_plus > 7)
            page_plus = 0;
        if (page_minus < 0)
            page_minus = 7;

        switch (rand() % 10)
        {
        case (0 | 1):
            page = page_minus;
            break;
        case (2 | 3):
            break;
        case (4 | 5):
            page = page_plus;
            break;
        default:
            int prev_page = page;
            while (page == page_minus || page == page_plus || page == prev_page)
                page = rand() % 8;
        }
        reference_string[i] = page;
    }
}

void print_reference_string()
{
    for (int i = 0; i < MAX_REF; i++)
    {
        cout << reference_string[i] << " ";
    }
    cout << "\n";
}

void print_frames()
{
    for (int i = 0; i < 3; i++)
        if (physical[i] != -1)
            cout << setw(2) << physical[i];
}

void print_action(int victim, int page_ref)
{
    cout << right << setw(4) << victim << " evicted, " << page_ref << " entered";
}

#endif