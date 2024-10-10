#include <bits/stdc++.h>
#define SLOT 4
using namespace std;

class Process {
public:
    int pid, p, bt, wt, tat, rt;
    Process() : pid(0), p(0), bt(0), wt(0), tat(0), rt(0) {}
};
bool asc_pid(const Process& a, const Process& b) {
    return a.pid < b.pid;
}
bool asc_p(const Process& a, const Process& b) {
    return a.p < b.p;
}

class Scheduler {
private:
    int n;
    Process proc[100];

public:
    Scheduler(int n) : n(n) {}
    void input() {
        for (int i = 0; i < n; i++) {
            cin >> proc[i].p >> proc[i].bt;
            proc[i].pid = i + 1;
            proc[i].wt = 0;
            proc[i].tat = 0;
            proc[i].rt = proc[i].bt;
        }
    }
    void print_proc() {
        cout << "Process | Priority | Burst Time | Waiting Time | Turn Around Time\n";
        for (int i = 0; i < n; i++) {
            cout << "P[" <<proc[i].pid<< "] \t| " <<proc[i].p<< " \t| " 
                 <<proc[i].bt<< " \t| " <<proc[i].wt<< " \t| " <<proc[i].tat<< "\n";
        }
    }
    void execute_proc(Process* f_proc[], int count, int& ct) {
        if (ct)
            for (int i = 0; i < count; i++)
                f_proc[i]->wt = ct;

        while (true) {
            bool no_left = true;
            for (int i = 0; i < count; i++)
                if (f_proc[i]->rt) { no_left = false; break; }

            if (no_left) break;

            for (int i = 0; i < count; i++) {
                if (!f_proc[i]->rt) continue;

                int et = SLOT;
                int rt = f_proc[i]->rt - SLOT;
                if (rt > 0) {
                    ct += SLOT;
                    f_proc[i]->rt = rt;
                } else {
                    ct += et + rt;
                    f_proc[i]->rt = 0;
                    et = SLOT + rt;
                    f_proc[i]->tat = ct;
                }
                for (int j = 0; j < count; j++)
                    if (j != i && f_proc[j]->rt)
                        f_proc[j]->wt += et;
            }
        }
    }

    void schedule_execution() {
        sort(proc, proc + n, asc_p);

        int i = 0, prevt = 0, count = 0;
        int curr_p = proc[0].p;
        Process* f_proc[100];

        while (i <= n) {
            if (curr_p != proc[i].p || i == n) {
                execute_proc(f_proc, count, prevt);
                if (i == n) break;

                for (int j = 0; j < count; j++)
                    prevt = max(prevt, f_proc[j]->tat);
                curr_p = proc[i].p;
                count = 0;
            }
            f_proc[count++] = &proc[i++];
        }
    }

    void avg_time() {
        int twt = 0, ttat = 0;
        for (int i = 0; i < n; i++) {
            twt += proc[i].wt;
            ttat += proc[i].tat;
        }
        cout << "Average Waiting Time: " << (float)twt/n << "\n";
        cout << "Average Turn Around Time: " << (float)ttat/n << "\n";
    }
    void run() {
        input();
        schedule_execution();
        sort(proc, proc + n, asc_pid);
        print_proc();
        cout << "\n";
        avg_time();
    }
};

int main() {
    int n; cin >> n;
    Scheduler scheduler(n);
    scheduler.run();
    return 0;
}