/*

    字典树（前缀树）模板

*/


// 指针版本（动态开点）
class Trie {
public:
    vector<Trie*> child;
    bool isEnd;
    int cnt; // 以当前节点字符为前缀的字符串个数

    Trie() : child(26), isEnd(false), cnt(0) {}

    void insert(string &s) { // 插入一个字符串
        Trie* node = this;
        for (auto &&ch: s) {
            int c = ch - 'a';
            if (!node->child[c]) node->child[c] = new Trie();
            node = node->child[c];
            node->cnt ++;
        }
        node->isEnd = true;
    }

    int query(string &s) {
        Trie* node = this;
        int res = 0;
        for (auto &&ch: s) {
            int c = ch - 'a';
            if(!node->child[c]) break;
            node = node->child[c];
        }
        return node->cnt;
    }
    
};



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
    void insert(string &s) {
        int rt = 0;
        for(auto &&ch : s) {
            int id = ch - 'a';
            if(!tr[rt][id]) tr[rt][id] = ++tot;
            rt = tr[rt][id];
        }
        flag[rt] ++;
    }

    // 查询字符串s在trie树包含的所有模式串中的出现次数
    int query(string &s) {
        int rt = 0;
        for(auto &&ch : s) {
            int id = ch - 'a';
            if (!tr[rt][id]) return 0;
            rt = tr[rt][id];
        }
        return flag[rt];
    }
};
