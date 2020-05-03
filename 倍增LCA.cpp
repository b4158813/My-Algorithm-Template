int bfa[maxn][21],bdep[maxn];
// int bsum[maxn][21],bmax[maxn][21];
inline void init_beizeng(){
	for(int i=1;i<21;++i){
		for(int j=1;j<=n;j++){
			bfa[j][i]=bfa[bfa[j][i-1]][i-1];
			// bsum[j][i]=bsum[j][i-1]+bsum[bfa[j][i-1]][i-1];
			// bmax[j][i]=max(bmax[j][i-1],bmax[bfa[j][i-1]][i-1]);
		}
	}
}

// init dfs
inline void bdfs(int u,int fath,int depth){
	bdep[u]=depth;
	bfa[u][0]=fath;
	for(int i=head[u];~i;i=e[i].next){
		int v=e[i].v;
		if(v!=fath){
			// bsum[v][0]=e[i].w;
			// bmax[v][0]=e[i].w;
			bdfs(v,u,depth+1);
		}
	}
}

// LCA
inline int LCA(int x,int y){
	if(bdep[x]<bdep[y]) swap(x,y);
	// int Sum=0,Max=-1;
	while(bdep[x]>bdep[y]){
		// Sum+=bsum[x][int(log2(bdep[x]-bdep[y]))];
		// Max=max(Max,bmax[x][int(log2(bdep[x]-bdep[y]))]);
		x=bfa[x][int(log2(bdep[x]-bdep[y]))];
	}
	if(x==y) return x;
	for(int i=log2(bdep[x]);i>=0;i--){
		if(bfa[x][i]!=bfa[y][i]){
			x=bfa[x][i],y=bfa[y][i];
		}
	}
	return bfa[x][0];
}