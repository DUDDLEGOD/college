#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Helper to print standard metrics cleanly
void printMetrics(string name, int faults, int hits) {
    int total = faults + hits;
    cout << "\n--- " << name << " ---\n";
    cout << "Total Pages: " << total << "\n";
    cout << "Page Faults: " << faults << "\n";
    cout << "Page Hits  : " << hits << "\n";
    cout << "Hit Ratio  : " << (float)hits / total * 100 << "%\n";
}

// 1. First-In, First-Out (FIFO)
void fifo(const vector<int>& pages, int frames) {
    unordered_set<int> memory; // Fast lookup for hits
    queue<int> arrival_order;  // Tracks who arrived first
    int faults = 0, hits = 0;

    for (int p : pages) {
        // HIT: Page is already in memory
        if (memory.count(p)) {
            hits++;
        } 
        // FAULT: Page not in memory
        else {
            faults++;
            // If memory is full, remove the oldest page
            if (memory.size() == frames) {
                int victim = arrival_order.front();
                arrival_order.pop();
                memory.erase(victim);
            }
            // Bring new page into memory
            memory.insert(p);
            arrival_order.push(p);
        }
    }
    printMetrics("FIFO", faults, hits);
}

// 2. Least Recently Used (LRU)
void lru(const vector<int>& pages, int frames) {
    vector<int> memory; // Back = newest, Front = oldest
    int faults = 0, hits = 0;

    for (int p : pages) {
        auto it = find(memory.begin(), memory.end(), p);

        // HIT: Page found
        if (it != memory.end()) {
            hits++;
            // Remove it from current spot and put it at the back (most recently used)
            memory.erase(it);
            memory.push_back(p);
        } 
        // FAULT: Page not found
        else {
            faults++;
            // If full, remove the front element (least recently used)
            if (memory.size() == frames) {
                memory.erase(memory.begin());
            }
            // Add new page to the back
            memory.push_back(p);
        }
    }
    printMetrics("LRU", faults, hits);
}

int main() {
    // Standard textbook reference string
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int frames = 3; // Number of memory slots available

    cout << "Simulating with " << frames << " memory frames...\n";

    fifo(pages, frames);
    lru(pages, frames);

    return 0;
}