#include <iostream>
#include <queue>

using namespace std;

void printMetrics(string name, int n, int at[], int bt[], int ct[]) {
    cout << "\n--- " << name << " ---\n";
    cout << "P\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        int tat = ct[i] - at[i];      // TAT = CT - AT
        int wt = tat - bt[i];         // WT = TAT - BT
        cout << "P" << i << "\t" << at[i] << "\t" << bt[i] << "\t" 
             << ct[i] << "\t" << tat << "\t" << wt << "\n";
    }
}

void fcfs(int n, int at[], int bt[]) {
    int ct[10], time = 0;
    for (int i = 0; i < n; i++) {
        if (time < at[i]) time = at[i]; // Wait if CPU is idle
        time += bt[i];                  // Run process
        ct[i] = time;                   // Record completion
    }
    printMetrics("FCFS", n, at, bt, ct);
}

void sjf(int n, int at[], int bt[]) {
    int ct[10], rt[10];
    for (int i = 0; i < n; i++) rt[i] = bt[i]; // Use rt to track if done
    
    int time = 0, done = 0;
    while (done < n) {
        int idx = -1, min_val = 9999;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 && bt[i] < min_val) {
                min_val = bt[i]; idx = i;
            }
        }
        if (idx != -1) {
            time += bt[idx];   // Giant Leap (Run completely)
            ct[idx] = time;
            rt[idx] = 0;       // Mark done
            done++;
        } else time++;
    }
    printMetrics("SJF (Non-Preemptive)", n, at, bt, ct);
}

void srtf(int n, int at[], int bt[]) {
    int ct[10], rt[10];
    for (int i = 0; i < n; i++) rt[i] = bt[i];
    
    int time = 0, done = 0;
    while (done < n) {
        int idx = -1, min_val = 9999;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 && rt[i] < min_val) {
                min_val = rt[i]; idx = i;
            }
        }
        if (idx != -1) {
            rt[idx]--;         // Baby Step (Run 1 tick)
            time++;
            if (rt[idx] == 0) { 
                ct[idx] = time; 
                done++; 
            }
        } else time++;
    }
    printMetrics("SRTF (Preemptive SJF)", n, at, bt, ct);
}

void priorityNP(int n, int at[], int bt[], int pri[]) {
    int ct[10], rt[10];
    for (int i = 0; i < n; i++) rt[i] = bt[i];
    
    int time = 0, done = 0;
    while (done < n) {
        int idx = -1, min_val = 9999;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 && pri[i] < min_val) {
                min_val = pri[i]; idx = i; // ONLY LINE CHANGED FROM SJF
            }
        }
        if (idx != -1) {
            time += bt[idx];
            ct[idx] = time;
            rt[idx] = 0;
            done++;
        } else time++;
    }
    printMetrics("Priority (Non-Preemptive)", n, at, bt, ct);
}

void priorityP(int n, int at[], int bt[], int pri[]) {
    int ct[10], rt[10];
    for (int i = 0; i < n; i++) rt[i] = bt[i];
    
    int time = 0, done = 0;
    while (done < n) {
        int idx = -1, min_val = 9999;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 && pri[i] < min_val) {
                min_val = pri[i]; idx = i; // ONLY LINE CHANGED FROM SRTF
            }
        }
        if (idx != -1) {
            rt[idx]--;
            time++;
            if (rt[idx] == 0) { 
                ct[idx] = time; 
                done++; 
            }
        } else time++;
    }
    printMetrics("Priority (Preemptive)", n, at, bt, ct);
}

void rr(int n, int at[], int bt[], int tq) {
    int ct[10], rt[10];
    for (int i = 0; i < n; i++) rt[i] = bt[i];
    
    int time = at[0], done = 0;
    queue<int> q;
    bool in_q[10] = {false};
    
    q.push(0); in_q[0] = true; // Start with first process

    while (done < n) {
        if (q.empty()) {
            time++;
            for (int i = 0; i < n; i++) {
                if (at[i] <= time && rt[i] > 0 && !in_q[i]) {
                    q.push(i); in_q[i] = true;
                }
            }
            continue;
        }

        int i = q.front(); q.pop();
        int exec = (rt[i] < tq) ? rt[i] : tq; // Run for quantum OR remaining time
        rt[i] -= exec;
        time += exec;

        // Check who arrived while we were running
        for (int j = 0; j < n; j++) {
            if (at[j] <= time && rt[j] > 0 && !in_q[j]) {
                q.push(j); in_q[j] = true;
            }
        }

        // Put current process back in line if not done
        if (rt[i] > 0) {
            q.push(i);
        } else {
            ct[i] = time;
            done++;
        }
    }
    printMetrics("Round Robin", n, at, bt, ct);
}

int main() {
    int n = 4;
    int at[] = {0, 1, 2, 3};      // Arrival Times
    int bt[] = {8, 4, 9, 5};      // Burst Times
    int pri[] = {3, 1, 4, 2};     // Priorities (Lower number = higher priority)
    int tq = 3;                   // Time Quantum for Round Robin

    // Run all simulations
    fcfs(n, at, bt);
    sjf(n, at, bt);
    srtf(n, at, bt);
    priorityNP(n, at, bt, pri);
    priorityP(n, at, bt, pri);
    rr(n, at, bt, tq);

    return 0;
}