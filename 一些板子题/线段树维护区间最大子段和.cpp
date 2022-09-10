/*
    https://www.luogu.com.cn/problem/P4513
    线段树维护最大子段和模板
    给定一个序列（有正有负），两种操作：
        1. 单点修改
        2. 求[l, r]最大子段和
*/

#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
/*
普通线段树 Segment Tree
*/
class SegTree {
    #define ls (i<<1)
    #define rs (i<<1|1)
    struct Node {
        long long res_l, res_r, res, sum;
        Node(): res_l(0), res_r(0), res(0), sum(0) {}
    };
    vector<Node> tr;
    inline void push_up(int i) {
        tr[i].res = max({tr[ls].res, tr[rs].res, tr[ls].res_r + tr[rs].res_l});
        tr[i].sum = tr[ls].sum + tr[rs].sum;
        tr[i].res_l = max(tr[ls].res_l, tr[ls].sum + tr[rs].res_l);
        tr[i].res_r = max(tr[rs].res_r, tr[rs].sum + tr[ls].res_r);
    }

public:
    SegTree(const int &N): tr(N<<2) {}

    // given init value
    inline void build(int i,int l,int r,const vector<int> &a){
        if(l==r){
            tr[i].res_l = tr[i].res_r = tr[i].res = tr[i].sum = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(ls, l, mid, a);
        build(rs, mid+1, r, a);
        push_up(i);
    }

    inline void update(int i, int l, int r, int pos, ll k) {
        if(l == r){
            tr[i].sum = tr[i].res_l = tr[i].res_r = tr[i].res = k;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) update(ls, l, mid, pos, k);
        else update(rs, mid+1, r, pos, k);
        push_up(i);
    }

    inline Node getmax(int i, int l, int r, int L, int R) {
        if (l >= L && r <= R) return tr[i];
        int mid = (l + r) >> 1;
        if(mid >= R) return getmax(ls, l, mid, L, R);
        else if(mid < L) return getmax(rs, mid+1, r, L, R);
        else{
            Node left = getmax(ls, l, mid, L, R);
            Node right = getmax(rs, mid+1, r, L, R);
            Node t;
            t.res_l = max(left.res_l, left.sum + right.res_l);
            t.res_r = max(right.res_r, right.sum + left.res_r);
            t.res = max({left.res, right.res, left.res_r + right.res_l});
            return t;
        }
    }
};
////////////////////////////////////////////////////////
void solve(){
    
    int n, m;
    cin >> n >> m;
    vector<int> a(n+1);
    for(int i=1;i<=n;++i) cin >> a[i];
    SegTree T(n+10);
    T.build(1, 1, n, a);
    int op, x, y;
    while(m--){
        cin >> op >> x >> y;
        if(op&1){
            if(x > y) swap(x, y);
            cout << T.getmax(1, 1, n, x, y).res << '\n';
        }else{
            T.update(1, 1, n, x, y);
        }
    }
}

int main(){
    
    cin.tie(nullptr)->sync_with_stdio(false);
    
    int _ = 1;
    // cin>>_;
    while(_--){
        
        solve();
        
    }
    
    return 0;
}