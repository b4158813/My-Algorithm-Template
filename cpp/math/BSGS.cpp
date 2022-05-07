// a^x=b(mod p) <=> a^(im)=b*a^k(mod p)
inline ll BSGS(ll a,ll b,ll p){
	unordered_map<ll,ll> ma;
	ll m=ceil(sqrt(p));
	for(ll i=0,cur=b%p;i<=m;i++,cur=cur*a%p)
		ma[cur]=i;
	ll am=qpow(a,m,p);
	for(ll i=1,now=am;i<=m;i++,now=now*am%p){
		if(ma.count(now)) return (i*m-ma[now]+p)%p;// x
	}
	return -1;// no solution
}