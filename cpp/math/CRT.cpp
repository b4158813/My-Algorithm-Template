inline ll exgcd(ll a,ll b,ll &x,ll &y){
	if(!b){x=1,y=0;return a;}
	ll res=exgcd(b,a%b,x,y);
	ll tx=x;x=y;y=tx-a/b*y;
	return res;
}


// x = a[i] (mod b[i]) b[i]互质
inline void crt(){
	ll tot=1,ans=0;
	for(int i=1;i<=n;i++) tot*=b[i];
	rep(i,1,n){
		ll tp=tot/b[i];
		ll x,y;
		exgcd(tp,b[i],x,y);
		ans=(ans+a[i]*tp*x)%tot;
		// Ans = sum(a[i] * M[i] * M^-1[i])
	}
	printf("%lld\n",(ans+tot)%tot);
}// https://www.luogu.com.cn/problem/P4777