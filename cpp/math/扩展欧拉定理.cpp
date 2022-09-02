ll a,m,b,phim;
bool flag=false;

/*
	https://www.luogu.com.cn/problem/P5091
	扩展欧拉定理
		通常用于求解快速幂时指数特别巨大的情况（此时，若指数为b，模数为m，则指数需要模phi(m))
	a^b mod m = a^(b mod phi[m] + phi[m]) mod m {if b>=phi[m]}
*/

template<class T>
inline void _read(T &x) {
	x=0;int f=0;char ch=getchar();
	while(ch<48||ch>57){f|=(ch=='-');ch=getchar();}
	while(ch>=48&&ch<=57){
		x=(x<<1)+(x<<3)+(ch^48);
		if(x>=phim) flag=true,x%=phim;
		ch=getchar();
	}
	x=f?-x:x;
	return;
}

// get phi[n]
inline ll getphi(ll n){
	ll res=n;
	for(ll i=2;i*i<=n;i++){
		if(n%i==0) res=res/i*(i-1);
		while(n%i==0) n/=i;
	}
	if(n>1) res=res/n*(n-1);
	return res;
}

int main(){
	read(a),read(m);
	phim=getphi(m);
	_read(b);
	// get a^b mod m
	ll ans=qpow(a,b+(flag?phim:0),m);
	printf("%lld\n",ans);
	return 0;
}