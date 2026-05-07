#include <iostream>
#include <vector>

using namespace std;

// 1. FIRST FIT
void firstFit(vector<int> b, const vector<int>& p) {
    cout << "First Fit: ";
    for (int sz : p) {
        int idx = -1;
        for (int j = 0; j < b.size(); j++) {
            if (b[j] >= sz) { 
                idx = j; 
                break; // MAGIC LINE: Stop at the first one that fits
            }
        }
        if (idx != -1) { cout << "B" << idx << " "; b[idx] -= sz; }
        else cout << "Wait ";
    }
    cout << "\n";
}

// 2. BEST FIT
void bestFit(vector<int> b, const vector<int>& p) {
    cout << "Best Fit:  ";
    for (int sz : p) {
        int idx = -1;
        for (int j = 0; j < b.size(); j++) {
            if (b[j] >= sz) {
                // MAGIC LINE: Take it if it's the smallest one that fits
                if (idx == -1 || b[j] < b[idx]) idx = j; 
            }
        }
        if (idx != -1) { cout << "B" << idx << " "; b[idx] -= sz; }
        else cout << "Wait ";
    }
    cout << "\n";
}

// 3. WORST FIT
void worstFit(vector<int> b, const vector<int>& p) {
    cout << "Worst Fit: ";
    for (int sz : p) {
        int idx = -1;
        for (int j = 0; j < b.size(); j++) {
            if (b[j] >= sz) {
                // MAGIC LINE: Take it if it's the biggest one that fits
                if (idx == -1 || b[j] > b[idx]) idx = j; 
            }
        }
        if (idx != -1) { cout << "B" << idx << " "; b[idx] -= sz; }
        else cout << "Wait ";
    }
    cout << "\n";
}

int main() {
    vector<int> blocks = {100, 500, 200, 300, 600};
    vector<int> processes = {212, 417, 112, 426};

    // Because 'blocks' is passed by value, we don't need to reset it!
    firstFit(blocks, processes);
    bestFit(blocks, processes);
    worstFit(blocks, processes);

    return 0;
}