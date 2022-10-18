
/* ModInt类 */
////////////////////////////////////////////////////////////////////////////////
template <unsigned M_> struct ModInt {
    static constexpr unsigned M = M_;
    unsigned x;
    constexpr ModInt() : x(0U) {}
    constexpr ModInt(unsigned x_) : x(x_ % M) {}
    constexpr ModInt(unsigned long long x_) : x(x_ % M) {}
    constexpr ModInt(int x_) : x(((x_ %= static_cast<int>(M)) < 0) ? (x_ + static_cast<int>(M)) : x_) {}
    constexpr ModInt(long long x_) : x(((x_ %= static_cast<long long>(M)) < 0) ? (x_ + static_cast<long long>(M)) : x_) {}
    ModInt &operator+=(const ModInt &a) { x = ((x += a.x) >= M) ? (x - M) : x; return *this; }
    ModInt &operator-=(const ModInt &a) { x = ((x -= a.x) >= M) ? (x + M) : x; return *this; }
    ModInt &operator*=(const ModInt &a) { x = (static_cast<unsigned long long>(x) * a.x) % M; return *this; }
    ModInt &operator/=(const ModInt &a) { return (*this *= a.inv()); }
    template <class T> ModInt &operator+=(const T &a) { x = ((x += ModInt(a).x) >= M) ? (x - M) : x; return *this; }
    template <class T> ModInt &operator-=(const T &a) { x = ((x -= ModInt(a).x) >= M) ? (x + M) : x; return *this; }
    template <class T> ModInt &operator*=(const T &a) { x = (static_cast<unsigned long long>(x) * ModInt(a).x) % M; return *this; }
    template <class T> ModInt &operator/=(const T &a) { return (*this *= ModInt(a).inv()); }
    ModInt pow(long long e) const { // qpow
        if (e < 0) return inv().pow(-e);
        ModInt a = *this, b = 1U; for (; e; e >>= 1) { if (e & 1) b *= a; a *= a; } return b;
    }
    ModInt inv() const { // exgcd
        unsigned a = M, b = x; int y = 0, z = 1;
        for (; b; ) { const unsigned q = a / b; const unsigned c = a - q * b; a = b; b = c; const int w = y - static_cast<int>(q) * z; y = z; z = w; }
        assert(a == 1U); return ModInt(y);
    }
    ModInt operator+() const { return *this; }
    ModInt operator-() const { ModInt a; a.x = x ? (M - x) : 0U; return a; }
    ModInt operator+(const ModInt &a) const { return (ModInt(*this) += a); }
    ModInt operator-(const ModInt &a) const { return (ModInt(*this) -= a); }
    ModInt operator*(const ModInt &a) const { return (ModInt(*this) *= a); }
    ModInt operator/(const ModInt &a) const { return (ModInt(*this) /= a); }
    template <class T> friend ModInt operator+(T a, const ModInt &b) { return (ModInt(a) += b); }
    template <class T> friend ModInt operator-(T a, const ModInt &b) { return (ModInt(a) -= b); }
    template <class T> friend ModInt operator*(T a, const ModInt &b) { return (ModInt(a) *= b); }
    template <class T> friend ModInt operator/(T a, const ModInt &b) { return (ModInt(a) /= b); }
    explicit operator bool() const { return x; }
    bool operator==(const ModInt &a) const { return (x == a.x); }
    bool operator!=(const ModInt &a) const { return (x != a.x); }
    friend std::ostream &operator<<(std::ostream &os, const ModInt &a) { return os << a.x; }
};
////////////////////////////////////////////////////////////////////////////////
constexpr int mod = 1e9+7;
using mint = ModInt<mod>;


/*
    结合ModInt类的 O(N)预处理阶乘逆元 + O(1)求组合数
*/
constexpr int N = 1e5;
vector<mint> fac(N+5), ifac(N+5);
int init_fac = []{
    fac[0] = 1;
    for (int i = 1; i <= N; i++)
        fac[i] = fac[i - 1] * i;

    ifac[N] = mint(fac[N]).pow(mod-2);
    for (int i = N - 1; i >= 0; i--)
        ifac[i] = ifac[i + 1] * (i + 1);
    return 0;
}();

inline mint C(int n, int m) {
    return (n < m) ? 0 : fac[n] * ifac[m] * ifac[n - m];
}

/*
    自动扩容版求组合数 O(n logn)
*/
vector<mint> fac(1,1), ifac(1,1);
inline mint C(int n, int m) {
    if(n < m) return 0;
    while((int)fac.size() < n + 1){
        fac.emplace_back(fac.back() * (int)fac.size());
        ifac.emplace_back(1 / fac.back());
    }
    return fac[n] * ifac[m] * ifac[n - m];
}