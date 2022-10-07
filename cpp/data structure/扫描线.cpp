/*
    p5490扫描线 https://www.luogu.com.cn/problem/P5490
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class SegTree {
#define ls (i << 1)
#define rs (i << 1 | 1)
   public:
    struct Node {
        int left, right, cnt, len;
        Node()
            : left(0), right(0), cnt(0), len(0) {}
    };
    vector<Node> tr;
    vector<int> X;
    inline void push_up(int i, int l, int r) {
        if (tr[i].cnt)
            tr[i].len = X[r + 1] - X[l];
        else
            tr[i].len = tr[ls].len + tr[rs].len;
    }

    SegTree(const int& N)
        : tr(N << 2), X(1) {}

    // 注意：tr[i] 对应 [X[l], X[r+1]] 这条线段
    inline void edit(int i, int l, int r, int L, int R, int k) {
        if (X[r + 1] <= L || X[l] >= R)
            return;
        if (X[r + 1] <= R && X[l] >= L) {
            tr[i].cnt += k;
            push_up(i, l, r);
            return;
        }
        int mid = (l + r) >> 1;
        edit(ls, l, mid, L, R, k);
        edit(rs, mid + 1, r, L, R, k);
        push_up(i, l, r);
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    set<int> se;
    vector<tuple<int, int, int, int>> line;
    for (int i = 0; i < n; ++i) {
        int xa, xb, ya, yb;
        cin >> xa >> ya >> xb >> yb;
        se.insert(xa);
        se.insert(xb);
        line.emplace_back(make_tuple(xa, xb, ya, 1));
        line.emplace_back(make_tuple(xa, xb, yb, -1));
    }
    int tot = se.size();
    SegTree T = SegTree(tot << 1);
    for (auto& x : se)
        T.X.emplace_back(x);
    sort(line.begin(), line.end(), [&](tuple<int, int, int, int>& t1, tuple<int, int, int, int>& t2) {
        return get<2>(t1) < get<2>(t2);
    });
    ll ans = 0;
    for (int i = 0; i < n + n - 1; ++i) {
        T.edit(1, 1, tot - 1, get<0>(line[i]), get<1>(line[i]), get<3>(line[i]));
        ans += 1LL * T.tr[1].len * (get<2>(line[i + 1]) - get<2>(line[i]));
    }
    cout << ans << '\n';
    return 0;
}
