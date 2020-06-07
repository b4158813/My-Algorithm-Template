#include<bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// #include <ext/pb_ds/priority_queue.hpp>
// using namespace __gnu_pbds;
using namespace std;
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define All(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define ios ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> VI;
typedef pair<int,int> PII;
// typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> pbds_set;
// typedef __gnu_pbds::priority_queue<ll,less<ll>,pairing_heap_tag> pbds_pq;
// typedef gp_hash_table<int,int> pbds_map;
const double PI=acos(-1.0);
const double eps=1e-6;
const long long mod=1e9+7;
const int inf=0x7fffffff;
const int maxn=100005;
inline ll qpow(ll x,ll y,ll Mod) {ll ans=1,base=x%Mod; while(y){if(y&1)ans=(ans*base)%Mod;base=(base*base)%Mod;y>>=1;} return ans;}
inline ll gcd(ll a,ll b){while(b){ll c=b;b=a%b;a=c;} return a;}
inline ll lcm(ll a,ll b){return a/gcd(a,b)*b;} 
// fast read
template<class T>
inline void read(T &x) {
	x=0;int f=0;char ch=getchar();
	while(ch<'0'||ch>'9'){f|=(ch=='-');ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	x=f?-x:x;
	return;
}
//fast write
template<class T>
inline void write(T x){
	if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}



int main(){
	#define LOCAL
	#ifdef LOCAL
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	clock_t _begin = clock();
	#endif

	


	#ifdef LOCAL
	double _used = 1000.0 * double(clock() - _begin) / CLOCKS_PER_SEC - 200.0;
	if (_used < 0) _used = 0.0;
	printf("------------------------------\n");
	printf("Time used: %.2lf ms.\n", _used);
	#endif
	return 0;
}