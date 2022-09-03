// ST表 O(nlogn)预处理，O(1)查询静态区间最值
vector<vector<int>> ST(n+2, vector<int>(23, 0));
auto init_st = [&]() -> void{ //st init
	for(int i=1;i<=n;i++) ST[i][0]=a[i];
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i+(1<<(j-1))-1<=n;i++){
			ST[i][j]=max(ST[i][j-1],ST[i+(1<<(j-1))][j-1]);
		}
	}
};
init_st();
auto query = [&](int l,int r) -> int{ //查询l,r最值
	int len=log2(r-l+1);
	return max(ST[l][len],ST[r-(1<<len)+1][len]);
};