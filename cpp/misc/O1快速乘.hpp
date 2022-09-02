/*
        O1快速乘
        用来解决 long long 乘以 long long 爆 long long 的问题
*/
inline ll multi(ll x, ll y, ll Mod) {
    ll tmp = (x * y - (ll)((long double)x / Mod * y + 1.0e-8) * Mod);
    return tmp < 0 ? tmp + Mod : tmp;
}