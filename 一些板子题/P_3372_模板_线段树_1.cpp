#include<bits/stdc++.h>
using namespace std;
using ll = int64_t;
using pii = pair<int,int>;

// Segment Tree
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

void solve(){
    int n,m;
    cin>>n>>m;
    SegTree T;
    for(int x,i=1;i<=n;++i) cin>>x, T.update(1,n,i,i,x);
    for(int op,x,y,k,i=0;i<m;++i){
        cin>>op>>x>>y;
        if(op&1){
            cin>>k;
            T.update(1,n,x,y,k);
        }else{
            cout<<T.getsum(1,n,x,y)<<'\n';
        }
    }
    
}

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int _ = 1;
    // cin>>_;
    while(_--){
        
        solve();
        
    }
    
    return 0;
}