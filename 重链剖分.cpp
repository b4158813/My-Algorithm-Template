/* Heavy Path Decomposition */
// dfs序、深度、子树大小、父节点、重儿子、链顶
int dfsx,csid[maxn],csdep[maxn],cssize[maxn],csfa[maxn],csson[maxn],cstop[maxn];
// value need to maintain
int csw[maxn];

// first dfs
inline void csdfs1(int u,int fath,int depth){
	csfa[u]=fath;
	csdep[u]=depth;
	cssize[u]=1;
	/* long path dec */
	// cssize[u]=csdep[u];
	for(int i=head[u];~i;i=e[i].next){
		int v=e[i].v;
		if(v!=fath){
			/* edge to point */
			// w[v]=e[i].w;
			// wdep[v]+=w[v];
			csdfs1(v,u,depth+1);
			cssize[u]+=cssize[v];
			/* long path dec */
			// cssize[u]=max(cssize[u],cssize[v]);
			if(cssize[v]>cssize[csson[u]])
				csson[u]=v;
		}
	}
}

//second dfs
inline void csdfs2(int u,int topf){
	csid[u]=++dfsx;
	/* value need to maintain */
	// csw[dfsx]=u;
	cstop[u]=topf;
	if(!csson[u]) return;
	csdfs2(csson[u],topf);
	for(int i=head[u];~i;i=e[i].next){
		int v=e[i].v;
		if(v!=csfa[u]&&v!=csson[u])
			csdfs2(v,v);
	}
}

/*--------------------------------------*/

// get LCA
inline int LCA(int x,int y){
	while(cstop[x]!=cstop[y]){
		if(csdep[cstop[x]]<csdep[cstop[y]])
			swap(x,y);
		x=csfa[cstop[x]];
	}
	return csdep[x]<csdep[y]?x:y;
}

// [x,y] + k
inline void addroute(int x,int y,int k){
	while(cstop[x]!=cstop[y]){
		if(csdep[cstop[x]]<csdep[cstop[y]])
			swap(x,y);
		// Segment Tree: add(i,l,r,k)
		add(1,csid[cstop[x]],csid[x],k);
		x=csfa[cstop[x]];
	}
	if(csdep[x]>csdep[y]) swap(x,y);
	add(1,csid[x],csid[y],k);
}

// get [x,y] sum
inline ll getroutesum(int x,int y){
	ll res=0;
	while(cstop[x]!=cstop[y]){
		if(csdep[cstop[x]]<csdep[cstop[y]])
			swap(x,y);
		// Segment Tree: getsum(i,l,r)
		res+=getsum(1,csid[cstop[x]],csid[x],k);
		x=csfa[cstop[x]];
	}
	if(csdep[x]>csdep[y]) swap(x,y);
	res+=getsum(1,csid[x],csid[y],k);
	return res;
}

