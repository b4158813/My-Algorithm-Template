/*

    重链剖分
        - 用处：维护树上操作，通常结合线段树等
        - 原理：一棵树被完全剖分成若干重链，任意两点间的链个数小于等于 log2(两点间距离)

    注：
        - 此代码默认所有下标从 1 开始

*/

// 重链剖分模板
template <class T, class U>
class TreeChain {
public:

    int n, root;          // 树节点个数, 根节点
    vector<vector<U>> e;  // 树边
    int dfsx = 0;         // dfs序总数

    // 每个节点对应的dfs序、深度、子树大小、父节点、重儿子、重链顶
    vector<int> csid, csdep, cssize, csfa, csson, cstop;
    
    // 需要维护的值(以节点为下标)
    vector<T> a;

    // 需要维护的值(以dfs序为下标)
    vector<T> csw;

    SegTree<T> Seg;  // 线段树

    // 第一次dfs：处理出 深度、父亲、子树大小、重儿子
    void csdfs1(int u, int fath, int depth) {
        csdep[u] = depth;
        csfa[u] = fath;
        cssize[u] = 1;
        for (auto&& v : e[u]) {
            if (v == fath)
                continue;

            /* 边权转点权 */
            // csw[v] = w;
            // wdep[v] += csw[v];

            csdfs1(v, u, depth + 1);
            cssize[u] += cssize[v];
            if (cssize[v] > cssize[csson[u]])
                csson[u] = v;
        }
    }

    // 第二次dfs：求出 dfs序、dfs序对应初始值、节点所在链的顶端
    void csdfs2(int u, int topf) {
        csid[u] = ++dfsx;

        /* 需要维护的值 */
        csw[dfsx] = a[u];

        cstop[u] = topf;
        if (!csson[u])
            return;
        csdfs2(csson[u], topf);  // 先搞重儿子所在链
        for (auto&& v : e[u]) {
            if (v == csfa[u] || v == csson[u])
                continue;
            csdfs2(v, v);  // 再搞轻儿子所在链
        }
    }

    // 构造函数 + 初始化
    // 节点数、根节点、边、需要维护的权值
    TreeChain(int _n, int _root, const vector<vector<U>> &_e, const vector<T> &_a)
        : n(_n), root(_root), e(_e), a(_a) {

        csid.resize(n+1);
        csdep.resize(n+1);
        cssize.resize(n+1);
        csfa.resize(n+1);
        csson.resize(n+1);
        cstop.resize(n+1);
        a.resize(n+1);
        csw.resize(n+1);

        csdfs1(root, -1, 1);
        csdfs2(root, root);

        Seg.RESIZE(n);
        Seg.build(1, 1, n, csw);
    }

    // get LCA
    int LCA(int x, int y) {
        while (cstop[x] != cstop[y]) {
            if (csdep[cstop[x]] < csdep[cstop[y]])
                swap(x, y);
            x = csfa[cstop[x]];
        }
        return csdep[x] < csdep[y] ? x : y;
    };


    // 把节点x权值改为k
    void changepoint(int x, T k){
        Seg.change_point(1, 1, n, csid[x], k);
    }

    // [x,y] 路径上点权值 + k
    void addroute(int x, int y, T k) {
        while (cstop[x] != cstop[y]) {              // 如果不属于同一条重链
            if (csdep[cstop[x]] < csdep[cstop[y]])  // 设x所在链头部较深
                swap(x, y);
            Seg.add_range(1, 1, n, csid[cstop[x]], csid[x], k);
            x = csfa[cstop[x]];  // x跳到所在链头部的父节点上，继续下去
        }
        // 直到x、y在同一重链上
        if (csdep[x] > csdep[y])
            swap(x, y);                             // 设x较浅
        Seg.add_range(1, 1, n, csid[x], csid[y], k);  // 对重链对应区间更新
    }

    // 求 [x, y] 路径上点最大权值
    T getroutemax(int x,int y){
        T res = LLONG_MIN;
        while (cstop[x] != cstop[y]) {
            if (csdep[cstop[x]] < csdep[cstop[y]])
                swap(x, y);
            res = max(res, Seg.getmax(1, 1, n, csid[cstop[x]], csid[x]));
            x = csfa[cstop[x]];
        }
        if (csdep[x] > csdep[y])
            swap(x, y);
        res = max(res, Seg.getmax(1, 1, n, csid[x], csid[y]));
        return res;
    }

    // 求 [x, y] 路径上点权值和
    T getroutesum(int x, int y) {
        T res = 0;
        while (cstop[x] != cstop[y]) {
            if (csdep[cstop[x]] < csdep[cstop[y]])
                swap(x, y);
            res += Seg.getsum(1, 1, n, csid[cstop[x]], csid[x]);
            x = csfa[cstop[x]];
        }
        if (csdep[x] > csdep[y])
            swap(x, y);
        res += Seg.getsum(1, 1, n, csid[x], csid[y]);
        return res;
    }

    // 以x为根的子树权值 + k
    void addroot(int x, T k){
        Seg.add_range(1, 1, n, csid[x], csid[x] + cssize[x] - 1, k);
    }

    // 求以x为根的子树权值和
    T getrootsum(int x){
        return Seg.getsum(1, 1, n, csid[x], csid[x] + cssize[x] - 1);
    }

};

/*----------------------------------------------------------*/