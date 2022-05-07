// rmq
int n,m,a[maxn],ST[maxn][23];
inline void init_st(){ //st init
	for(int i=1;i<=n;i++) ST[i][0]=a[i];
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i+(1<<(j-1))-1<=n;i++){
			ST[i][j]=max(ST[i][j-1],ST[i+(1<<(j-1))][j-1]);
		}
	}
}
inline int query(int l,int r){ //查询l,r最值
	int len=log2(r-l+1);
	return max(ST[l][len],ST[r-(1<<len)+1][len]);
}