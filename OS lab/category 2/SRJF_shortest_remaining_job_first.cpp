#include <bits/stdc++.h>
using namespace std;
#define slot 1
const int MAX_SIZE = 101; 

struct Process {
    int pid, at;
    int bt, wt;
    int tat, rt;
};

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n; cin >> n;
    vector<pair<int, int>> input(n);
    vector<Process> proc(n);

    for (int i=0; i<n; ++i) {
        cin >> input[i].first/*arrival time*/ >> input[i].second; /*brust time*/
        proc[i].pid = i+1;
        proc[i].at = input[i].first;
        proc[i].bt = input[i].second;
        proc[i].wt = 0;
        proc[i].tat = 0;
        proc[i].rt = proc[i].bt;
    }
    int ct = 0, i = 0;

    while (i<n) {
        sort(proc.begin(), proc.end(), [](const Process &a, const Process &b) {
            return a.rt<b.rt;
        });  // Sorting by remaining time
        if (!proc[i].rt) {
            proc[i].tat = ct; // ending time

            bool no_left = true;
            for (int j = i+1; j<n; ++j) {
                if (proc[j].rt) {
                    i = j;
                    no_left = false;
                    break;
                }
            }
            if (no_left) break;
        }
        if (proc[i].at > ct+1) {
            bool no_replacement = true;
            for (int j = i+1; j < n; ++j) {
                if (proc[j].at <= ct+1) {
                    swap(proc[i], proc[j]);
                    no_replacement = false;
                    break;
                }
            }
            if (no_replacement) { ct += slot;
                continue;
            }
        }
        proc[i].rt -= slot;
        ct += slot; // Update waiting time for remaining processes
        for (int j = i+1; j<n; ++j) {
            if (proc[j].rt && proc[j].at <= ct) proc[j].wt += slot;
        }
    }
    sort(proc.begin(), proc.end(), [](const Process &a, const Process &b) {
        return a.pid<b.pid; // Sorting by process ID
    });
    cout << "Process\t| Arrival Time \t| Burst Time \t| Waiting Time \t| Turn Around Time" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "P[" << proc[i].pid << "] \t| " << proc[i].at << " \t\t| "<< proc[i].bt << " \t\t| " << proc[i].wt << " \t\t| " << proc[i].tat << endl;
    }
    // Calculate average waiting time and turn around time
    int twt = 0, ttat = 0;
    for (int i = 0; i < n; ++i) {
        twt += proc[i].wt;
        ttat += proc[i].tat;
    }
    cout << fixed << setprecision(4);
    cout << "\nAverage Waiting Time: " << (float)twt / n << endl;
    cout << "Average Turn Around Time: " << (float)ttat / n << endl;

    return (EXIT_SUCCESS);
}