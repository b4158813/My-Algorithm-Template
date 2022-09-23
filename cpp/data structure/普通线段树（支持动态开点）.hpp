/*
    线段树 Segment Tree（支持动态开点）
    
    支持常规操作：
        1. 单点修改
        2. 区间加
        3. 区间求和
        4. 区间最值（最大/最小）
        5. 区间查找 <= k 的第一个数的下标（树上二分）
    
    注意根节点：
        - 普通线段树：1
        - 动态开点：0
    
    使用方式：
        - 非动态开点：
            SegTree<int> Seg(n);
            Seg.build(1, 1, n, a); // 建树
        - 动态开点：
            开启 #define DYNAMIC
*/


// #define DYNAMIC // 是否开启动态开点
template<class T>
class SegTree {

    static constexpr T T_MIN = (std::is_same<T,int>::value ? INT_MIN : LLONG_MIN);
    static constexpr T T_MAX = (std::is_same<T,int>::value ? INT_MAX : LLONG_MAX);

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

public:
    #ifdef DYNAMIC
        SegTree(): tcnt(0), tr(1) {}
    #else
        // 初值初始化
        void build(int i,int l,int r,const vector<T> &a){
            if(l==r){
                tr[i].val = tr[i].maxh = a[l];
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

    // 单点修改
    void change_point(int i, int l, int r, int pos, T k) {
        if (l == r) {
            tr[i].val = tr[i].maxh = k;
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