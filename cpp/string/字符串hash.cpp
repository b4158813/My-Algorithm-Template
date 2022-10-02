// 字符串哈希，查询时下标从 1 开始
struct StrHash{
    using ull = unsigned long long;
    static constexpr int P = 13331;
    static constexpr int N = 1e5+5;
    ull h[N], p[N]; // h[k]存储字符串前k个字母的哈希值, p[k]存储 P^k mod 2^64

    StrHash(const string &s){
        int n = s.size();
        p[0] = 1;
        for (int i = 1; i <= n; ++ i ){
            h[i] = h[i - 1] * P + s[i - 1];
            p[i] = p[i - 1] * P;
        }
    }

    // 计算子串 str[l ~ r] 的哈希值
    ull get(const int &l, const int &r){
        return h[r] - h[l - 1] * p[r - l + 1];
    }

};