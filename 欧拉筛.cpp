int f[maxn],prime[maxn],phi[maxn],cnt;
// get phi[1~n]
inline void init(int N){
	phi[1]=1;//欧拉函数：小于等于n的与n互质的正整数个数
	f[0]=f[1]=1;//0：素数，1：合数
	for(int i=2;i<=N;i++){
		if(f[i]==0){
			prime[++cnt]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=cnt&&i*prime[j]<=N;j++){
			f[i*prime[j]]=1;
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}else phi[i*prime[j]]=phi[i]*phi[prime[j]];//积性函数
		}
	}
}

// get phi[n]
inline int getphi(int n){
	int res=n;
	for(int i=2;i*i<=n;i++){
		if(n%i==0) res=res/i*(i-1);
		while(n%i==0) n/=i;  
	}
	if(n>1) res=res/n*(n-1);
	return res;
}