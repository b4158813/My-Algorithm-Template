/*
	倍增LCA
*/
vector<array<int,22>> bfa(n+1);
// vector<array<int,22>> bsum(n+1), bmax(n+1);
vector<int> deep(n+1);
auto init_beizeng = [&](int root){
	// init dfs
	auto dfs = [&](auto &&self, int u,int fa,int dep)->void{
		deep[u] = dep;
		bfa[u][0] = fa;
		for(auto &&v:e[u]){
			if(v == fa) continue;
			// bsum[v][0]=e[i].w;
			// bmax[v][0]=e[i].w;
			self(self, v, u, dep+1);
		}
	};
	dfs(dfs, root, 0, 0);

	// dp
	for(int i=1;(1<<i)<=n;++i){
		for(int j=1;j<=n;++j){
			bfa[j][i]=bfa[bfa[j][i-1]][i-1];
			// bsum[j][i]=bsum[j][i-1]+bsum[bfa[j][i-1]][i-1];
			// bmax[j][i]=max(bmax[j][i-1],bmax[bfa[j][i-1]][i-1]);
		}
	}
};
init_beizeng(s);
// LCA
auto LCA = [&](int x,int y){
	if(deep[x]<deep[y]) swap(x,y);
	// int Sum = 0, Max = -1;
	while(deep[x]>deep[y]){
		// Sum += bsum[x][int(log2(deep[x]-deep[y]))];
		// Max = max(Max, bmax[x][int(log2(deep[x]-deep[y]))]);
		x=bfa[x][int(log2(deep[x]-deep[y]))];
	}
	if(x==y) return x;
	for(int i=log2(deep[x]); i>=0; i--){
		if(bfa[x][i]!=bfa[y][i]){
			x=bfa[x][i],y=bfa[y][i];
		}
	}
	return bfa[x][0];
};