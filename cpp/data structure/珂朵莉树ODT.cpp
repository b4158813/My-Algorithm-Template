#define IT set<odtnode>::iterator
struct odtnode
{
	int l,r;
	mutable ll v;
	odtnode(int L,int R=-1,ll V=0):l(L),r(R),v(V){}
	bool operator <(const odtnode& rhs)const{
		return l<rhs.l;
	}
};
set<odtnode> odt;

inline IT split(int pos){
	IT it=odt.lower_bound(odtnode(pos));
	if(it!=odt.end()&&it->l==pos) return it;
	it--;
	int l=it->l,r=it->r;
	ll v=it->v;
	odt.erase(it);
	odt.insert(odtnode(l,pos-1,v));
	return odt.insert(odtnode(pos,r,v)).first;
}

// Assign to same value
inline void assign(int l,int r,ll k){
	IT itr=split(r+1),itl=split(l);
	odt.erase(itl,itr);
	odt.insert(odtnode(l,r,k));
}


// [l,r] + k
inline void add(int l,int r,ll k){
	IT itr=split(r+1),itl=split(l);
	for(;itl!=itr;itl++) itl->v+=k;
}

// kth small
inline ll kths(int l,int r,int k){
	IT itr=split(r+1),itl=split(l);
	vector<pair<ll,int>> vec;
	vec.clear();
	for(;itl!=itr;itl++){
		vec.push_back(pair<ll,int>(itl->v,itl->r-itl->l+1));
	}
	sort(vec.begin(),vec.end());
	for(vector<pair<ll,int>>::iterator it=vec.begin();it!=vec.end();it++){
		k-=it->second;
		if(k<=0) return it->first;
	}
	return -1ll;
}

// x pow sum mod y
inline ll xpowsum(int l,int r,ll x,ll y){
	IT itr=split(r+1),itl=split(l);
	ll res=0;
	for(;itl!=itr;itl++){
		res=((res+(itl->r-itl->l+1)*qpow(itl->v,x,y)%y)%y+y)%y;
	}
	return res;
}