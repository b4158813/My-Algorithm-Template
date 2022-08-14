/*
普通线段树 Segment Tree
*/
class SegTree {
    #define ls (i<<1)
    #define rs (i<<1|1)
    struct Node {
        long long val, tg;
        Node(): val(0), tg(0) {}
    };
    vector<Node> tr;
    inline void push_down(int i, int l, int r) {
        if (!tr[i].tg) return;
        int k = tr[i].tg;
        int mid = (l + r) >> 1;
        tr[ls].val = (tr[ls].val + k * (mid - l + 1));
        tr[rs].val = (tr[rs].val + k * (r - mid));
        tr[ls].tg = (tr[ls].tg + k);
        tr[rs].tg = (tr[rs].tg + k);
        tr[i].tg = 0;
    }
    inline void push_up(int i) {
        tr[i].val = (tr[ls].val + tr[rs].val);
    }

public:
    SegTree(const int &N): tr(N<<2) {}

    // given init value
    inline void build(int i,int l,int r,const vector<int> &a){
        if(l==r){
            tr[i].val = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(ls, l, mid, a);
        build(rs, mid+1, r, a);
        push_up(i);
    }

    inline void update(int i, int l, int r, int L, int R, int k) {
        if (l >= L && r <= R) {
            tr[i].tg = (tr[i].tg + k);
            tr[i].val = (tr[i].val + 1LL * k * (r - l + 1));
            return;
        }
        push_down(i, l, r);
        int mid = (l + r) >> 1;
        if (mid >= L) update(ls, l, mid, L, R, k);
        if (mid+1 <= R) update(rs, mid+1, r, L, R, k);
        push_up(i);
    }

    inline long long getsum(int i, int l, int r, int L, int R) {
        if (l >= L && r <= R) return tr[i].val;
        push_down(i, l, r);
        int mid = (l + r) >> 1;
        long long ret = 0;
        if (mid >= L) ret += getsum(ls, l, mid, L, R);
        if (mid+1 <= R) ret += getsum(rs, mid+1, r, L, R);
        return ret;
    }
};
////////////////////////////////////////////////////////

/*
动态开点线段树 Dynamic Segment Tree
*/
class SegTree {
    struct Node {
        long long val, tg, ls, rs;
        Node(): val(0), tg(0), ls(0), rs(0) {}
    };
    vector<Node> tr;
    int tcnt; // 0: [1, MAX]
    inline void push_down(int o, int l, int r) {
        if (!tr[o].ls) tr[o].ls = ++tcnt, tr.emplace_back(Node{});
        if (!tr[o].rs) tr[o].rs = ++tcnt, tr.emplace_back(Node{});
        if (!tr[o].tg) return;
        int k = tr[o].tg;
        int mid = (l + r) >> 1;
        tr[tr[o].ls].val += k * (mid - l + 1);
        tr[tr[o].rs].val += k * (r - mid);
        tr[tr[o].ls].tg += k;
        tr[tr[o].rs].tg += k;
        tr[o].tg = 0;
    }
    inline void push_up(int o) {
        tr[o].val = tr[tr[o].ls].val + tr[tr[o].rs].val;
    }

public:
    SegTree(): tr(1), tcnt(0) {}

    inline void update(int l, int r, int L, int R, int k, int o = 0) {
        if (l >= L && r <= R) {
            tr[o].tg += k;
            tr[o].val += 1LL * k * (r - l + 1);
            return;
        }
        push_down(o, l, r);
        int mid = (l + r) >> 1;
        if (mid >= L) update(l, mid, L, R, k, tr[o].ls);
        if (mid+1 <= R) update(mid+1, r, L, R, k, tr[o].rs);
        push_up(o);
    }

    inline long long getsum(int l, int r, int L, int R, int o = 0) {
        if (l >= L && r <= R) return tr[o].val;
        push_down(o, l, r);
        int mid = (l + r) >> 1;
        long long ret = 0;
        if (mid >= L) ret += getsum(l, mid, L, R, tr[o].ls);
        if (mid+1 <= R) ret += getsum(mid+1, r, L, R, tr[o].rs);
        return ret;
    }
};
/////////////////////////////////

/*
    p5490扫描线 https://www.luogu.com.cn/problem/P5490
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

class SegTree {
    #define ls (i<<1)
    #define rs (i<<1|1)
public:
    struct Node {
        int left, right, cnt, len;
        Node(): left(0), right(0), cnt(0), len(0) {}
    };
    vector<Node> tr;
    vector<int> X;
    inline void push_up(int i,int l,int r) {
		if(tr[i].cnt) tr[i].len = X[r+1] - X[l];
		else tr[i].len = tr[ls].len + tr[rs].len;
    }

    SegTree(const int &N): tr(N<<2), X(1) {}

    inline void edit(int i, int l, int r, int L, int R, int k) {
        if(X[r+1]<=L||X[l]>=R) return;
		if(X[r+1]<=R&&X[l]>=L){
			tr[i].cnt += k;
			push_up(i,l,r);
			return;
		}
		int mid = (l+r)>>1;
		if(X[l]<R) edit(ls,l,mid,L,R,k);
		if(X[r+1]>L) edit(rs,mid+1,r,L,R,k);
		push_up(i,l,r);
    }
};

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	int n;
	cin>>n;
	set<int> se;
	vector<tuple<int,int,int,int>> line;
	for(int i=0;i<n;++i){
		int xa,xb,ya,yb;
		cin>>xa>>ya>>xb>>yb;
		se.insert(xa);
		se.insert(xb);
		line.emplace_back(make_tuple(xa,xb,ya,1));
		line.emplace_back(make_tuple(xa,xb,yb,-1));
	}
	int tot = se.size();
	SegTree T = SegTree(tot<<1);
	for(auto &x:se) T.X.emplace_back(x);
	sort(line.begin(), line.end(), [&](tuple<int,int,int,int> t1, tuple<int,int,int,int> t2){
		return get<2>(t1) < get<2>(t2);
	});
	ll ans = 0;
	for(int i=0;i<n+n-1;++i){
		T.edit(1,1,tot-1,get<0>(line[i]),get<1>(line[i]),get<3>(line[i]));
		ans += 1LL * T.tr[1].len * (get<2>(line[i+1]) - get<2>(line[i]));
	}
	cout<<ans<<'\n';
	return 0;
}
/////////////////////////////////////////