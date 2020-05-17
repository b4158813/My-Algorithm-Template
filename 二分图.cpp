
// 匈牙利算法
int idx,have[maxn],used[maxn];
inline bool Hungary(int u){
	for(int i=head[u];~i;i=e[i].next){
		int v=e[i].v;
		if(used[v]!=idx){
			used[v]=idx;
			if(!have[v]||Hungary(have[v])){
				have[v]=u;
				return true;
			}
		}
	}
	return false;
}

// 二分图判定
int colr[maxn];
inline bool isbg(int u,int col){
	colr[u]=col;;
	for(int i=head[u];~i;i=e[i].next){
		int v=e[i].v;
		if(colr[u]==colr[v]) return false;
		else if(!colr[v]&&!isbg(v,3-col)) return false;
	}
	return true;
}