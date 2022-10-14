#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int,int>;
using tiii = tuple<int,int,int>;

string to_string(const string &s){return '"' + s + '"';}
string to_string(const char* s){return to_string((string) s);}
string to_string(bool b){return (b ? "true" : "false");}
template <typename A, typename B> string to_string(const pair<A, B> &p){return "(" + to_string(p.first) + "," + to_string(p.second) + ")";}
template <typename A, typename B, typename C> string to_string(const tuple<A, B, C> &p){return "(" + to_string(get<0>(p)) + "," + to_string(get<1>(p)) + "," + to_string(get<2>(p)) + ")";}
template <typename A, typename B, typename C, typename D> string to_string(const tuple<A, B, C, D> &p){return "(" + to_string(get<0>(p)) + "," + to_string(get<1>(p)) + "," + to_string(get<2>(p)) + "," + to_string(get<3>(p)) + ")";}
template <typename A> string to_string(const A &v){bool first = true;string res = "[";for (const auto &x : v) {if (!first) res += ",";first = false;res += to_string(x);}res += "]";return res;}
void debug_out(){std::cerr << endl;}
template<class T, class... Ts> void debug_out(const T &x, const Ts &...xs){std::cerr << to_string(x) << ' '; debug_out(xs...);}


void solve(){
    
    
    
}

int main(){
    
    cin.tie(nullptr)->sync_with_stdio(false);
    
    int _ = 1;
    cin>>_;
    while(_--){
        
        solve();
        
    }
    
    return 0;
}