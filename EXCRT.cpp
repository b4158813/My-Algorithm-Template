// O1快速乘
inline ll multi(ll x,ll y,ll Mod){
	ll tmp=(x*y-(ll)((long double)x/Mod*y+1.0e-8)*Mod);
	return tmp<0 ? tmp+Mod : tmp;
}

inline ll exgcd(ll a,ll b,ll &x,ll &y){
	if(!b){x=1,y=0;return a;}
	ll res=exgcd(b,a%b,x,y);
	ll tx=x;x=y;y=tx-a/b*y;
	return res;
}

// x = a[i] (mod b[i]) b[i]不互质
inline ll excrt(){
	ll ans=a[1],M=b[1];// 特判第一个方程
	for(int i=2;i<=n;i++){
		ll aa=M,bb=b[i];
		ll cc=(a[i]-ans%bb+bb)%bb;// aa*x=cc(mod bb)
		ll x,y;
		ll g=exgcd(aa,bb,x,y),bg=bb/g;
		if(cc%g) return -1;// 无解
		x=multi(cc/g,x,bg);// 防爆long long
		ans+=x*M;
		M*=bg;
		ans=(ans%M+M)%M;
	}
	return (ans%M+M)%M;
}// https://www.luogu.com.cn/problem/P4777