#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll p[65];
ll x;
inline void ins(ll x){
	for(int i=50;i>=0;i--){
		if((1ll<<i)&x){
			if(p[i]) x^=p[i];
			else{
				p[i]=x;
				break;
			}
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&x),ins(x);
	ll ans=0;
	for(int i=50;i>=0;i--)
		if((ans^p[i])>ans) ans^=p[i];
	printf("%lld\n",ans);
	return 0;
}