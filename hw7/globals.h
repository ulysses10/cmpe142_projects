#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

// *** Stuff to help in printing graph ***
enum algorithm
{
    fcfs,
    sstf,
    scan,
    look,
    cscan,
    clook
};
string alg[] = {"First Come First Serve", "Shortest Seek Time First", "Scan", "Circular Scan", "Look", "Circular Look"};
const int ordered_queue[10] = {256, 513, 1175, 1401, 1680, 2055, 2304, 2700, 3692, 4922};
// ***

// Useful items to use in scheduling algorithms
const int queue[10] = {2055, 1175, 2304, 2700, 513, 1680, 256, 1401, 4922, 3692};
const int width[10] = {57, 27, 77, 87, 17, 47, 7, 37, 107, 97};
const int drive_head = 2255;
const int MAX_CYLINDER = 4999;
const int MIN_CYLINDER = 0;
int schedule[10];      // This array can be used to hold the order of the requests based on the algorithm
int ordered_width[10]; // To hold the new width order used in printing

void print_graph(int algorithm, int moves)
{
    cout << "\n"
         << alg[algorithm] << ":\n\n";
    cout << "0";
    for (int i = 0; i < 10; i++)
    {
        cout << setfill('.') << setw(10);
        cout << ordered_queue[i];
        if (i == 5)
            cout << setfill('.') << setw(10) << drive_head;
        if (i == 9)
            cout << setfill('.') << setw(10) << MAX_CYLINDER << "\n";
    }
    cout << setfill(' ') << setw(73) << "*2255\n\n";

    for (int i = 0; i < 10; i++)
    {
        cout << setw(ordered_width[i]) << "*" << schedule[i] << "\n\n";
    }

    cout << "Total head movement: " << moves << " cylinders\n\n";
}

void fcfs_scheduling()
{
    int total_movement = 0;
    int previous_position = drive_head;
    for (int i = 0; i < 10; i++)
    {
        schedule[i] = queue[i];
        ordered_width[i] = width[i];
        if (queue[i] > previous_position)
            total_movement = total_movement + (queue[i] - previous_position);
        else
            total_movement = total_movement + (previous_position - queue[i]);
        previous_position = queue[i];
    }
    print_graph(fcfs, total_movement);
}

void sstf_scheduling()
{
    int total_movement = 0;
    int previous_position = drive_head;
    int min_index = 0;
    int min_seek = 10000;
    int min_cylinder;
    int x = 10;
    int min_width;
    int q[10] = {2055, 1175, 2304, 2700, 513, 1680, 256, 1401, 4922, 3692};
    int w[10] = {57, 27, 77, 87, 17, 47, 7, 37, 107, 97};
    for (int i = 0; i < 10; i++)
    {

        // find min seek time
        for (int j = 0; j < x; j++)
        {
            if (abs(previous_position - q[j]) < min_seek)
            {
                min_cylinder = q[j];
                min_seek = abs(previous_position - min_cylinder);
                min_index = j;
                min_width = w[j];
            }
        }
        // "remove" min_cylinder
        for (int j = min_index; j < x - 1; j++)
        {
            q[j] = q[j + 1];
            w[j] = w[j + 1];
        }
        x--;
        // add to schedule
        schedule[i] = min_cylinder;
        ordered_width[i] = min_width;
        total_movement = total_movement + abs(previous_position - min_cylinder);

        // "reset" trackers
        min_seek = 10000;
        previous_position = min_cylinder;
    }
    print_graph(sstf, total_movement);
}

void scan_scheduling(){

    for(int i=0; i<10; i++){
        //wip
    }
}

#endif