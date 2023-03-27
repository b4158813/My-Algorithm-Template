/*
    https://codeforces.com/problemset/problem/803/F
    问题：求 gcd == 1 的子序列的个数
    题解：莫比乌斯函数 + 容斥
    定义 f[i] 表示包含因子i的数组成的子序列的个数，则根据（包含不同质因子数的个数）进行容斥
    答案为：f[1] - f[1个质因子组成] + f[2个不同质因子组成] - f[3个不同质因子组成] ...
    可以发现，这个正负号就是莫比乌斯函数，于是用莫比乌斯函数来容斥就行了
*/

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int mod = 1e9 + 7;
constexpr int N = 1e5;
vector<int> prime, f(N + 5), mu(N + 5);
static auto init_euler = [] {
    f[0] = f[1] = 1;  // 0：素数，1：合数
    mu[1] = 1;        // 莫比乌斯函数
    for (int i = 2; i <= N; i++) {
        if (!f[i]) {
            prime.emplace_back(i);
            mu[i] = -1;
        }
        for (auto &&p: prime) {
            if(p * i > N) {
                break;
            }
            f[i * p] = 1;
            if (i % p == 0) {
                mu[i * p] = 0; // 有平方因子
                break;
            } else {
                mu[i * p] = -mu[i]; // 积性函数
            }
        }
    }
    return 0;
}();

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    unordered_map<int, int> ma;
    for(auto &&x: a) {
        cin >> x;
        ma[x] ++;
    }
    int maxh = *max_element(a.begin(), a.end());
    
    auto qpow = [&](ll x, ll y) {
        ll res = 1, base = x;
        while(y) {
            if(y & 1) {
                res = (res * base) % mod;
            }
            base = (base * base) % mod;
            y >>= 1;
        }
        return res;
    };

    
    ll ans{0};
    for(int i=1;i<=maxh;++i) {
        ll s{0};
        for(int j=i;j<=maxh;j+=i) {
            s += ma[j];
        }
        ans = (ans + 1LL * mu[i] * (qpow(2, s) - 1) % mod + mod) % mod;
    }
    
    cout << ans << '\n';
    
    return 0;
}