#include <bits/stdc++.h>
using namespace std;

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n; cin >> n;

    vector<tuple<int, int, int, int>> vt(n);
    for (int i=0; i<n; i++) {
        int x; cin >> x;
        vt[i] = make_tuple(i+1, x, 0, 0);
    }
    sort(vt.begin(), vt.end(), [](const tuple<int, int, int, int> &a, const tuple<int, int, int, int> &b) {
        return get<1>(a) < get<1>(b);
    });
    int cnt = 0;
    for (int i=0; i<n; i++) {
        vt[i] = make_tuple(get<0>(vt[i]), get<1>(vt[i]), cnt, cnt + get<1>(vt[i]));
        cnt += get<1>(vt[i]);
    }

    sort(vt.begin(), vt.end(), [](const tuple<int, int, int, int> &a, const tuple<int, int, int, int> &b) {
        return get<0>(a) < get<0>(b);
    });

    cout << "Process | Burst Time\t| Waiting Time\t| Turn Around Time\n";
    for (const auto &p : vt) {
        cout << "P[" << get<0>(p) << "] \t| " << get<1>(p) << " \t\t| " << get<2>(p) << " \t\t| " << get<3>(p) << endl;
    } cout << endl;

    int twt = 0, ttat = 0;
    for (const auto &p : vt) {
        twt += get<2>(p);
        ttat += get<3>(p);
    }

    cout << fixed << setprecision(4);
    cout << "Average Waiting Time: " << static_cast<float>(twt) / n << endl;
    cout << "Average Turn Around Time: " << static_cast<float>(ttat) / n << endl;
    return (EXIT_SUCCESS);
}