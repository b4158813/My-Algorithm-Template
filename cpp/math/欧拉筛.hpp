/*
    欧拉筛 求 素数(√）、欧拉函数(√)、莫比乌斯函数(todo)
    time complexity: O(N)
*/
constexpr int N = 1e5;
vector<int> prime, f(N + 5), phi(N + 5), mu(N + 5);
static auto init_euler = [] {
    phi[1] = 1;       //欧拉函数：小于等于n的与n互质的正整数个数
    f[0] = f[1] = 1;  // 0：素数，1：合数
    mu[1] = 1;        // 莫比乌斯函数
    for (int i = 2; i <= N; i++) {
        if (!f[i]) {
            prime.emplace_back(i);
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for (auto &&p: prime) {
            if(p * i > N) {
                break;
            }
            f[i * p] = 1;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                mu[i * p] = 0; // 有平方因子
                break;
            } else {
                phi[i * p] = phi[i] * phi[p];  //积性函数
                mu[i * p] = -mu[i];            // 同上
            }
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