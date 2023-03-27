vector<int> sz(n), center(n);
int minh = 1e9;
auto dfs = [&](auto &&self, int u,int fa) -> void {
    sz[u] = 1;
    center[u] = 0;
    for(auto v:e[u]){
        if(v==fa) continue;
        self(self, v,u);
        sz[u] += sz[v];
        center[u] = max(center[u], sz[v]);
    }
    center[u] = max(center[u], n - sz[u]);
    if(center[u]<minh){
        minh = center[u];
    }
};