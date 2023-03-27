/*
        Tarjan SCC
        有向图 强连通分量
		
		usage:
		```
		for(int i=0;i<n;++i) {
			if(!dfn[i]) {
				tarjan(i);
			}
		}
		```
*/
vector<int> low(n), dfn(n), sta;
vector<bool> vis(n);
vector<int> color(n);
vector<vector<int>> groups;
int deep{0}, scc{0};
function<void(int)> tarjan = [&](int u) {
    vis[u] = 1;
    sta.emplace_back(u);
    low[u] = dfn[u] = ++deep;
    for (auto &&v: e[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        vis[u] = 0;
        color[u] = scc;
        vector<int> gr{u};
        while (sta.back() != u) {
            gr.emplace_back(sta.back());
            color[sta.back()] = scc;
            vis[sta.back()] = 0;
            sta.pop_back();
        }
        sta.pop_back();
        scc++;
        groups.emplace_back(gr);
    }
};

/*
    Tarjan V-DCC
    无向图 点双连通分量 + 割点
		
	usage:
	```
	for(int i=0;i<n;++i) {
		if(!dfn[i]) {
			RT = i;
			tarjan(i, i);
		}
	}
	```
*/
vector<int> low(n), dfn(n), sta;
vector<bool> cut(n);
vector<vector<int>> dcc;
int deep{0}, RT{0};
function<void(int, int)> tarjan = [&](int u, int fa) {
    dfn[u] = low[u] = ++deep;
    sta.emplace_back(u);
    if (e[u].empty() && u == fa) {
        dcc.emplace_back(vector<int>{u});
        return;
    }
    int child = 0;
    for (auto v : e[u]) {
        if (v == fa)
            continue;
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                child++;
                if (u != RT || child > 1) {
                    cut[u] = 1;
				}
                dcc.emplace_back(vector<int>());
                int t;
                do {
                    t = sta.back();
                    sta.pop_back();
                    dcc.back().emplace_back(t);
                } while (t != v);
                dcc.back().emplace_back(u);
            }
        }else {
            low[u] = min(low[u], dfn[v]);
		}
    }
    return;
};