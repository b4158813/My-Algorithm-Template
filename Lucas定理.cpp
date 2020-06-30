// Lucas定理求组合数，预处理阶乘fac[]
inline ll C(ll n,ll m,ll Mod){
	return (n<m)?0:fac[n]*qpow(fac[m],Mod-2,Mod)%Mod*qpow(fac[n-m],Mod-2,Mod)%Mod;
}
inline ll Lucas(ll n,ll m,ll Mod){
	return (!m)?1:Lucas(n/Mod,m/Mod,Mod)%Mod*C(n%Mod,m%Mod,Mod)%Mod;
}
