/*
匈牙利算法
usage:
for(int i=1;i<=n;++i) {
    idx ++;
    if(Hungary(i)) {
        cnt ++;
    }
}
*/
int idx = 0;
vector<int> have(n + 1), used(n + 1);
function<bool(int)> Hungary = [&](int u) {
    for (auto&& v : e[u]) {
        if (used[v] != idx) {
            used[v] = idx;
            if (!have[v] || Hungary(have[v])) {
                have[v] = u;
                return true;
            }
        }
    }
    return false;
};

// 二分图判定
vector<int> colr(n + 1);
function<bool(int, int)> isbg = [&](int u, int col) {
    colr[u] = col;
    for (auto&& v : e[u]) {
        if (colr[u] == colr[v])
            return false;
        else if (!colr[v] && !isbg(v, 3 - col))
            return false;
    }
    return true;
};