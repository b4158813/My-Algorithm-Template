class DSU_node{
public:
    int sz;
    DSU_node* fa;
    DSU_node(): sz(1){
        fa = this;
    }
};

DSU_node* find(DSU_node* x){
    return (x==x->fa ? x : x->fa = find(x->fa));
}

void unite(DSU_node* x, DSU_node* y){
    if(!x || !y) return;
    x = find(x);
    y = find(y);
    if(x != y){
        y->fa = x;
        x->sz += y->sz;
    }
}
