#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

// We use 'atomic' so the compiler doesn't optimize away our while loop
atomic<bool> flag[2] = {false, false};
atomic<int> turn = 0;

// The shared resource we want to protect
int shared_counter = 0; 

void p0() {
    for (int i = 0; i < 10000; i++) {
        flag[0] = true;
        turn = 1;
        while (flag[1] && turn == 1); // Wait
        
        shared_counter++; // CRITICAL SECTION
        
        flag[0] = false;
    }
}

void p1() {
    for (int i = 0; i < 10000; i++) {
        flag[1] = true;
        turn = 0;
        while (flag[0] && turn == 0); // Wait
        
        shared_counter++; // CRITICAL SECTION
        
        flag[1] = false;
    }
}

int main() {
    // Start both threads at the same time
    thread t1(p0);
    thread t2(p1);

    // Wait for both to finish
    t1.join();
    t2.join();

    // Since each thread adds 10,000, the result should always be exactly 20,000.
    // If Peterson's solution didn't work, this number would be lower due to race conditions.
    cout << "Final counter value: " << shared_counter << "\n";
    
    return 0;
}
