/* Matrix quick power */
struct M
{
	ll mat[15][15];
};

M operator *(M x1,M x2){
	M res;
	memset(res.mat,0,sizeof(res.mat));
	// n: transition matrix dimension
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++){
				res.mat[i][j]+=(x1.mat[i][k]%mod*x2.mat[k][j]%mod)%mod;
				res.mat[i][j]%=mod;
			}
		}
	}
	return res;
}

// res*move^y
inline M mqpow(M res,M move,ll y){
	while(y){
		if(y&1) res=res*move;
		move=move*move;
		y>>=1;
	}
	return res;
}
