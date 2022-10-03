/*
    线段树 Segment Tree（支持动态开点）
    
    支持常规操作：
        1. 单点修改
        2. 区间加
        3. 区间求和
        4. 区间最值（最大/最小）
        5. 区间查找 <= k 的第一个数的下标（树上二分）
    
    根节点：均为 1
    使用方式：
        - 非动态开点：
            SegTree<int> Seg(n); // 开1个普通线段树
            Seg.build(1, 1, n, a); // 以vector a为初值建树，表示[1,n]区间
        - 动态开点：
            开启 #define DYNAMIC
            SegTree<int> Seg; // 开一个动态开点线段树
            SegTree<int> Seg(n); // 开n个动态开点线段树，下标 1 ~ n（用同一个vector<Node>表示，线段树合并时使用）
            SegTree<int> Seg[n]; // 开n个动态开点线段树（不需要合并时也可以这么用）
*/


// #define DYNAMIC // 是否开启动态开点
template<class T>
class SegTree {
public:
    static constexpr T T_MIN = numeric_limits<T>::lowest();
    static constexpr T T_MAX = numeric_limits<T>::max();

    struct Node {
        T val, maxh, tg;
        #ifdef DYNAMIC
            int ls, rs;
        #endif
        Node(): val(0), maxh(0), tg(0) {
            #ifdef DYNAMIC
                ls = 0, rs = 0;
            #endif
        }
    };

    #ifdef DYNAMIC
        #define ls (tr[i].ls)
        #define rs (tr[i].rs)
        int tcnt; // 动态节点数
    #else
        #define ls (i<<1)
        #define rs (i<<1|1)
    #endif

    vector<Node> tr;

    void push_down(int i, int l, int r) {
        #ifdef DYNAMIC
            if(!ls) ls = ++tcnt, tr.emplace_back(Node{});
            if(!rs) rs = ++tcnt, tr.emplace_back(Node{});
        #endif
        if (!tr[i].tg) return;
        T k = tr[i].tg;
        int mid = (l + r) >> 1;
        tr[ls].val += k * (mid - l + 1);
        tr[rs].val += k * (r - mid);
        tr[ls].maxh += k;
        tr[rs].maxh += k;
        tr[ls].tg += k;
        tr[rs].tg += k;
        tr[i].tg = 0;
    }
    void push_up(int i) {
        tr[i].val = tr[ls].val + tr[rs].val;
        tr[i].maxh = max(tr[ls].maxh, tr[rs].maxh);
    }


    /* 构造与初始化 */
    #ifdef DYNAMIC
        SegTree(): tcnt(1), tr(2) {}
        // 开N棵动态开点线段树，根节点分别为 1 ~ N（用于线段树合并）
        SegTree(const int &N): tcnt(N), tr(N+1) {}

        // 线段树合并：将b为根的树合并到a为根的树上
        int merge(int a, int b, int l, int r){
            if(!a) return b;
            if(!b) return a;
            if(l == r){
                /* 合并信息操作 */
                return a;
            }
            int mid = (l + r) >> 1;
            tr[a].LS = merge(tr[a].LS, tr[b].LS, l, mid);
            tr[a].RS = merge(tr[a].RS, tr[b].RS, mid + 1, r);
            push_up(a);
            return a;
        }
    #else
        // 初值初始化
        void build(int i,int l,int r,const vector<T> &a){
            if(l==r){
                tr[i].val = a[l];
                tr[i].maxh = a[l];
                return;
            }
            int mid = (l + r) >> 1;
            build(ls, l, mid, a);
            build(rs, mid+1, r, a);
            push_up(i);
        }

        void RESIZE(const int &N) { tr.resize(N<<2); }
        SegTree() = default;
        SegTree(const int &N): tr(N<<2) {}
        SegTree(const int &N, const vector<T> &a): tr(N<<2) { build(1, 1, N, a); }
    #endif
    /* 构造与初始化 */


    // 单点修改
    void change_point(int i, int l, int r, int pos, T k) {
        if (l == r) {
            tr[i].val = k;
            tr[i].maxh = k;
            return;
        }
        push_down(i, l, r);
        int mid = (l + r) >> 1;
        if (pos <= mid) change_point(ls, l, mid, pos, k);
        else change_point(rs, mid+1, r, pos, k);
        push_up(i);
    }

    // 区间加
    void add_range(int i, int l, int r, int L, int R, T k) {
        if (l >= L && r <= R) {
            tr[i].tg += k;
            tr[i].maxh += k;
            tr[i].val += k * (r - l + 1);
            return;
        }
        push_down(i, l, r);
        int mid = (l + r) >> 1;
        if (mid >= L) add_range(ls, l, mid, L, R, k);
        if (mid+1 <= R) add_range(rs, mid+1, r, L, R, k);
        push_up(i);
    }

    // 区间求max/min
    T getmax(int i, int l, int r, int L, int R){
        if(l >= L && r <= R) return tr[i].maxh;
        push_down(i, l, r);
        int mid = (l + r) >> 1;
        T ret = T_MIN;
        if(mid >= L) ret = max(ret, getmax(ls, l, mid, L, R));
        if(mid + 1 <= R) ret = max(ret, getmax(rs, mid+1, r, L, R));
        return ret;
    }

    // 区间求和
    T getsum(int i, int l, int r, int L, int R) {
        if (l >= L && r <= R) return tr[i].val;
        push_down(i, l, r);
        int mid = (l + r) >> 1;
        T ret = 0;
        if (mid >= L) ret += getsum(ls, l, mid, L, R);
        if (mid+1 <= R) ret += getsum(rs, mid+1, r, L, R);
        return ret;
    }
    
    // 在[L,R]内查找小于等于k的第一个数的下标（不存在返回-1）
    int getleft_idx(int i, int l, int r, int L, int R, T k){
        if(tr[i].maxh < k) return -1;
        if(l == r) return l;
        push_down(i, l, r);
        int mid = (l + r) >> 1;
        if(mid >= R) return getleft_idx(ls, l, mid, L, R, k);
        else if(mid+1 <= L) return getleft_idx(rs, mid+1, r, L, R , k);
        else{
            int left = getleft_idx(ls, l, mid, L, R, k);
            if(left != -1) return left;
            int right = getleft_idx(rs, mid+1, r, L, R, k);
            if(right != -1) return right;
            return -1;
        }
    }

};
////////////////////////////////////////////////////////