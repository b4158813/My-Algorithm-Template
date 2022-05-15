/*
https://codeforces.com/contest/220/problem/B
m个询问，每个询问求区间中值为x的数恰好出现x次的数的个数
莫队：维护区间中每个数的出现次数
*/

#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;i++)
const int maxn = 1e5+5;
int n,m,a[maxn],blk,st[maxn],en[maxn],bel[maxn],now;
int res;
int ans[maxn];
unordered_map<int,int> cnt;
struct Q{
	int l,r,id;
}q[maxn];
bool cmp(Q x1,Q x2){
	if(bel[x1.l]==bel[x2.l]) return bel[x1.r]<bel[x2.r];
	return bel[x1.l]<bel[x2.l];
}

inline void init_blk(int n){
	blk=sqrt(n);
	rep(i,1,blk){
		st[i]=n/blk*(i-1)+1;
		en[i]=n/blk*i;
	}
	en[blk]=n;
	rep(i,1,blk){
		rep(j,st[i],en[i]){
			bel[j]=i;
		}
	}
}
inline void del(int pos){
    if(cnt[a[pos]] == a[pos]) res--;
	--cnt[a[pos]];
    if(cnt[a[pos]] == a[pos]) res++;
	// if(!cnt[a[pos]]) --now;
}
inline void add(int pos){
    if(cnt[a[pos]] == a[pos]) res--;
	// if(!cnt[a[pos]]) ++now;
	++cnt[a[pos]];
    if(cnt[a[pos]] == a[pos]) res++;
}
int main(){
	scanf("%d %d",&n, &m);
	rep(i,1,n) scanf("%d",&a[i]);
	init_blk(n);
	rep(i,1,m){
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id=i;
	}
	sort(q+1,q+1+m,cmp);
	int l=1,r=0;
	rep(i,1,m){
		int tl=q[i].l,tr=q[i].r;
		while(l<tl) del(l++);
		while(l>tl) add(--l);
		while(r<tr) add(++r);
		while(r>tr) del(r--);
		ans[q[i].id]=res;
	}
	rep(i,1,m) printf("%d\n",ans[i]);
	return 0;
}