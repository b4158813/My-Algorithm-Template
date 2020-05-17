
/* Normal Segment Tree */

struct SegmentTree
{	
	#define ls i<<1
	#define rs i<<1|1
	struct Tree{
		int l,r;
		ll sum,ptg;
	}tr[maxn<<2];

	inline void push_up(int i){
		tr[i].sum=(tr[ls].sum+tr[rs].sum)%mod;
	}

	inline void push_down(int i){
		if(tr[i].ptg==0) return;
		ll k=tr[i].ptg%mod;
		tr[ls].sum=(tr[ls].sum+k*(tr[ls].r-tr[ls].l+1)%mod)%mod;
		tr[rs].sum=(tr[rs].sum+k*(tr[rs].r-tr[rs].l+1)%mod)%mod;
		tr[ls].ptg=(tr[ls].ptg+k)%mod;
		tr[rs].ptg=(tr[rs].ptg+k)%mod;
		tr[i].ptg=0;
	}

	inline void build(int i,int l,int r){
		tr[i].l=l,tr[i].r=r;
		tr[i].ptg=0;
		if(tr[i].l==tr[i].r){
			tr[i].sum=a[l]%mod;
			return;
		}
		int mid=(l+r)>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
		push_up(i);
	}

	inline void changepoint(int i,int pos,ll k){
		if(tr[i].l==tr[i].r){
			tr[i].sum=k%mod;
			return;
		}
		push_down(i);
		if(tr[ls].r>=pos) changepoint(ls,pos,k);
		else changepoint(rs,pos,k);
		push_up(i);
	}

	inline void addinterval(int i,int l,int r,ll k){
		if(tr[i].l>=l&&tr[i].r<=r){
			tr[i].sum=(tr[i].sum+k*(tr[i].r-tr[i].l+1)%mod)%mod;
			tr[i].ptg=(tr[i].ptg+k)%mod;
			return;
		}
		push_down(i);
		if(tr[ls].r>=l) addinterval(ls,l,r,k);
		if(tr[rs].l<=r) addinterval(rs,l,r,k);
		push_up(i);
	}

	inline ll getsum(int i,int l,int r){
		if(tr[i].l>=l&&tr[i].r<=r)
			return tr[i].sum;
		push_down(i);
		ll res=0;
		if(tr[ls].r>=l) res=(res+getsum(ls,l,r))%mod;
		if(tr[rs].l<=r) res=(res+getsum(rs,l,r))%mod;
		return res;
	}
}T;
