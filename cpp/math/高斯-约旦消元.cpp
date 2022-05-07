// Gauss-Jordan Elimination
// n*n Matrix
inline void Gauss_Jordan(){
	for(int i=1;i<=n;i++){
		int tp=i;
		for(int j=i+1;j<=n;j++){
			if(fabs(a[j][i])>fabs(a[tp][i]))
				tp=j;
		}
		if(fabs(a[tp][i])<eps){
			printf("No Solution\n");
			return;
		}
		if(tp!=i) swap(a[tp],a[i]);
		for(int j=1;j<=n;j++){
			if(j!=i){
				double div=a[j][i]/a[i][i];
				for(int k=i;k<=n+1;k++){
					a[j][k]-=a[i][k]*div;
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
		printf("%.2lf\n",a[i][n+1]/a[i][i]);
}