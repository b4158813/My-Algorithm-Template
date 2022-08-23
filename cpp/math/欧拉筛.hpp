// get phi[1~n]: O(n)
constexpr int N = 1e5;
vector<int> prime, f(N+5), phi(N+5);
int init_euler = [] {
    phi[1] = 1;       //欧拉函数：小于等于n的与n互质的正整数个数
    f[0] = f[1] = 1;  // 0：素数，1：合数
    for (int i = 2; i <= N; i++) {
        if (!f[i]) {
            prime.emplace_back(i);
            phi[i] = i - 1;
        }
        for (int j = 0; j < (int)prime.size() && i * prime[j] <= N; ++j) {
            f[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            } else
                phi[i * prime[j]] = phi[i] * phi[prime[j]];  //积性函数
        }
    }
    return 0;
}();

// get phi[n]: O(sqrt(n))
inline int getphi(int n) {
    int res = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            res = res / i * (i - 1);
        while (n % i == 0)
            n /= i;
    }
    if (n > 1)
        res = res / n * (n - 1);
    return res;
}