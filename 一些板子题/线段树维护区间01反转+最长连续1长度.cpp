/*
    https://ac.nowcoder.com/acm/contest/925/K
    初始为01序列，两种操作：
        1. 将[l, r]区间所有01值反转(0变1，1变0)
        2. 求[l, r]区间最长的连续1的长度
    
    此题类似 **线段树维护区间最大子段和**
    
    方法是 线段树合并：

        线段树节点维护值：
            - 左端点开始的最长连续1个数(len1_l)
            - 右端点开始的最长连续1个数(len1_r)
            - 区间最长连续1个数(len1)
            - 左端点开始的最长连续0个数(len0_l)
            - 右端点开始的最长连续0个数(len0_r)
            - 区间最长连续0个数(len0)
            - 反转标记（记录区间反转了几次）(tag)

        push_up操作：
            len1 = max(ls的len1, rs的len1, ls的len1_r + rs的len1_l);
            len0 = max(ls的len0, rs的len0, ls的len0_r + rs的len0_l);
            len1_l = ls的len1_l + (ls的len1_l == ls区间长度 ? 0 : rs的len1_l)
            len1_r = ...
            len0_l = ...
            len0_r = ...

        push_down操作：
            将root的tag^=1，并反转ls和rs
        
        反转操作：
            交换len0,len0_l,len0_r 和 len1,len1_l,len1_r
            并将tag^=1
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
        long long len_l, len_r, len, len0_l, len0_r, len0, tg;
        Node(): len_l(0), len_r(0), len(0), len0_l(0), len0_r(0), len0(0), tg(0) {}
    };
    vector<Node> tr;
    inline void change(int i){
        swap(tr[i].len0_l, tr[i].len_l);
        swap(tr[i].len0_r, tr[i].len_r);
        swap(tr[i].len, tr[i].len0);
        tr[i].tg ^= 1;
    }
    inline void push_down(int i){
        if(!tr[i].tg) return;
        change(ls);
        change(rs);
        tr[i].tg = 0;
    }
    inline void push_up(int i, int l, int r) {
        int mid = (l + r) >> 1;
        tr[i].len = max({tr[ls].len, tr[rs].len, tr[ls].len_r + tr[rs].len_l});
        tr[i].len0 = max({tr[ls].len0, tr[rs].len0, tr[ls].len0_r + tr[rs].len0_l});
        if(tr[ls].len_l == mid - l + 1) tr[i].len_l = tr[ls].len_l + tr[rs].len_l;
        else tr[i].len_l = tr[ls].len_l;
        if(tr[rs].len_r == r - mid) tr[i].len_r = tr[rs].len_r + tr[ls].len_r;
        else tr[i].len_r = tr[rs].len_r;
        if(tr[ls].len0_l == mid - l + 1) tr[i].len0_l = tr[ls].len0_l + tr[rs].len0_l;
        else tr[i].len0_l = tr[ls].len0_l;
        if(tr[rs].len0_r == r - mid) tr[i].len0_r = tr[rs].len0_r + tr[ls].len0_r;
        else tr[i].len0_r = tr[rs].len0_r;
    }

public:
    SegTree(const int &N): tr(N<<2) {}

    // given init value
    inline void build(int i,int l,int r,const vector<int> &a){
        if(l==r){
            tr[i].len_l = tr[i].len_r = tr[i].len = a[l];
            tr[i].len0_l = tr[i].len0_r = tr[i].len0 = (a[l]==0);
            return;
        }
        int mid = (l + r) >> 1;
        build(ls, l, mid, a);
        build(rs, mid+1, r, a);
        push_up(i, l, r);
    }


    inline void update(int i, int l, int r, int L, int R) {
        if (l >= L && r <= R) {
            change(i);
            return;
        }
        push_down(i);
        int mid = (l + r) >> 1;
        if (mid >= L) update(ls, l, mid, L, R);
        if (mid+1 <= R) update(rs, mid+1, r, L, R);
        push_up(i, l, r);
    }

    inline Node getmax(int i, int l, int r, int L, int R) {
        if (l >= L && r <= R) return tr[i];
        push_down(i);
        int mid = (l + r) >> 1;
        if(mid >= R) return getmax(ls, l, mid, L, R);
        else if(mid < L) return getmax(rs, mid+1, r, L, R);
        else{
            Node ret;
            Node left = getmax(ls, l, mid, L, R);
            Node right = getmax(rs, mid+1, r, L, R);
            ret.len = max({left.len, right.len, left.len_r + right.len_l});
            ret.len0 = max({left.len0, right.len0, left.len0_r + right.len0_l});
            if(tr[ls].len_l == mid - l + 1) ret.len_l = left.len_l + right.len_l;
            else ret.len_l = left.len_l;
            if(right.len_r == r - mid) ret.len_r = right.len_r + left.len_r;
            else ret.len_r = right.len_r;
            if(left.len0_l == mid - l + 1) ret.len0_l = left.len0_l + right.len0_l;
            else ret.len0_l = left.len0_l;
            if(right.len0_r == r - mid) ret.len0_r = right.len0_r + left.len0_r;
            else ret.len0_r = right.len0_r;
            return ret;
        }
    }
};
////////////////////////////////////////////////////////
void solve(){
    
    int n, m;
    cin >> n;
    vector<int> a(n+1);
    for(int i=1;i<=n;++i) cin >> a[i];
    SegTree T(n+10);
    T.build(1, 1, n, a);
    cin >> m;
    int op, x, y;
    while(m--){
        cin >> op >> x >> y;
        if(op){
            T.update(1, 1, n, x, y);
        }else{
            cout << T.getmax(1, 1, n, x, y).len << '\n';
        }
        // for(int i=1;i<=n;++i) cout << T.getval(1,1,n,i) << ' ';
        // cout << endl;
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