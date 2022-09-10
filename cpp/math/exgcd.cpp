/*
	扩展欧几里得算法(exgcd)
	用途：
		- 用于求解二元一次不定方程
			a * x + b * y = 1 中的 x, y
		- 用于求解乘法逆元
			a * x ≡ 1 (mod b) <==> a * x + b * y = 1
			解得x即为a的逆元（前提是gcd(a,b)=1)
*/

ll exgcd(ll a,ll b,ll &x,ll &y){//返回gcd
	if(b == 0) { x = 1; y = 0; return a;}
	ll res = exgcd(b, a % b, x,y);
	ll tx = x; x = y; y = tx - a / b *y ;
	return res;
}