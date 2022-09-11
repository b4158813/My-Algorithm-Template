/*
    普通线段树 Segment Tree
    
    支持操作：
        1. 区间加
        2. 区间求和
        3. 区间最值（最大 最小）
        4. 区间查找 <= k 的第一个数的下标（树上二分）
    
    支持套modint类
*/
template<class T>
class SegTree {
    #define ls (i<<1)
    #define rs (i<<1|1)
    const T T_MIN = (std::is_same<T,int>::value ? INT_MIN : LLONG_MIN);
    const T T_MAX = (std::is_same<T,int>::value ? INT_MAX : LLONG_MAX);
    struct Node {
        T val, maxh, tg;
        Node(): val(0), maxh(0), tg(0) {}
    };
    vector<Node> tr;
    inline void push_down(int i, int l, int r) {
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
    inline void push_up(int i) {
        tr[i].val = (tr[ls].val + tr[rs].val);
        tr[i].maxh = max(tr[ls].maxh, tr[rs].maxh);
    }

public:
    SegTree() = default;

    SegTree(const int &N): tr(N<<2) {}

    // 初值初始化
    inline void build(int i,int l,int r,const vector<int> &a){
        if(l==r){
            tr[i].val = tr[i].maxh = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(ls, l, mid, a);
        build(rs, mid+1, r, a);
        push_up(i);
    }

    // 区间加
    inline void update(int i, int l, int r, int L, int R, T k) {
        if (l >= L && r <= R) {
            tr[i].tg += k;
            tr[i].val += k * (r - l + 1);
            return;
        }
        push_down(i, l, r);
        int mid = (l + r) >> 1;
        if (mid >= L) update(ls, l, mid, L, R, k);
        if (mid+1 <= R) update(rs, mid+1, r, L, R, k);
        push_up(i);
    }

    // 区间求max/min
    inline T getmax(int i, int l, int r, int L, int R){
        if(l >= L && r <= R) return tr[i].maxh;
        push_down(i, l, r);
        int mid = (l + r) >> 1;
        T ret = T_MIN;
        if(mid >= L) ret = max(ret, getmax(ls, l, mid, L, R));
        if(mid + 1 <= R) ret = max(ret, getmax(rs, mid+1, r, L, R));
        return ret;
    }

    // 区间求和
    inline T getsum(int i, int l, int r, int L, int R) {
        if (l >= L && r <= R) return tr[i].val;
        push_down(i, l, r);
        int mid = (l + r) >> 1;
        T ret = 0;
        if (mid >= L) ret += getsum(ls, l, mid, L, R);
        if (mid+1 <= R) ret += getsum(rs, mid+1, r, L, R);
        return ret;
    }
    
    // 在[L,R]内查找小于等于k的第一个数的下标（不存在返回-1）
    inline int getleft_idx(int i, int l, int r, int L, int R, T k){
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