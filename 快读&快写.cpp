// fread
inline char _nc(){
    static char buf[100000],*L=buf,*R=buf;
    return L==R&&(R=(L=buf)+fread(buf,1,100000,stdin),L==R)?EOF:*L++;
}
template<class T> void read(T &x) {
	x=0;int f=0;char ch=_nc();
	while(ch<'0'||ch>'9'){f|=(ch=='-');ch=_nc();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=_nc();}
	x=f?-x:x;
	return;
}

// fast read
template<class T> void read(T &x) {
	x=0;int f=0;char ch=getchar();
	while(ch<'0'||ch>'9'){f|=(ch=='-');ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	x=f?-x:x;
	return;
}

//fast write
inline void write(ll x){
	if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}