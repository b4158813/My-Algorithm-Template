#include<bits/stdc++.h>
using namespace std;
using ll = int64_t;
using pii = pair<int,int>;
constexpr int mod = 1e9+7;
void solve(){
    int n;
    cin>>n;
    vector<int> a(n+1);
    vector<int> inv(n+1);
    for(int i=1;i<=n;++i) cin>>a[i];
    inv[1] = 1;
    for(int i=2;i<=n;++i) // linearly calculate mod inverse of [1,2,...,n]
        inv[i] = 1LL * (mod-mod/i)*inv[mod%i]%mod;
    for(int i=2;i<=n;++i) // prefix of mod inverse of [1,2,...,n]
        inv[i] = (1LL * inv[i] + inv[i-1])%mod;
    int ans = 0;
    int tot = 0;
    int r = n, l = 0;
    for(int i=1;i<=(n+1)/2;++i){
        tot = (1LL * tot + inv[r--] - inv[l++] + mod) % mod;
        ans = (1LL * ans + 1LL * a[i] * tot ) % mod;
    }
    if(n%2==0) ans = (1LL * ans + 1LL * a[n/2+1] * tot) % mod;
    for(int i=(n+1)/2+1+(n%2==0);i<=n;++i){
        tot = (1LL * tot - inv[++r] + inv[--l] + mod) % mod;
        ans = (1LL * ans + 1LL * a[i] * tot) % mod;
    }
    cout<<ans<<'\n';
}

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int _ = 1;
//     cin>>_;
    while(_--){
        
        solve();
        
    }
    
    return 0;
}