#include <iostream>

using namespace std;

// Shared variables for Peterson's Solution
bool flag[2] = {false, false};
int turn = 0;

// The shared resource
int shared_counter = 0;

void process0() {
    // 1. Show interest
    flag[0] = true;
    
    // 2. Be polite (give the turn to process 1)
    turn = 1;
    
    // 3. Wait if Process 1 is interested AND it is Process 1's turn
    // (In this single-threaded simulation, this loop will instantly pass)
    while (flag[1] && turn == 1) {
        // Busy wait
    }
    
    // --- CRITICAL SECTION START ---
    shared_counter++;
    cout << "P0 is in the critical section. Counter is now: " << shared_counter << "\n";
    // --- CRITICAL SECTION END ---
    
    // 4. Leave
    flag[0] = false;
}

void process1() {
    // 1. Show interest
    flag[1] = true;
    
    // 2. Be polite (give the turn to process 0)
    turn = 0;
    
    // 3. Wait if Process 0 is interested AND it is Process 0's turn
    while (flag[0] && turn == 0) {
        // Busy wait
    }
    
    // --- CRITICAL SECTION START ---
    shared_counter++;
    cout << "P1 is in the critical section. Counter is now: " << shared_counter << "\n";
    // --- CRITICAL SECTION END ---
    
    // 4. Leave
    flag[1] = false;
}

int main() {
    cout << "Starting non-threaded simulation of Peterson's Solution...\n\n";

    // Simulate the processes taking turns accessing the shared resource
    for (int i = 0; i < 3; i++) {
        process0();
        process1();
    }

    cout << "\nSimulation finished. Final counter value: " << shared_counter << "\n";

    return 0;
}