// a^x = b (mod p) <=> a^(x-k) * a/prod(g) = b/prod(g) (mod p/prod(g))
inline ll EXBSGS(ll a,ll b,ll p){
	if(b==1) return 0;// a^x = 1 (mod p)
	ll g,k=0,ag=1;
	while((g=gcd(a,p))>1){
		if(b%g) return -1;// no solution
		k++,b/=g,p/=g,ag=ag*(a/g)%p;
		if(ag==b) return k;// a^(x-k)=1
	}
	ll inv,y;
	exgcd(ag,p,inv,y);// get inv of ag
	inv=(inv+p)%p;
	ll res=BSGS(a,b*inv%p,p);// BSGS
	return res==-1?res:res+k;// solution + k
}