#include <iostream>
#include <vector>

using namespace std;

// Helper to print results cleanly
void printResults(string name, const vector<int>& processes, const vector<int>& allocation) {
    cout << "\n--- " << name << " ---\n";
    cout << "Process\tSize\tBlock Index\n";
    for (int i = 0; i < processes.size(); i++) {
        cout << "P" << i + 1 << "\t" << processes[i] << "\t";
        if (allocation[i] != -1) cout << allocation[i] + 1 << "\n";
        else cout << "Not Allocated\n";
    }
}

// 1. First Fit
void firstFit(vector<int> blocks, vector<int> processes) {
    vector<int> alloc(processes.size(), -1);
    
    for (int i = 0; i < processes.size(); i++) {
        for (int j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= processes[i]) {
                alloc[i] = j;                 // Assign block
                blocks[j] -= processes[i];    // Reduce available memory
                break;                        // Move to next process
            }
        }
    }
    printResults("First Fit", processes, alloc);
}

// 2. Best Fit
void bestFit(vector<int> blocks, vector<int> processes) {
    vector<int> alloc(processes.size(), -1);
    
    for (int i = 0; i < processes.size(); i++) {
        int bestIdx = -1;
        for (int j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= processes[i]) {
                // If it's the first fit found, or smaller than the current best
                if (bestIdx == -1 || blocks[j] < blocks[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            alloc[i] = bestIdx;
            blocks[bestIdx] -= processes[i];
        }
    }
    printResults("Best Fit", processes, alloc);
}

// 3. Worst Fit
void worstFit(vector<int> blocks, vector<int> processes) {
    vector<int> alloc(processes.size(), -1);
    
    for (int i = 0; i < processes.size(); i++) {
        int worstIdx = -1;
        for (int j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= processes[i]) {
                // If it's the first fit found, or larger than the current worst
                if (worstIdx == -1 || blocks[j] > blocks[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            alloc[i] = worstIdx;
            blocks[worstIdx] -= processes[i];
        }
    }
    printResults("Worst Fit", processes, alloc);
}

// 4. Next Fit
void nextFit(vector<int> blocks, vector<int> processes) {
    vector<int> alloc(processes.size(), -1);
    int lastAllocated = 0; // Pointer to remember where we left off
    int n = blocks.size();

    for (int i = 0; i < processes.size(); i++) {
        // Check all blocks starting from lastAllocated
        for (int j = 0; j < n; j++) {
            // Circular modulo math ensures we wrap around to index 0 if needed
            int idx = (lastAllocated + j) % n; 
            
            if (blocks[idx] >= processes[i]) {
                alloc[i] = idx;
                blocks[idx] -= processes[i];
                lastAllocated = idx; // Update the pointer
                break;
            }
        }
    }
    printResults("Next Fit", processes, alloc);
}

int main() {
    // Standard textbook data
    vector<int> memoryBlocks = {100, 500, 200, 300, 600};
    vector<int> processSizes = {212, 417, 112, 426};

    // Because we pass by value, the original sizes are untouched for each run
    firstFit(memoryBlocks, processSizes);
    bestFit(memoryBlocks, processSizes);
    worstFit(memoryBlocks, processSizes);
    nextFit(memoryBlocks, processSizes);

    return 0;
}