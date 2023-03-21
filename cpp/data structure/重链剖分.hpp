/*

    重链剖分(Heavy Light Decomposition)
        - 用处：维护树上操作，通常结合线段树等
        - 原理：一棵树被完全剖分成若干重链，任意两点间的链个数小于等于 log2(两点间距离)

    trick:
        1. 边权转点权：
            - 构造时 U = pii
            - 需要修改dfs1中的遍历参数 v->[w, v], 以及 添加 边权转点权操作（用w维护）
            - 对树上route操作时，在最后 x,y 处在同一条重链上时，需要判x,y是否重合
            如果是则不做操作(因为LCA的权值代表其父节点边权)
            否则只处理[id[x]+1, id[y]]这个区间

                 x(y)              x
                /   \             / \
              ...   ...         ...  .
                                      \
                                       y
                                        \
                                        ...

    注：
        - 此代码默认所有下标从 1 开始

*/

// 重链剖分模板 <权值类型, 树边类型>
template <class T, class U>
class HLD {
public:

    int n, root;          // 树节点个数, 根节点
    vector<vector<U>> e;  // 树边
    int dfsx = 0;         // dfs序总数

    // 每个节点对应的dfs序、深度、子树大小、父节点、重儿子、重链顶
    vector<int> id, dep, sz, fa, bigson, top;
    
    // 需要维护的值(以节点为下标，动态开点不需要)
    vector<T> a;

    // 需要维护的值(以dfs序为下标，动态开点不需要)
    vector<T> w;

    // 线段树(多棵请使用vector包装)
    // 若动态开点，则自行在外部实现初始化逻辑
    SegTree<T> Seg;

    // 第一次dfs：处理出 深度、父亲、子树大小、重儿子
    void dfs1(int u, int fath, int depth) {
        dep[u] = depth;
        fa[u] = fath;
        sz[u] = 1;
        for (auto&& v : e[u]) {
            if (v == fath)
                continue;

            /* 边权转点权 */
            // w[v] = w;

            dfs1(v, u, depth + 1);
            sz[u] += sz[v];
            if (sz[v] > sz[bigson[u]])
                bigson[u] = v;
        }
    }

    // 第二次dfs：求出 dfs序、dfs序对应初始值、节点所在链的顶端
    void dfs2(int u, int topf) {
        id[u] = ++dfsx;

        /* 需要维护的值(动态开点不需要) */
        w[dfsx] = a[u];

        top[u] = topf;
        if (!bigson[u])
            return;
        dfs2(bigson[u], topf);  // 先搞重儿子所在链
        for (auto&& v : e[u]) {
            if (v == fa[u] || v == bigson[u])
                continue;
            dfs2(v, v);  // 再搞轻儿子所在链
        }
    }

    // 构造函数 + 初始化
    // 节点数、根节点、边、需要维护的权值
    HLD(int _n, int _root, const vector<vector<U>> &_e, const vector<T> &_a)
        : n(_n), root(_root), e(_e), a(_a) {

        id.resize(n+1);
        dep.resize(n+1);
        sz.resize(n+1);
        fa.resize(n+1);
        bigson.resize(n+1);
        top.resize(n+1);

        a.resize(n+1);
        w.resize(n+1);

        dfs1(root, -1, 1);
        dfs2(root, root);

        Seg.RESIZE(n);
        Seg.build(1, 1, n, w);
    }

    // get LCA
    int LCA(int x, int y) {
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]])
                swap(x, y);
            x = fa[top[x]];
        }
        return dep[x] < dep[y] ? x : y;
    };


    // 把节点x权值改为k
    void changepoint(int x, T k){
        Seg.change_point(1, 1, n, id[x], k);
    }

    // [x,y] 路径上点权值 + k
    void addroute(int x, int y, T k) {
        while (top[x] != top[y]) {              // 如果不属于同一条重链
            if (dep[top[x]] < dep[top[y]])  // 设x所在链头部较深
                swap(x, y);
            Seg.add_range(1, 1, n, id[top[x]], id[x], k);
            x = fa[top[x]];  // x跳到所在链头部的父节点上，继续下去
        }
        // 直到x、y在同一重链上
        if (dep[x] > dep[y])
            swap(x, y);                             // 设x较浅
        Seg.add_range(1, 1, n, id[x], id[y], k);  // 对重链对应区间更新
    }

    // 求 [x, y] 路径上点最大权值
    T getroutemax(int x,int y){
        T res = LLONG_MIN;
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]])
                swap(x, y);
            res = max(res, Seg.getmax(1, 1, n, id[top[x]], id[x]));
            x = fa[top[x]];
        }
        if (dep[x] > dep[y])
            swap(x, y);
        res = max(res, Seg.getmax(1, 1, n, id[x], id[y]));
        return res;
    }

    // 求 [x, y] 路径上点权值和
    T getroutesum(int x, int y) {
        T res = 0;
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]])
                swap(x, y);
            res += Seg.getsum(1, 1, n, id[top[x]], id[x]);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y])
            swap(x, y);
        res += Seg.getsum(1, 1, n, id[x], id[y]);
        return res;
    }

    // 以x为根的子树权值 + k
    void addroot(int x, T k){
        Seg.add_range(1, 1, n, id[x], id[x] + sz[x] - 1, k);
    }

    // 求以x为根的子树权值和
    T getrootsum(int x){
        return Seg.getsum(1, 1, n, id[x], id[x] + sz[x] - 1);
    }

};

/*----------------------------------------------------------*/