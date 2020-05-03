int n,k,ran[maxn],fa[maxn];
// ran:集合大小
// fa：父亲
inline void init(int n){
	for(int i=1;i<=n;i++){
		fa[i]=i;
		ran[i]=1;
	}
}
inline int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
inline void unite(int x, int y){
	x=find(x);
	y=find(y);
	if(x!=y){
		fa[x]=y;
		ran[y]+=ran[x];
	}
}