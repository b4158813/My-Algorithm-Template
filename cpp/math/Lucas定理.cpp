//预处理阶乘逆元
ll ifac[N], fac[N];
inline void init_fac(int N) {
    fac[1] = 1;
    for (int i = 2; i <= N; i++)
        fac[i] = fac[i - 1] * i % mod;

    ifac[N] = qpow(fac[N], mod - 2, mod);
    for (int i = N - 1; i >= 0; i--)
        ifac[i] = ifac[i + 1] * (i + 1) % mod;
}

// Lucas定理求组合数，预处理阶乘fac[]
inline ll C(ll n, ll m, ll Mod) {
    return (n < m) ? 0 : fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
inline ll Lucas(ll n, ll m, ll Mod) {
    return (!m) ? 1 : Lucas(n / Mod, m / Mod, Mod) % Mod * C(n % Mod, m % Mod, Mod) % Mod;
}
