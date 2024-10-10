#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define slot 1
const int MAX_SIZE = 101; 
const int N = 1e7 + 10;

struct Process {
    int pid, p, bt, wt, tat;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    
    int n; cin >> n;

    vector<Process> proc(n);
    for (int i = 0; i < n; i++) {
        cin >> proc[i].p >> proc[i].bt;
        proc[i].pid = i + 1;
        proc[i].wt = 0;
        proc[i].tat = 0;
    }
    auto ascending_p = [](const Process &a, const Process &b) {
        return a.p < b.p;
    }; //sort by priority

    auto asc_pid = [](const Process &a, const Process &b) {
        return a.pid < b.pid;
    }; //sort by prc ID

    sort(proc.begin(), proc.end(), ascending_p);
    int ct = 0;
    for (int i = 0; i < n; i++) {
        proc[i].wt = ct;
        ct += proc[i].bt;
        proc[i].tat = ct;
    }
    sort(proc.begin(), proc.end(), asc_pid);
    cout << "Process\t| Priority \t| Burst Time \t| Waiting Time \t| Turn Around Time" << endl;
    for (int i = 0; i < n; i++) {
        cout << "P[" << proc[i].pid << "] \t| " << proc[i].p << " \t\t| "
         << proc[i].bt << " \t\t| " << proc[i].wt << " \t\t | " << proc[i].tat << "\n";
    }
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
    }

    cout << "\nAverage Waiting Time: " << (float)total_wt / n << endl;
    cout << "Average Turn Around Time: " << (float)total_tat / n << endl;

    return (EXIT_SUCCESS);
}