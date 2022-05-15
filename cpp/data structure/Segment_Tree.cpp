/*
普通线段树 Segment Tree
*/
class SegTree {
    #define ls (i<<1)
    #define rs (i<<1|1)
    struct Node {
        ll val, tg;
        Node(): val(0), tg(0) {}
    };
    vector<Node> tr;
    void push_down(int i, int l, int r) {
        if (!tr[i].tg) return;
        int k = tr[i].tg;
        int mid = (l + r) >> 1;
        tr[ls].val = (tr[ls].val + k * (mid - l + 1));
        tr[rs].val = (tr[rs].val + k * (r - mid));
        tr[ls].tg = (tr[ls].tg + k);
        tr[rs].tg = (tr[rs].tg + k);
        tr[i].tg = 0;
    }
    void push_up(int i) {
        tr[i].val = (tr[ls].val + tr[rs].val);
    }

public:
    SegTree(const int &N): tr(N<<2) {}

    void build(int i, int l, int r){
        if(l==r){
            return;
        }
        int mid = (l + r) >> 1;
        build(ls, l, mid);
        build(rs, mid+1, r);
        push_up(i);
    }

    // given init
    void build_by_val(int i,int l,int r,const vector<int> &a){
        if(l==r){
            tr[i].val = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build_by_val(ls, l, mid, a);
        build_by_val(rs, mid+1, r, a);
        push_up(i);
    }

    void update(int i, int l, int r, int L, int R, int k) {
        if (l >= L && r <= R) {
            tr[i].tg = (tr[i].tg + k);
            tr[i].val = (tr[i].val + (ll)k * (r - l + 1));
            return;
        }
        push_down(i, l, r);
        int mid = (l + r) >> 1;
        if (mid >= L) update(ls, l, mid, L, R, k);
        if (mid+1 <= R) update(rs, mid+1, r, L, R, k);
        push_up(i);
    }

    ll getsum(int i, int l, int r, int L, int R) {
        if (l >= L && r <= R) return tr[i].val;
        push_down(i, l, r);
        int mid = (l + r) >> 1;
        ll ret = 0;
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
        ll val, tg, ls, rs;
        Node(): val(0), tg(0), ls(0), rs(0) {}
    };
    vector<Node> tr;
    int tcnt; // 0: [1, MAX]
    void push_down(int o, int l, int r) {
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
    void push_up(int o) {
        tr[o].val = tr[tr[o].ls].val + tr[tr[o].rs].val;
    }

public:
    SegTree(): tr(1), tcnt(0) {}

    void update(int l, int r, int L, int R, int k, int o = 0) {
        if (l >= L && r <= R) {
            tr[o].tg += k;
            tr[o].val += (ll)k * (r - l + 1);
            return;
        }
        push_down(o, l, r);
        int mid = (l + r) >> 1;
        if (mid >= L) update(l, mid, L, R, k, tr[o].ls);
        if (mid+1 <= R) update(mid+1, r, L, R, k, tr[o].rs);
        push_up(o);
    }

    ll getsum(int l, int r, int L, int R, int o = 0) {
        if (l >= L && r <= R) return tr[o].val;
        push_down(o, l, r);
        int mid = (l + r) >> 1;
        ll ret = 0;
        if (mid >= L) ret += getsum(l, mid, L, R, tr[o].ls);
        if (mid+1 <= R) ret += getsum(mid+1, r, L, R, tr[o].rs);
        return ret;
    }
};
