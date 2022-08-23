#include<bits/stdc++.h>
using namespace std;

class Dinic{
public:

    vector<vector<tuple<int,int,int>>> e;
    vector<int> deep,cur;

    Dinic(int n): e(n), deep(n), cur(n) {}

    void addedge(int u,int v,int w){
        e[u].emplace_back(make_tuple(v,w,(int)e[v].size()));
        e[v].emplace_back(make_tuple(u,0,(int)e[u].size()-1));
    }

    bool bfs(int s, int t){
        fill(cur.begin(),cur.end(),0); // 当前弧
        fill(deep.begin(),deep.end(),-1);
        deep[s] = 0;
        queue<int> q;
        q.push(s);
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(auto &[v,w,r]:e[u]){
                if(w>0 && deep[v]==-1){
                    deep[v] = deep[u] + 1;
                    q.push(v);
                }
            }
        }
        return deep[t]!=-1;
    }

    long long dfs(int u, int t, long long flow){
        if(u==t) return flow;
        long long left = flow;
        for(int &i=cur[u];i<(int)e[u].size();++i){
            auto &[v,w,r] = e[u][i];
            auto &[vv,ww,rr] = e[v][r];
            if(w>0 && deep[v]==deep[u]+1){
                long long c = dfs(v,t,min(left,1LL*w));
                w -= c;
                ww += c;
                left -= c;
                if(!left) break;
            }
        }
        return flow - left;
    }

    long long maxflow(int s,int t){
        long long res = 0;
        while(bfs(s,t)){
            res += dfs(s,t,LLONG_MAX);
        }
        return res;
    }
};

class Dinic_mcmf {
   public:
    // e[u] -> (v, flow, cost, rev)
    vector<vector<tuple<int, long long, long long, int>>> e;
    vector<int> cur, inq, vis;
    vector<long long> dis;
    static constexpr long long INF = LLONG_MAX;

    Dinic_mcmf(int n): e(n), cur(n), inq(n), vis(n), dis(n) {}

    void addedge(int u, int v, long long w, long long c) {
        e[u].emplace_back(make_tuple(v, w, c, (int)e[v].size()));
        e[v].emplace_back(make_tuple(u, 0, -c, (int)e[u].size() - 1));
    }

    bool spfa(int s,int t){
        fill(cur.begin(), cur.end(), 0);  // 当前弧
        fill(dis.begin(), dis.end(), INF);
        dis[s] = 0;
        queue<int> q;
        q.push(s);
        inq[s] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = 0;
            for (auto&& [v, w, c, r] : e[u]) {
                if (w > 0 && dis[v] > dis[u] + c) {
                    dis[v] = dis[u] + c;
                    if(!inq[v]) q.push(v);
                }
            }
        }
        return dis[t] != INF;
    }

    long long dfs(int u, int t, long long flow=INF) {
        if (u == t)
            return flow;
        long long left = flow;
        vis[u] = 1;
        for (int& i = cur[u]; i < (int)e[u].size(); ++i) {
            auto& [v, w, c, r] = e[u][i];
            auto& [vv, ww, cc, rr] = e[v][r];
            if (w > 0 && !vis[v] && dis[v] == dis[u] + c) {
                long long out = dfs(v, t, min(left, w));
                w -= out;
                ww += out;
                left -= out;
                if (!left)
                    break;
            }
        }
        vis[u] = 0;
        return flow - left;
    }

    pair<long long, long long> mcmf(int s,int t){
        long long mf = 0, mincost_mf = 0, flow = 0;
        while(spfa(s, t)){
            flow = dfs(s, t);
            mf += flow;
            mincost_mf += flow * dis[t];
        }
        return pair<long long, long long>(mf, mincost_mf);
    }
};