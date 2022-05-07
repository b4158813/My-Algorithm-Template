
class Dinic{
public:

    vector<vector<tuple<int,int,int>>> e;
    vector<int> deep,cur;

    Dinic(int n){
        e.resize(n);
        deep.resize(n);
        cur.resize(n);
    }

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

    ll dfs(int u, int t, ll flow){
        if(u==t) return flow;
        ll left = flow;
        for(int &i=cur[u];i<(int)e[u].size();++i){
            auto &[v,w,r] = e[u][i];
            auto &[vv,ww,rr] = e[v][r];
            if(w>0 && deep[v]==deep[u]+1){
                ll c = dfs(v,t,min(left,1ll*w));
                w -= c;
                ww += c;
                left -= c;
                if(!left) break;
            }
        }
        return flow - left;
    }

    ll maxflow(int s,int t){
        ll res = 0;
        while(bfs(s,t)){
            res += dfs(s,t,2e18);
        }
        return res;
    }
};


int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,m,s,t;
    cin>>n>>m>>s>>t;
    s--,t--;
    Dinic mxf(n);
    for(int u,v,w,i=0;i<m;++i){
        cin>>u>>v>>w;
        u--,v--;
        mxf.addedge(u,v,w);
    }
    cout<<mxf.maxflow(s,t)<<'\n';
    
    return 0;
}