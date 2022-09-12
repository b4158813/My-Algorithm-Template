// f1[u], f2[u]维护包含u的子树的最长和次长路径
vector<int> f1(n), f2(n);
auto dfs = [&](auto &&self, int u,int fa)->void{
    f1[u] = f2[u] = 0;
    for(auto &&v: e[u]){
        if(v == fa) continue;
        self(self, v, u);
        int t = f1[v] + 1;
        if(t > f1[u]){
            f2[u] = f1[u];
            f1[u] = t;
        }else if(t > f2[u]){
            f2[u] = t;
        }
    }
};