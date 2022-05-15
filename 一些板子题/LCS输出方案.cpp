#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

void solve(){
    
    string s,t;
    cin>>s>>t;
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            if(s[i-1]==t[j-1]){
                dp[i][j] = dp[i-1][j-1]+1;
            }else{
                dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            }
        }
    }
    vector<vector<int>> spos(26, vector<int>(n+1, 0));
    vector<vector<int>> tpos(26, vector<int>(m+1, 0));
    for(int i=1;i<=n;++i){
        for(int j=0;j<26;++j){
            if(s[i-1]==j+'a') spos[j][i] = i;
            else spos[j][i] = spos[j][i-1];
        }
    }
    for(int i=1;i<=m;++i){
        for(int j=0;j<26;++j){
            if(t[i-1]==j+'a') tpos[j][i] = i;
            else tpos[j][i] = tpos[j][i-1];
        }
    }
    set<string> res;
    function<void(int,int,int,string)> dfs = [&](int x,int y,int len,string tp){
        if(len==0){
            res.insert(tp);
            return;
        }
        if(x==0 || y==0){
            return;
        }
        for(int i=0;i<26;++i){
            int px = spos[i][x];
            int py = tpos[i][y];
            if(dp[px][py]==len) dfs(px-1,py-1,len-1,char(i+'a')+tp);
        }
        
    };
    string ans = "";
    dfs(n,m,dp[n][m],ans);
    for(auto &ss:res){
        cout<<ss<<'\n';
    }
}

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int _;
    cin>>_;
    while(_--){
        
        solve();
        
    }
    
    return 0;
}