int low[maxn],dfn[maxn],sta[maxn],color[maxn],vis[maxn],top,scc,deep;
void tarjan(int u){
	vis[sta[++top]=u]=1;
	low[u]=dfn[u]=++deep;
	for(int i=head[u];~i;i=e[i].next){
		int v=e[i].v;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(vis[v]) low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		vis[u]=0;
		color[u]=++scc;
		while(sta[top]!=u){
			color[sta[top]]=scc;
			vis[sta[top--]]=0;
		}
		top--;
	}
}