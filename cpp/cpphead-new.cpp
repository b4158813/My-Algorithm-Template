#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int,int>;
using tiii = tuple<int,int,int>;

namespace std {
    string to_string(const string& s){return '"'+s+'"';}
    string to_string(const char* s){return to_string((string)s);}
    string to_string(bool b){return (b?"true":"false");}
    template <typename A> string to_string(const A& v) {bool flag{true};string s{"["};for(const auto& x:v){s+=","[flag]+to_string(x);flag=(flag?0:0);}s.append("]");return s;}
    template <typename T, typename U> string to_string(const pair<T, U>& pa){return "("+to_string(pa.first)+","+to_string(pa.second)+")";}
    template <class... T> string to_string(const tuple<T...>& tu){constexpr int N = tuple_size_v<tuple<T...>>;return [&]<size_t... I>(std::index_sequence<I...>){string s;return "("+(...,(s.append(to_string(get<I>(tu))+","[I==N-1])))+")";}(std::make_index_sequence<N>());}
    template <class... T> void debug_out(const T&... args){(..., (cerr << to_string(args) << ' '));endl(cerr);}
    #define debug(...) std::cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
}


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