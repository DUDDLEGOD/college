#include <iostream>
#include <vector>

using namespace std;

class BankersAlgorithm {
private:
    int n; // Number of processes
    int m; // Number of resources
    vector<vector<int>> alloc, max, need;
    vector<int> avail;

public:
    // Constructor handles all the initial setup nicely
    BankersAlgorithm(vector<vector<int>> allocation, 
                     vector<vector<int>> maximum, 
                     vector<int> available) {
        
        alloc = allocation;
        max = maximum;
        avail = available;
        
        n = alloc.size();
        m = avail.size();
        
        // Size the Need matrix and calculate: Need = Max - Allocation
        need.assign(n, vector<int>(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                need[i][j] = max[i][j] - alloc[i][j];
            }
        }
    }

    // The core Safety check
    void printSafeSequence() {
        vector<int> work = avail;              // Step 1: Initialize Work
        vector<bool> finish(n, false);         // Step 1: Initialize Finish to false
        vector<int> safeSeq;

        int doneCount = 0;
        while (doneCount < n) {
            bool foundProcess = false;

            for (int i = 0; i < n; i++) {
                if (!finish[i]) {
                    
                    // Check if this process's Need <= Work
                    bool canRun = true;
                    for (int j = 0; j < m; j++) {
                        if (need[i][j] > work[j]) {
                            canRun = false;
                            break;
                        }
                    }

                    // If it can run, simulate execution
                    if (canRun) {
                        for (int j = 0; j < m; j++) {
                            work[j] += alloc[i][j]; // It finishes and returns resources
                        }
                        
                        safeSeq.push_back(i);       // Add to our safe path
                        finish[i] = true;           // Mark as done
                        foundProcess = true;        // We made progress!
                        doneCount++;
                    }
                }
            }

            // If we looped through all processes and couldn't find ANY that can run
            if (!foundProcess) {
                cout << "System is in an UNSAFE state! Deadlock is likely.\n";
                return; // Stop running
            }
        }

        // If we made it here, we found a safe path for everyone
        cout << "System is SAFE! \nSafe Sequence: ";
        for (int i : safeSeq) {
            cout << "P" << i << (i == safeSeq.back() ? "" : " -> ");
        }
        cout << "\n";
    }
};

int main() {
    // Standard textbook example data
    // 5 Processes (P0 to P4), 3 Resources (A, B, C)
    
    vector<int> available = {3, 3, 2}; // Resources currently available
    
    vector<vector<int>> maximum = {
        {7, 5, 3}, // P0
        {3, 2, 2}, // P1
        {9, 0, 2}, // P2
        {2, 2, 2}, // P3
        {4, 3, 3}  // P4
    };
    
    vector<vector<int>> allocation = {
        {0, 1, 0}, // P0
        {2, 0, 0}, // P1
        {3, 0, 2}, // P2
        {2, 1, 1}, // P3
        {0, 0, 2}  // P4
    };

    // Instantiate our class and run the check
    cout << "Initializing Banker's Algorithm...\n";
    BankersAlgorithm system(allocation, maximum, available);
    
    system.printSafeSequence();

    return 0;
}