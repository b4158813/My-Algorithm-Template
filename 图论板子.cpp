struct Edge{
	int u,v,w,next;
}e[maxn<<1];
int cnt,head[maxn];
inline void init_graph(){
	cnt=0;
	memset(head,-1,sizeof(head));
}
inline void addedge(int u,int v,int w=0){
	e[cnt]=Edge{u,v,w,head[u]};
	head[u]=cnt++;
}
