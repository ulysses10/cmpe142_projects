#include "globals.h"

int main()
{
    // Generate a string of 100 page references
    generate_reference_string();
    // int a =lru; // set a to algorithm to be tested; look at enum in globals
    for (int a = 0; a < 6; a++)
    {
        swap_count = 0;
        hit_count = 0;
        // setup physical memory with "empty" frames
        for (int i = 0; i < 3; i++)
            physical[i] = -1;
        int x = 0;

        cout << "Ref" << setw(8) << "Frames" << setw(10) << "Action\n";

        for (int i = 0; i < MAX_REF; i++)
        {
            int page_ref = reference_string[i];
            frequency[page_ref]++;

            cout << setw(4) << left << page_ref << " ";
            if (physical_empty_frames() && not_in_physical(page_ref))
            {
                // For first references the physical memory will most likely be empty
                // so just insert the first 3 unique page reference into physical
                physical[x] = page_ref;
                queue[x] = page_ref; // queue is also filled with first 3 unique references
                x++;
                for (int i = 0; i < x; i++)
                    cout << setw(2) << physical[i];
            }
            else if (not_in_physical(page_ref))
            {
                // page fault: page replacement is needed
                // Choose victim page based on algorithm
                // This is where you call your algorithm function
                // ex:
                int victim;
                switch (a)
                {
                case fifo:
                    victim = victim_fifo(page_ref);
                    break;
                case sc:
                    victim = victim_fifo(page_ref);
                    break;
                case rndm:
                    victim = victim_random();
                    break;
                case opt:
                    victim = victim_optimal(page_ref, i);
                    break;
                case lfu:
                    victim = victim_lfu(page_ref);
                    break;
                case mfu:
                    victim = victim_mfu(page_ref);
                    break;
                case lru:
                    victim = victim_lru(page_ref);
                    break;
                }

                // reset last used of ref page to zero
                last_used[victim] = 0;

                // replace victim with page_ref
                if (replaced(victim, page_ref))
                {
                    print_frames();
                    print_action(victim, page_ref);
                }
            }
            else
            {
                // if second chance being used:
                if (a == sc)
                {
                    second_chance(page_ref);
                }

                // reset last used of ref page to zero
                last_used[page_ref] = 0;

                // no action: reference page is in physical memory
                print_frames();
                hit_count++;
            }
            for (int j = 0; j < x; j++)
            {
                last_used[queue[j]] += 1;
            }
            cout << "\n";
        }
        switch (a)
        {
        case fifo:
            cout << "Stats for First In First Out: \n";
            break;
        case sc:
            cout << "Stats for Second Chance: \n";
            break;
        case rndm:
            cout << "Stats for Random: \n";
            break;
        case opt:
            cout << "Stats for Optimal: \n";
            break;
        case lfu:
            cout << "Stats for Least Frequently Used: \n";
            break;
        case mfu:
            cout << "Stats for Most Frequently Used: \n";
            break;
        case lru:
            cout << "Stats for Least Recently Used: \n";
            break;
        }
        cout << "Total swaps: " << swap_count << "\n";
        cout << "Hit ratio: " << hit_count << "%\n";
        cout << "****************************************************\n\n";
    }

    return 0;
}