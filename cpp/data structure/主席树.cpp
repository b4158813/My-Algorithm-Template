int n,m,a[maxn],b[maxn],ans;
int T[maxn*40],ls[maxn*40],rs[maxn*40],ci[maxn*40],tcnt;

// build
inline void build(int &rt,int l,int r){
	rt=++tcnt,ci[rt]=0;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(ls[rt],l,mid);
	build(rs[rt],mid+1,r);
}

// insert
int update(int o,int l,int r,int val){
	int oo=++tcnt;
	ls[oo]=ls[o],rs[oo]=rs[o],ci[oo]=ci[o]+1;
	if(l==r) return oo;
	int mid=(l+r)>>1;
	if(mid>=val) ls[oo]=update(ls[oo],l,mid,val);
	else rs[oo]=update(rs[oo],mid+1,r,val);
	return oo;
}

// kth
int query(int L,int R,int l,int r,int k){
	if(l==r) return l;
	int mid=(l+r)>>1;
	int x=ci[ls[L]]-ci[ls[R]];
	if(x>=k) return query(ls[L],ls[R],l,mid,k);
	else return query(rs[L],rs[R],mid+1,r,k-x);
}

int main(){
	read(n),read(m);
	rep(i,1,n) read(a[i]),b[i]=a[i];
	sort(b+1,b+1+n);
	int len=unique(b+1,b+1+n)-b-1;
	build(T[0],1,len);
	rep(i,1,n){
		int x=lower_bound(b+1,b+1+len,a[i])-b;
		T[i]=update(T[i-1],1,len,x);
	}
	for(int i=0,x,y,k;i<m;i++){
		read(x),read(y),read(k);
		printf("%d\n",b[query(T[x-1],T[y],1,len,k)]);
	}
	return 0;
}