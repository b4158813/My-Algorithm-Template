// Trie树
// 数组版本（记得在堆区创建对象，每次使用前clear()）
struct Trie {
    static constexpr int N = 1000010, M = 26;

    int tot;
    int tr[N][M];
    int flag[N];

    Trie(): tot(0) {}

    virtual void clear() {
        for(int i = 0; i <= tot; i++) {
            memset(tr[i], 0, sizeof tr[i]);
            flag[i] = 0;
        }
        tot = 0;
    }

    // 插入一个字符串
    void insert(const string &s) {
        int rt = 0;
        for(auto &&ch : s) {
            int id = ch - 'a';
            if(!tr[rt][id]) tr[rt][id] = ++tot;
            rt = tr[rt][id];
        }
        flag[rt] ++;
    }

    // 查询字符串s在trie树包含的所有模式串中的出现次数
    int query(const string &s) {
        int rt = 0;
        for(auto &&ch : s) {
            int id = ch - 'a';
            if (!tr[rt][id]) return 0;
            rt = tr[rt][id];
        }
        return flag[rt];
    }
};

// AC自动机 继承自 Trie树（数组版本）
struct AC_Automaton: Trie {
    
    int fail[N]; // 失配指针
    int sum[N]; // fail树树上前缀和 统计模式串出现次数
    int idx[N]; // idx[i]代表第i个字符串对应的rt节点编号

    void clear() override {
        for(int i = 0; i <= tot; i ++) {
            fail[i] = sum[i] = 0;
        }
        Trie::clear();
    }

    // 插入第i个字符串
    void insert(const string &s, int num) {
        int rt = 0;
        for(auto &&ch : s) {
            int id = ch - 'a';
            if(!tr[rt][id]) tr[rt][id] = ++tot;
            rt = tr[rt][id];
        }
        flag[rt] ++;
        idx[num] = rt;
    }

    // 构建fail失配指针
    void build_fail() {
        queue<int> q;
        for(int v, i=0;i<M;++i) {
            v = tr[0][i];
            if(v) {
                fail[v] = 0;
                q.emplace(v);
            }
        }
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(int v, i=0;i<M;++i) {
                v = tr[u][i];
                if(v) {
                    fail[v] = tr[fail[u]][i];
                    q.emplace(v);
                }else {
                    tr[u][i] = tr[fail[u]][i];
                }
            }
        }
    }

    // 查询AC自动机中有多少模式串在文本串s中的出现过
    int query(const string &s) {
        int rt{0}, res{0};
        for(auto &&ch: s) {
            int id = ch - 'a';
            int v = tr[rt][id];
            while(v && flag[v] != -1) {
                res += flag[v];
                flag[v] = -1;
                v = fail[v];
            }
            rt = tr[rt][id];
        }
        return res;
    }

    // 构建fail树
    vector<vector<int>> e; // fail树
    void build_fail_tree() {
        e.clear();
        e.resize(tot + 1);
        for(int i=1;i<=tot;++i) {
            e[fail[i]].emplace_back(i);
        }
    }

    // 求每个模式串在文本串s中的出现次数（fail树上求前缀和）
    void get_cnt(const string& s) {
        int rt{0};
        for(auto &&ch: s) {
            int id = ch - 'a';
            int v = tr[rt][id];
            sum[v] ++;
            rt = tr[rt][id];
        }

        auto dfs = [&](auto &&self, int u) -> void {
            for(auto &&v: e[u]) {
                self(self, v);
                sum[u] += sum[v];
            }
        };
        dfs(dfs, 0);
    }
}aca;