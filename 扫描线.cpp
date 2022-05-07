#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define ls (i<<1)
#define rs (i<<1|1)
#define lld I64d
typedef long long ll;
const long long mod=1e9+7;
const int inf=0x7fffffff;
const int maxn=1000005;

int n,cnt=0;
ll disc[maxn<<1];

struct node{
	ll l,r,h;
	int k;
	bool operator<(const node &rhs)const{
		return h<rhs.h;
	}
}line[maxn<<1];

struct segtree{
	int l,r,sum;
	ll len;
}tr[maxn<<2];

void build(int i,int l,int r){
	tr[i].l = l, tr[i].r = r;
	tr[i].sum = 0;
	tr[i].len = 0;
	if(l==r) return;
	int mid = (l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	return;
}

void push_up(int i){
	if(tr[i].sum) tr[i].len = disc[tr[i].r+1] - disc[tr[i].l];
	else tr[i].len = tr[ls].len + tr[rs].len;
}

void edit(int i,int L,int R,int k){
	if(disc[tr[i].r+1]<=L||disc[tr[i].l]>=R) return;
	if(disc[tr[i].r+1]<=R&&disc[tr[i].l]>=L){
		tr[i].sum+=k;
		push_up(i);
		return;
	}
	if(disc[tr[i].l]<R) edit(ls,L,R,k);
	if(disc[tr[i].r+1]>L) edit(rs,L,R,k);
	push_up(i);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		ll x1,x2,y1,y2;
		scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
		disc[i*2-1] = x1;
		disc[i*2] = x2;
		line[i*2-1] = {x1,x2,y1,1};
		line[i*2] = {x1,x2,y2,-1};
	}
	n<<=1;
	sort(line+1,line+1+n);
	sort(disc+1,disc+1+n);
	int tot = unique(disc+1,disc+1+n)-disc-1;
	build(1,1,tot-1);
	ll ans = 0;
	for(int i=1;i<n;++i){
		edit(1,line[i].l,line[i].r,line[i].k);
		ans += tr[1].len*(line[i+1].h - line[i].h);
	}
	printf("%lld\n",ans);
	return 0;
}
// p5490扫描线 https://www.luogu.com.cn/problem/P5490