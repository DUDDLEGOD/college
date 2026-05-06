#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// P = Process, at = Arrival, bt = Burst, pri = Priority, rt = Remaining
// ct = Completion, tat = Turnaround, wt = Waiting
struct P { int id, at, bt, pri, rt, ct, tat, wt; };

// Super simple print function
void printStats(string name, vector<P>& p) {
    cout << "\n--- " << name << " ---\nID\tCT\tTAT\tWT\n";
    for(auto& x : p) cout << x.id << "\t" << x.ct << "\t" << x.tat << "\t" << x.wt << "\n";
}

// 1. FCFS (FIFO) - Assumes processes are sorted by arrival time
void fcfs(vector<P> p) {
    int time = 0;
    for(auto& x : p) {
        time = max(time, x.at) + x.bt;
        x.ct = time; 
        x.tat = x.ct - x.at; 
        x.wt = x.tat - x.bt;
    }
    printStats("FIFO (FCFS)", p);
}

// 2. SJF (Non-Preemptive)
void sjf(vector<P> p) {
    int time = 0, done = 0, n = p.size();
    while(done < n) {
        int idx = -1, min_bt = 1e9;
        for(int i = 0; i < n; i++) {
            if(p[i].rt > 0 && p[i].at <= time && p[i].bt < min_bt) {
                min_bt = p[i].bt; idx = i;
            }
        }
        if(idx != -1) {
            time += p[idx].bt;
            p[idx].rt = 0; // Mark as done
            done++;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        } else time++;
    }
    printStats("SJF (Non-Preemptive)", p);
}

// 3. SRTF (Preemptive SJF)
void srtf(vector<P> p) {
    int time = 0, done = 0, n = p.size();
    while(done < n) {
        int idx = -1, min_rt = 1e9;
        for(int i = 0; i < n; i++) {
            if(p[i].rt > 0 && p[i].at <= time && p[i].rt < min_rt) {
                min_rt = p[i].rt; idx = i;
            }
        }
        if(idx != -1) {
            p[idx].rt--; // Execute for 1 tick
            time++;
            if(p[idx].rt == 0) {
                done++;
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
            }
        } else time++;
    }
    printStats("SRTF (Preemptive)", p);
}

// 4. Priority (Non-Preemptive) - Lower number = higher priority
void priorityNP(vector<P> p) {
    int time = 0, done = 0, n = p.size();
    while(done < n) {
        int idx = -1, min_pri = 1e9;
        for(int i = 0; i < n; i++) {
            if(p[i].rt > 0 && p[i].at <= time && p[i].pri < min_pri) {
                min_pri = p[i].pri; idx = i;
            }
        }
        if(idx != -1) {
            time += p[idx].bt;
            p[idx].rt = 0; // Mark as done
            done++;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        } else time++;
    }
    printStats("Priority (Non-Preemptive)", p);
}

// 5. Priority (Preemptive)
void priorityP(vector<P> p) {
    int time = 0, done = 0, n = p.size();
    while(done < n) {
        int idx = -1, min_pri = 1e9;
        for(int i = 0; i < n; i++) {
            if(p[i].rt > 0 && p[i].at <= time && p[i].pri < min_pri) {
                min_pri = p[i].pri; idx = i;
            }
        }
        if(idx != -1) {
            p[idx].rt--; // Execute for 1 tick
            time++;
            if(p[idx].rt == 0) {
                done++;
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
            }
        } else time++;
    }
    printStats("Priority (Preemptive)", p);
}

// 6. Round Robin
void rr(vector<P> p, int tq) {
    int time = 0, done = 0, n = p.size();
    queue<int> q;
    vector<bool> inQ(n, false);
    
    // Start with the first process
    q.push(0); inQ[0] = true; time = p[0].at;

    while(done < n) {
        if(q.empty()) { time++; /* Fast forward time if idle */ }
        else {
            int i = q.front(); q.pop();
            int exec = min(p[i].rt, tq);
            p[i].rt -= exec;
            time += exec;
            
            // Check for new arrivals while this process was running
            for(int j = 0; j < n; j++) {
                if(p[j].at <= time && p[j].rt > 0 && !inQ[j]) {
                    q.push(j); inQ[j] = true;
                }
            }
            
            // Re-queue the current process if it's not done
            if(p[i].rt > 0) {
                q.push(i);
            } else {
                done++;
                p[i].ct = time;
                p[i].tat = p[i].ct - p[i].at;
                p[i].wt = p[i].tat - p[i].bt;
            }
        }
    }
    printStats("Round Robin", p);
}

int main() {
    // {id, AT, BT, Priority, RT (must equal BT initially), CT, TAT, WT}
    vector<P> processes = {
        {1, 0, 8, 3, 8, 0, 0, 0},
        {2, 1, 4, 1, 4, 0, 0, 0},
        {3, 2, 9, 4, 9, 0, 0, 0},
        {4, 3, 5, 2, 5, 0, 0, 0}
    };
    
    int timeQuantum = 3;

    fcfs(processes);
    sjf(processes);
    srtf(processes);
    priorityNP(processes);
    priorityP(processes);
    rr(processes, timeQuantum);

    return 0;
}