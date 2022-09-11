/*
    普通线段树
    支持操作：
        1. 区间加
        2. 区间乘
        3. 区间求和
*/
template<class T>
class SegTree {
    #define ls (i<<1)
    #define rs (i<<1|1)
    struct Node {
        T val, ptg, mtg;
        Node(): val(0), ptg(0), mtg(1) {}
    };
    vector<Node> tr;
    inline void push_down(int i, int l, int r) {
        T add = tr[i].ptg, mult = tr[i].mtg;
        int mid = (l + r) >> 1;
        tr[ls].val *= mult;
        tr[rs].val *= mult;
        tr[ls].val += add * (mid - l + 1);
        tr[rs].val += add * (r - mid);
        tr[ls].mtg *= mult;
        tr[rs].mtg *= mult;
        tr[ls].ptg *= mult;
        tr[rs].ptg *= mult;
        tr[ls].ptg += add;
        tr[rs].ptg += add;
        tr[i].ptg = 0;
        tr[i].mtg = 1;
    }
    inline void push_up(int i) {
        tr[i].val = (tr[ls].val + tr[rs].val);
    }

public:
    SegTree() = default;

    SegTree(const int &N): tr(N<<2) {}

    // 初值初始化
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

    // 区间加
    inline void range_add(int i, int l, int r, int L, int R, T k) {
        if (l >= L && r <= R) {
            tr[i].ptg += k;
            tr[i].val += k * (r - l + 1);
            return;
        }
        push_down(i, l, r);
        int mid = (l + r) >> 1;
        if (mid >= L) range_add(ls, l, mid, L, R, k);
        if (mid+1 <= R) range_add(rs, mid+1, r, L, R, k);
        push_up(i);
    }

    // 区间乘
    inline void range_mult(int i, int l, int r, int L, int R, T k) {
        if (l >= L && r <= R) {
            tr[i].mtg *= k;
            tr[i].ptg *= k;
            tr[i].val *= k;
            return;
        }
        push_down(i, l, r);
        int mid = (l + r) >> 1;
        if (mid >= L) range_mult(ls, l, mid, L, R, k);
        if (mid+1 <= R) range_mult(rs, mid+1, r, L, R, k);
        push_up(i);
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

};
////////////////////////////////////////////////////////