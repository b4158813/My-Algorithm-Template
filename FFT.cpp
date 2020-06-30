int n,m;
int bi,rev[maxn];
complex<double> f[maxn],g[maxn],ans[maxn];

// 递归FFT，type = 1 : DFT ; type = -1 : IDFT
void FFT(complex<double> *a,int n,int type){
	if(n<=1) return;
	int mid=n>>1;
	complex<double> a1[mid],a2[mid];
	for(int i=0;i<mid;i++)
		a1[i]=a[i<<1],a2[i]=a[i<<1|1];
	FFT(a1,mid,type),FFT(a2,mid,type);
	complex<double> w1(cos(PI/mid),type*sin(PI/mid)),w(1,0),x;
	for(int i=0;i<mid;i++){
		x=w*a2[i];
		a[i]=a1[i]+x;
		a[i+mid]=a1[i]-x;
		w*=w1;
	}
}

// 迭代FFT，type = 1 : DFT ; type = -1 : IDFT
void FFT(complex<double> *a,int n,int type){
	for(int i=0;i<n;i++)
		if(i<rev[i]) swap(a[i],a[rev[i]]);
	for(int len=1;len<=(n>>1);len<<=1){
		complex<double> w1(cos(PI/len),type*sin(PI/len));
		for(int i=0;i<=n-(len<<1);i+=len<<1){
			complex<double> w(1,0),x,y;
			for(int j=0;j<len;j++){
				x=a[i+j],y=w*a[i+j+len];
				a[i+j]=x+y,a[i+j+len]=x-y;
				w*=w1;
			}
		}
	}
}

int main(){
	read(n),read(m);
	for(int i=0,x;i<=n;i++) read(x),f[i]=x;
	for(int i=0,x;i<=m;i++) read(x),g[i]=x;
	int tot=1;
	while(tot<=n+m) tot<<=1,bi++;
	for(int i=1;i<tot;i++)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(bi-1));
	FFT(f,tot,1),FFT(g,tot,1);
	rep(i,0,tot) ans[i]=f[i]*g[i];
	FFT(ans,tot,-1);
	rep(i,0,n+m) printf("%d ",(int)(ans[i].real()/tot+0.5));
	return 0;
}