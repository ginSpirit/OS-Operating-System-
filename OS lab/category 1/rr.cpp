#include <bits/stdc++.h>
using namespace std;
const int SLOT = 4;

auto fx = [](int a, int b, int &c)-> int {
  int rt = b-SLOT;
  c = SLOT;
  if (rt>0) {return rt;}
  else {
    c += rt;
    return 0;
  }
};

auto turnAround =[](int a, int b, int c)->int {
  return a+b+c;
};

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n; cin >> n;
    unordered_map<int, int> mp;
    vector<tuple<int, int, int, int, int>> vt(n);

    for (int i=0; i<n; i++) {
        int x; cin >> x;
        mp[i+1] = x;
    }

    for (int i=0; i<n; i++) {
        get<0>(vt[i]) = i+1;
        get<1>(vt[i]) = mp[i+1];
        get<2>(vt[i]) = 0;
        get<3>(vt[i]) = 0;
        get<4>(vt[i]) = get<1>(vt[i]); 
    }

    int cnt = 0;
    while (any_of(vt.begin(), vt.end(), [](const auto& p) { return get<4>(p) > 0; })) {
        for (auto& i : vt) {
            if (!get<4>(i)) continue;

            int et, rt = fx(cnt, get<4>(i), et);
            if (rt > 0) {
                cnt += SLOT;
                get<4>(i) = rt;
            } else {
                cnt = turnAround(cnt, et, rt);
                get<4>(i) = 0;
                get<3>(i) = cnt;
            }

            auto updateWT = [&et](auto& x, const auto& y) {
                if (&x != &y && get<4>(x) > 0) {
                    get<2>(x) += et;
                }
            };
            for_each(vt.begin(), vt.end(), [&](auto& x) { updateWT(x, i); });
        }
    }

    cout << "Process \t| Burst Time \t| Waiting Time \t| Turn Around Time "<< endl;
    for (const auto& p : vt) {
        cout << "P[" << get<0>(p) << "] \t\t| " << get<1>(p) << " \t\t| " << get<2>(p) << " \t\t| " << get<3>(p) << endl;
    }

    auto calculate_avg_time = [](const vector<tuple<int, int, int, int, int>>& proc, int n) -> pair<float, float> {
        int turnAround_time = 0, totalTurnAround_Time = 0;
        for (const auto& p : proc) {
            turnAround_time += get<2>(p);
            totalTurnAround_Time += get<3>(p);
        }
        return make_pair(turnAround_time/(float)n, totalTurnAround_Time/(float)n);
    };

    auto [x, y] = calculate_avg_time(vt, n);
    cout << "Average Waiting Time: " << x << endl;
    cout << "Average Turn Around Time: " << y << endl;

    return (EXIT_SUCCESS);
}