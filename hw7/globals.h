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
    cscan,
    look,

    clook
};
string alg[] = {"First Come First Serve", "Shortest Seek Time First", "Scan", "Circular Scan", "Look", "Circular Look"};
const int ordered_queue[10] = {256, 513, 1175, 1401, 1680, 2055, 2304, 2700, 3692, 4922};
// ***

// Useful items to use in scheduling algorithms
const int queue[10] = {2055, 1175, 2304, 2700, 513, 1680, 256, 1401, 4922, 3692};
const int width[10] = {57, 27, 77, 87, 17, 47, 7, 37, 107, 97};
// const int edges[2] = {0, 4999};
// const int edge_width[2] = {1, 117};
const int drive_head = 2255;
const int MAX_CYLINDER = 4999;
const int MIN_CYLINDER = 0;

void print_graph(int algorithm, int moves, int length, int schedule[], int ordered_width[])
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

    for (int i = 0; i < length; i++)
    {
        cout << setw(ordered_width[i]) << "*" << schedule[i] << "\n\n";
    }

    cout << "Total head movement: " << moves << " cylinders\n\n";
}

void fcfs_scheduling()
{
    int length = 10;
    int schedule[length];
    int ordered_width[length];
    int total_movement = 0;
    int previous_position = drive_head;
    for (int i = 0; i < 10; i++)
    {
        schedule[i] = queue[i];
        ordered_width[i] = width[i];
        total_movement = total_movement + abs(previous_position - queue[i]);
    }
    print_graph(fcfs, total_movement, length, schedule, ordered_width);
}

void sstf_scheduling()
{
    int length = 10;
    int schedule[length];
    int ordered_width[length];
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
    print_graph(sstf, total_movement, length, schedule, ordered_width);
}

void scan_scheduling()
{
    int length = 11;
    int schedule[11] = {0, 2055, 1175, 2304, 2700, 513, 1680, 256, 1401, 4922, 3692};
    int ordered_width[11] = {1, 57, 27, 77, 87, 17, 47, 7, 37, 107, 97};
    int total_movement = 0;
    int previous_position = drive_head;
    int temp_q, temp_w;

    // Sort array in ascending order
    for (int i = 1; i < 11; i++)
    {
        int s_key = schedule[i];
        int w_key = ordered_width[i];
        int j = i - 1;
        while (j >= 0 && schedule[j] > s_key) // -- for non increasing order: a[j]<key
        {
            schedule[j + 1] = schedule[j];
            ordered_width[j + 1] = ordered_width[j];
            j -= 1;
        }
        schedule[j + 1] = s_key;
        ordered_width[j + 1] = w_key;
    }

    // Sort left side of head in descending order
    //  -- Find midpoint
    int mid = 0;
    while (schedule[mid] < drive_head)
        mid++;

    // Sort array in ascending order
    for (int i = 1; i < mid; i++)
    {
        int s_key = schedule[i];
        int w_key = ordered_width[i];
        int j = i - 1;
        while (j >= 0 && schedule[j] < s_key) // -- for non increasing order: a[j]<key
        {
            schedule[j + 1] = schedule[j];
            ordered_width[j + 1] = ordered_width[j];
            j -= 1;
        }
        schedule[j + 1] = s_key;
        ordered_width[j + 1] = w_key;
    }

    //calculate
    for (int i = 0; i < length; i++)
    {
        total_movement = total_movement + abs(previous_position - schedule[i]);
        previous_position = schedule[i];
    }

    print_graph(scan, total_movement, length, schedule, ordered_width);
}

void cscan_scheduling()
{
    int length = 12;
    int schedule[12] = {0, 4999, 2055, 1175, 2304, 2700, 513, 1680, 256, 1401, 4922, 3692};
    int ordered_width[12] = {1, 117, 57, 27, 77, 87, 17, 47, 7, 37, 107, 97};
    int total_movement = 0;
    int previous_position = drive_head;
    int temp_q, temp_w;

    // Sort array in ascending order
    for (int i = 1; i < 12; i++)
    {
        int s_key = schedule[i];
        int w_key = ordered_width[i];
        int j = i - 1;
        while (j >= 0 && schedule[j] > s_key) // -- for non increasing order: a[j]<key
        {
            schedule[j + 1] = schedule[j];
            ordered_width[j + 1] = ordered_width[j];
            j -= 1;
        }
        schedule[j + 1] = s_key;
        ordered_width[j + 1] = w_key;
    }

    // Sort left side of head in descending order
    //  -- Find midpoint
    int mid = 0;
    while (schedule[mid] < drive_head)
        mid++;

    // Sort array in ascending order
    for (int i = 1; i < mid; i++)
    {
        int s_key = schedule[i];
        int w_key = ordered_width[i];
        int j = i - 1;
        while (j >= 0 && schedule[j] < s_key) // -- for non increasing order: a[j]<key
        {
            schedule[j + 1] = schedule[j];
            ordered_width[j + 1] = ordered_width[j];
            j -= 1;
        }
        schedule[j + 1] = s_key;
        ordered_width[j + 1] = w_key;
    }

    // Sort array in ascending order
    for (int i = mid + 1; i < 12; i++)
    {
        int s_key = schedule[i];
        int w_key = ordered_width[i];
        int j = i - 1;
        while (j >= mid && schedule[j] < s_key) // -- for non increasing order: a[j]<key
        {
            schedule[j + 1] = schedule[j];
            ordered_width[j + 1] = ordered_width[j];
            j -= 1;
        }
        schedule[j + 1] = s_key;
        ordered_width[j + 1] = w_key;
    }
    // calculate total head movement
    for (int i = 0; i < length; i++)
    {
        total_movement = total_movement + abs(previous_position - schedule[i]);
        previous_position = schedule[i];
    }
    print_graph(cscan, total_movement, length, schedule, ordered_width);
}

void look_scheduling()
{
    int length = 10;
    int schedule[10] = {2055, 1175, 2304, 2700, 513, 1680, 256, 1401, 4922, 3692};
    int ordered_width[10] = {57, 27, 77, 87, 17, 47, 7, 37, 107, 97};
    int total_movement = 0;
    int previous_position = drive_head;
    int temp_q, temp_w;

    // Sort array in ascending order
    for (int i = 1; i < 10; i++)
    {
        int s_key = schedule[i];
        int w_key = ordered_width[i];
        int j = i - 1;
        while (j >= 0 && schedule[j] > s_key) // -- for non increasing order: a[j]<key
        {
            schedule[j + 1] = schedule[j];
            ordered_width[j + 1] = ordered_width[j];
            j -= 1;
        }
        schedule[j + 1] = s_key;
        ordered_width[j + 1] = w_key;
    }

    // Sort left side of head in descending order
    //  -- Find midpoint
    int mid = 0;
    while (schedule[mid] < drive_head)
        mid++;

    // Sort array in ascending order
    for (int i = 1; i < mid; i++)
    {
        int s_key = schedule[i];
        int w_key = ordered_width[i];
        int j = i - 1;
        while (j >= 0 && schedule[j] < s_key) // -- for non increasing order: a[j]<key
        {
            schedule[j + 1] = schedule[j];
            ordered_width[j + 1] = ordered_width[j];
            j -= 1;
        }
        schedule[j + 1] = s_key;
        ordered_width[j + 1] = w_key;
    }
    // calculate total head movement
    for (int i = 0; i < length; i++)
    {
        total_movement = total_movement + abs(previous_position - schedule[i]);
        previous_position = schedule[i];
    }
    print_graph(look, total_movement, length, schedule, ordered_width);
}

void clook_scheduling()
{
    int length = 10;
    int schedule[10] = {2055, 1175, 2304, 2700, 513, 1680, 256, 1401, 4922, 3692};
    int ordered_width[10] = {57, 27, 77, 87, 17, 47, 7, 37, 107, 97};
    int total_movement = 0;
    int previous_position = drive_head;
    int temp_q, temp_w;

    // Sort array in ascending order
    for (int i = 1; i < 10; i++)
    {
        int s_key = schedule[i];
        int w_key = ordered_width[i];
        int j = i - 1;
        while (j >= 0 && schedule[j] > s_key) // -- for non increasing order: a[j]<key
        {
            schedule[j + 1] = schedule[j];
            ordered_width[j + 1] = ordered_width[j];
            j -= 1;
        }
        schedule[j + 1] = s_key;
        ordered_width[j + 1] = w_key;
    }

    // Sort left side of head in descending order
    //  -- Find midpoint
    int mid = 0;
    while (schedule[mid] < drive_head)
        mid++;

    // Sort array in ascending order
    for (int i = 1; i < mid; i++)
    {
        int s_key = schedule[i];
        int w_key = ordered_width[i];
        int j = i - 1;
        while (j >= 0 && schedule[j] < s_key) // -- for non increasing order: a[j]<key
        {
            schedule[j + 1] = schedule[j];
            ordered_width[j + 1] = ordered_width[j];
            j -= 1;
        }
        schedule[j + 1] = s_key;
        ordered_width[j + 1] = w_key;
    }

    // Sort array in ascending order
    for (int i = mid + 1; i < 10; i++)
    {
        int s_key = schedule[i];
        int w_key = ordered_width[i];
        int j = i - 1;
        while (j >= mid && schedule[j] < s_key) // -- for non increasing order: a[j]<key
        {
            schedule[j + 1] = schedule[j];
            ordered_width[j + 1] = ordered_width[j];
            j -= 1;
        }
        schedule[j + 1] = s_key;
        ordered_width[j + 1] = w_key;
    }
    // calculate total head movement
    for (int i = 0; i < length; i++)
    {
        total_movement = total_movement + abs(previous_position - schedule[i]);
        previous_position = schedule[i];
    }
    print_graph(clook, total_movement, length, schedule, ordered_width);
}
#endif