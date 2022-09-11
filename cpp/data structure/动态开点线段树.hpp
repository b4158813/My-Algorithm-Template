/*
    动态开点线段树 Dynamic Segment Tree
*/
template<class T>
class SegTree {
    struct Node {
        T val, tg, ls, rs;
        Node(): val(0), tg(0), ls(0), rs(0) {}
    };
    vector<Node> tr;
    int tcnt; // 0: [1, MAX]
    inline void push_down(int o, int l, int r) {
        if (!tr[o].ls) tr[o].ls = ++tcnt, tr.emplace_back(Node{});
        if (!tr[o].rs) tr[o].rs = ++tcnt, tr.emplace_back(Node{});
        if (!tr[o].tg) return;
        T k = tr[o].tg;
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

    // 区间加
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

    // 区间求和
    inline T getsum(int l, int r, int L, int R, int o = 0) {
        if (l >= L && r <= R) return tr[o].val;
        push_down(o, l, r);
        int mid = (l + r) >> 1;
        T ret = 0;
        if (mid >= L) ret += getsum(l, mid, L, R, tr[o].ls);
        if (mid+1 <= R) ret += getsum(mid+1, r, L, R, tr[o].rs);
        return ret;
    }
};
/////////////////////////////////