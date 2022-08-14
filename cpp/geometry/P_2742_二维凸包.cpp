#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<double, double>> point(n);
    for (int i = 0; i < n; i++) {
        cin >> point[i].first >> point[i].second;
    }
    sort(point.begin(), point.end(), [&](pair<double, double> a, pair<double, double> b) {
        return (a.second == b.second) ? (a.first < b.first) : (a.second < b.second);
    });
    auto judge = [&](int a, int b, int c) {
        return (point[a].second - point[b].second) * (point[b].first - point[c].first) > (point[a].first - point[b].first) * (point[b].second - point[c].second);
    };
    auto dis = [&](int a, int b) {
        return sqrt((point[a].first - point[b].first) * (point[a].first - point[b].first) + (point[a].second - point[b].second) * (point[a].second - point[b].second));
    };
    double ans = 0;
    vector<int> sta;
    sta.push_back(0), sta.push_back(1);
    for (int i = 2; i < n; i++) {
        while (sta.size() > 1 && !judge(i, sta[sta.size() - 1], sta[sta.size() - 2]))
            sta.pop_back();
        sta.push_back(i);
    }
    for (int i = 0; i < (int)sta.size() - 1; i++)
        ans += dis(sta[i], sta[i + 1]);
    sta.clear();
    sta.push_back(0), sta.push_back(1);
    for (int i = 2; i < n; i++) {
        while (sta.size() > 1 && judge(i, sta[sta.size() - 1], sta[sta.size() - 2]))
            sta.pop_back();
        sta.push_back(i);
    }
    for (int i = 0; i < (int)sta.size() - 1; i++)
        ans += dis(sta[i], sta[i + 1]);
    cout<<fixed<<setprecision(2)<<ans<<'\n';
    return 0;
}