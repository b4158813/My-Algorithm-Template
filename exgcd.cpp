ll exgcd(ll a,ll b,ll &x,ll &y){//返回gcd
	if(b==0){x=1;y=0;return a;}
	ll res=exgcd(b,a%b,x,y);
	ll tx=x;x=y;y=tx-a/b*y;
	return res;
}