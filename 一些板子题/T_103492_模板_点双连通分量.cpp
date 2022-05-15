#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;


int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,m;
    cin>>n>>m;
    vector<vector<int>> e(n);
    for(int u,v,i=0;i<m;++i){
        cin>>u>>v;
        u--,v--;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }

    vector<int> low(n),dfn(n),sta;
    vector<bool> cut(n);
    vector<vector<int>> dcc;
    int deep,RT=0;
    function<void(int,int)> tarjan = [&](int u,int fa){
        dfn[u] = low[u] = ++deep;
        sta.emplace_back(u);
        if(e[u].empty() && u==fa){
            dcc.emplace_back(vector<int>{u});
            return;
        }
        int child = 0;
        for(auto v:e[u]){
            if(v==fa) continue;
            if (!dfn[v]){
                tarjan(v,u);
                low[u] = min(low[u], low[v]);
                if(low[v] >= dfn[u]){
                    child++;
                    if(u!=RT || child>1) cut[u] = 1;
                    dcc.emplace_back(vector<int>());
                    int t;
                    do{
                        t = sta.back();
                        sta.pop_back();
                        dcc.back().emplace_back(t);
                    }while(t != v);
                    dcc.back().emplace_back(u);
                }
            }else low[u] = min(low[u], dfn[v]);
        }
        return;
    };
    return 0;
}