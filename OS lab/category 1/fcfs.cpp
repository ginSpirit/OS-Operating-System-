#include <bits/stdc++.h>
using namespace std;
#define endl "\n"

const long long MOD = 1e9+7;
const int INF = 0x3f3f3f3f;

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n; cin >> n; //number of process

    using Elements = tuple<int, int, int, int>;
    vector<Elements> store(n);
    vector<int> v(n);


    for (int i=0; i<n; i++) {
        int x; cin >> x;
        store[i] = make_tuple(i+1, x, 0, 0);
        v[i] = i+1;
    }
    //Calculating {waiting, turnaround} time
    int cnt = 0;
    for_each(store.begin(), store.end(), [&](Elements& it) {
        int& idx_2 = get<2>(it);
        int& idx_1 = get<1>(it);
        int& idx_3 = get<3>(it);
        idx_2 = cnt;
        cnt += idx_1;
        idx_3 = cnt;
    });

    cout << "Process\t| Burst Time \t| Waiting Time \t| Turn Around Time" << endl;
    for_each(store.begin(), store.end(), [](const Elements& it) {
        cout << "P[" << get<0>(it) << "] \t| " << get<1>(it) << " \t\t| " << get<2>(it) << " \t\t| " << get<3>(it) << '\n';
    });
    auto avgWaiting_TurnAtime = accumulate(store.begin(), store.end(), 0, [](int sum, const Elements& it) {
        return sum + get<2>(it); // returning {average waiting, turnaround} time
    });
    auto __turnAround = accumulate(store.begin(), store.end(), 0, [](int sum, const Elements& it) {
        return sum + get<3>(it);
    });

    cout << "Average Waiting Time: " << avgWaiting_TurnAtime/(float)n << endl;
    cout << "Average Turn Around Time: " <<__turnAround/(float)n << endl;

    return (EXIT_SUCCESS);
}