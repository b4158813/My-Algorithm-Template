/*
    https://www.luogu.com.cn/problem/P2572
    初始为01序列，5种操作：
        1. 将[l, r]区间全变为0
        2. 将[l, r]区间全变为1
        3. 将[l, r]区间所有01值反转(0变1，1变0)
        4. 求[l ,r]区间1的个数
        5. 求[l, r]区间最长的连续1的长度
    
    此题类似 **线段树维护区间最大子段和**
    
    方法是 线段树区间合并：

        线段树节点维护值：
            - 左端点开始的最长连续1个数(len1_l)
            - 右端点开始的最长连续1个数(len1_r)
            - 区间最长连续1个数(len1)
            - 区间1的总个数(len1_tot)
            - 左端点开始的最长连续0个数(len0_l)
            - 右端点开始的最长连续0个数(len0_r)
            - 区间最长连续0个数(len0)
            - 区间0的总个数(len0_tot)
            - 反转标记（记录区间反转了几次->是否反转）(tag)
                0: 未反转
                1: 反转
            - 赋值标记（记录区间是否被赋值为0/1）(tag01)
                -1: 没有任何赋值
                0: 区间赋值为0
                1: 区间赋值为1

        push_up操作：
            len1 = max(ls的len1, rs的len1, ls的len1_r + rs的len1_l);
            len0 = max(ls的len0, rs的len0, ls的len0_r + rs的len0_l);
            len1_tot = ls的len1_tot + rs的len1_tot
            len0_tot = ls的len0_tot + rs的len0_tot
            len1_l = ls的len1_l + (ls的len1_l == ls区间长度 ? 0 : rs的len1_l)
            len1_r = ...
            len0_l = ...
            len0_r = ...

        push_down操作（重点）：
            赋值操作优先级高于反转，因此需要先考虑下传赋值标记
            如果赋值标记不为-1，则下传赋值标记，并将反转标记归零
            否则下传反转标记
            **注意**：下传反转标记时，需要考虑左右儿子是否有赋值标记，若有，需要将赋值标记也反转（易错点）
        
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
        int len_l, len_r, len, len_tot, len0_l, len0_r, len0, len0_tot, tg, tg01;
        Node(): len_l(0), len_r(0), len(0), len_tot(0), len0_l(0), len0_r(0), len0(0), len0_tot(0), tg(0), tg01(-1) {}
    };
    vector<Node> tr;
    inline void change(int i){
        swap(tr[i].len0_l, tr[i].len_l);
        swap(tr[i].len0_r, tr[i].len_r);
        swap(tr[i].len, tr[i].len0);
        swap(tr[i].len_tot, tr[i].len0_tot);
        if(tr[i].tg01 != -1) tr[i].tg01 ^= 1;
        else tr[i].tg ^= 1;
    }
    inline void push_down(int i, int l, int r){
        int mid = (l+r) >> 1;
        if(tr[i].tg01==0){
            tr[ls].len0_l = tr[ls].len0_r = tr[ls].len0 = tr[ls].len0_tot = mid-l+1;
            tr[ls].len_l = tr[ls].len_r = tr[ls].len = tr[ls].len_tot = 0;
            tr[rs].len0_l = tr[rs].len0_r = tr[rs].len0 = tr[rs].len0_tot = r-mid;
            tr[rs].len_l = tr[rs].len_r = tr[rs].len = tr[rs].len_tot = 0;
            tr[ls].tg = tr[rs].tg = 0;
            tr[ls].tg01 = tr[rs].tg01 = 0;
            tr[i].tg01 = -1;
            tr[i].tg = 0;
            return;
        }else if(tr[i].tg01==1){
            tr[ls].len0_l = tr[ls].len0_r = tr[ls].len0 = tr[ls].len0_tot = 0;
            tr[ls].len_l = tr[ls].len_r = tr[ls].len = tr[ls].len_tot = mid-l+1;
            tr[rs].len0_l = tr[rs].len0_r = tr[rs].len0 = tr[rs].len0_tot = 0;
            tr[rs].len_l = tr[rs].len_r = tr[rs].len = tr[rs].len_tot = r-mid;
            tr[ls].tg = tr[rs].tg = 0;
            tr[ls].tg01 = tr[rs].tg01 = 1;
            tr[i].tg01 = -1;
            tr[i].tg = 0;
            return;
        }
        if(!tr[i].tg) return;
        change(ls);
        change(rs);
        tr[i].tg = 0;
    }
    inline void push_up(int i, int l, int r) {
        int mid = (l + r) >> 1;
        tr[i].len = max({tr[ls].len, tr[rs].len, tr[ls].len_r + tr[rs].len_l});
        tr[i].len0 = max({tr[ls].len0, tr[rs].len0, tr[ls].len0_r + tr[rs].len0_l});
        tr[i].len_tot = tr[ls].len_tot + tr[rs].len_tot;
        tr[i].len0_tot = tr[ls].len0_tot + tr[rs].len0_tot;
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
    SegTree(const int &N): tr(N<<3) {}

    // given init value
    inline void build(int i,int l,int r,const vector<int> &a){
        if(l==r){
            tr[i].len_l = tr[i].len_r = tr[i].len = tr[i].len_tot = a[l];
            tr[i].len0_l = tr[i].len0_r = tr[i].len0 = tr[i].len0_tot = (a[l]==0);
            tr[i].tg = 0, tr[i].tg01 = -1;
            return;
        }
        int mid = (l + r) >> 1;
        build(ls, l, mid, a);
        build(rs, mid+1, r, a);
        push_up(i, l, r);
    }

    inline void update_0(int i, int l, int r, int L, int R){
        if (l >= L && r <= R) {
            tr[i].len0_l = tr[i].len0_r = tr[i].len0 = tr[i].len0_tot = r - l + 1;
            tr[i].len_l = tr[i].len_r = tr[i].len = tr[i].len_tot = 0;
            tr[i].tg = 0;
            tr[i].tg01 = 0;
            return;
        }
        push_down(i,l,r);
        int mid = (l + r) >> 1;
        if (mid >= L) update_0(ls, l, mid, L, R);
        if (mid+1 <= R) update_0(rs, mid+1, r, L, R);
        push_up(i, l, r);
    }

    inline void update_1(int i, int l, int r, int L, int R){
        if (l >= L && r <= R) {
            tr[i].len0_l = tr[i].len0_r = tr[i].len0 = tr[i].len0_tot = 0;
            tr[i].len_l = tr[i].len_r = tr[i].len = tr[i].len_tot = r - l + 1;
            tr[i].tg = 0;
            tr[i].tg01 = 1;
            return;
        }
        push_down(i,l,r);
        int mid = (l + r) >> 1;
        if (mid >= L) update_1(ls, l, mid, L, R);
        if (mid+1 <= R) update_1(rs, mid+1, r, L, R);
        push_up(i, l, r);
    }

    inline void flip(int i, int l, int r, int L, int R) {
        if (l >= L && r <= R) {
            change(i);
            return;
        }
        push_down(i,l,r);
        int mid = (l + r) >> 1;
        if (mid >= L) flip(ls, l, mid, L, R);
        if (mid+1 <= R) flip(rs, mid+1, r, L, R);
        push_up(i, l, r);
    }

    inline int get_tot(int i, int l, int r, int L, int R){
        if (l >= L && r <= R) return tr[i].len_tot;
        push_down(i,l,r);
        int mid = (l + r) >> 1;
        int res = 0;
        if (mid >= L) res += get_tot(ls, l, mid, L, R);
        if (mid+1 <= R) res += get_tot(rs, mid+1, r, L, R);
        return res;
    }

    inline Node getmax(int i, int l, int r, int L, int R) {
        if (l >= L && r <= R) return tr[i];
        push_down(i,l,r);
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
    cin >> n >> m;
    vector<int> a(n+1);
    for(int i=1;i<=n;++i) cin >> a[i];
    SegTree T(n+10);
    T.build(1, 1, n, a);
    int op, x, y;
    while(m--){
        cin >> op >> x >> y;
        x++, y++;
        if(op == 0){
            T.update_0(1, 1, n, x, y);
        }else if(op == 1){
            T.update_1(1, 1, n, x, y);
        }else if(op == 2){
            T.flip(1, 1, n, x, y);
        }else if(op == 3){
            cout << T.get_tot(1, 1, n, x, y) << '\n';
        }else if(op == 4){
            cout << T.getmax(1, 1, n, x, y).len << '\n';
        }
        // for(int i=1;i<=n;++i) cout << T.get_tot(1,1,n,i,i) << " ";
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