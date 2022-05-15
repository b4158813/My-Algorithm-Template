#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// https://vjudge.net/problem/LightOJ-1205
// 求区间内回文数个数（数位DP）

ll dp[20][20][2];
int b[20];
ll gao(ll x){
    vector<int> a;
    while(x){
        a.emplace_back(x%10);
        x/=10;
    }
    
    auto dfs = [&](auto &&self, int pos,int len,bool sta, bool limit, bool lead) -> ll{
        if(pos == -1) return sta;
        if(!limit && !lead && dp[pos][len][sta]!=-1) return dp[pos][len][sta];
        int up = limit ? a[pos] : 9;
        ll res = 0;
        for(int i=0;i<=up;++i){
            b[pos] = i;
            if(lead && i==0){
                res += self(self,pos-1,len-1,sta, limit&&i==up, lead&&i==0);
            }else{
                if(sta && pos<=len/2)
                    res += self(self,pos-1,len, b[pos]==b[len-pos], limit&&i==up, lead&&i==0);
                else
                    res += self(self,pos-1, len, sta, limit&&i==up, lead&&i==0);
            }
        }
        if(!limit && !lead) dp[pos][len][sta] = res;
        return res;
    };
    int pos = a.size()-1;
    return dfs(dfs,pos, pos, true, true, true);
}

void solve(){
    memset(dp, -1, sizeof dp);
    ll x,y;
    cin>>x>>y;
    if(x>y) swap(x,y);
    cout<<gao(y) - gao(x-1)<<'\n';
    
}

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int _;
    cin>>_;
    int cnt = 0;
    while(_--){
        cout<<"Case "<<++cnt<<": ";
        solve();
        
    }
    
    return 0;
}
