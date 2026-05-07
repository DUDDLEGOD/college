#include <iostream>

using namespace std;

// 1. FIFO (The Modulo Hack)
void fifo(int pages[], int n, int frames) {
    int mem[10]; 
    for(int i = 0; i < frames; i++) mem[i] = -1; // -1 means empty
    
    int pointer = 0, faults = 0;

    for (int i = 0; i < n; i++) {
        bool hit = false;
        for (int j = 0; j < frames; j++) {
            if (mem[j] == pages[i]) hit = true;
        }
        
        if (!hit) { // FAULT
            mem[pointer] = pages[i];              // Overwrite oldest
            pointer = (pointer + 1) % frames;     // Move pointer forward (loops back to 0)
            faults++;
        }
    }
    cout << "FIFO Faults:    " << faults << "\n";
}

// 2. LRU (The Timer Hack)
void lru(int pages[], int n, int frames) {
    int mem[10], time[10] = {0}; 
    for(int i = 0; i < frames; i++) mem[i] = -1;
    
    int faults = 0, clock = 0;

    for (int i = 0; i < n; i++) {
        clock++;
        bool hit = false;
        
        for (int j = 0; j < frames; j++) {
            if (mem[j] == pages[i]) { 
                hit = true; 
                time[j] = clock; // HIT: Update its timestamp
            }
        }
        
        if (!hit) { // FAULT
            int victim = 0;
            // Find the frame with the smallest time (oldest)
            for (int j = 1; j < frames; j++) {
                if (time[j] < time[victim]) victim = j;
            }
            mem[victim] = pages[i]; // Overwrite victim
            time[victim] = clock;   // Set new timestamp
            faults++;
        }
    }
    cout << "LRU Faults:     " << faults << "\n";
}

// 3. OPTIMAL (The Forward-Look Hack)
void optimal(int pages[], int n, int frames) {
    int mem[10];
    for(int i = 0; i < frames; i++) mem[i] = -1;
    
    int faults = 0;

    for (int i = 0; i < n; i++) {
        bool hit = false;
        for (int j = 0; j < frames; j++) {
            if (mem[j] == pages[i]) hit = true;
        }
        
        if (!hit) { // FAULT
            int victim = 0, farthest = -1;
            
            // Check each frame in memory to see when it is used next
            for (int j = 0; j < frames; j++) {
                int next_use = 9999; // Assume infinity (never used again)
                
                // Look forward in the pages array
                for (int k = i + 1; k < n; k++) {
                    if (mem[j] == pages[k]) { 
                        next_use = k; 
                        break; 
                    }
                }
                
                // Track the one that is used farthest in the future
                if (next_use > farthest) {
                    farthest = next_use;
                    victim = j;
                }
            }
            mem[victim] = pages[i]; // Overwrite victim
            faults++;
        }
    }
    cout << "Optimal Faults: " << faults << "\n";
}

int main() {
    // Standard textbook reference string
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2};
    int n = sizeof(pages) / sizeof(pages[0]); // Automatically calculates array length
    int frames = 3;

    cout << "Simulating Page Replacement with " << frames << " frames...\n";
    cout << "------------------------------------------\n";

    fifo(pages, n, frames);
    lru(pages, n, frames);
    optimal(pages, n, frames);

    return 0;
}