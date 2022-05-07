
// KMP algorithm 下标从0开始
vector<int> KMP(string s){
	int len = s.size();
	vector<int> kmp(len);
	for(int j=0,i=1;i<len;++i){
		while(j && s[j]!=s[i]) j = kmp[j-1];
		if(s[j]==s[i]) j++;
		kmp[i] = j;
	}
}

// KMP algorithm 下标从1开始
vector<int> KMP(string s){
	s = "*" + s;
	int len = s.size();
	vector<int> kmp(len);
	for(int j=0,i=2;i<len;++i){
		while(j && s[j+1]!=s[i]) j = kmp[j];
		if(s[j+1]==s[i]) j++;
		kmp[i] = j;
	}
	return kmp;
}

// Z algorithm 下标从0开始
vector<int> Z_algorithm(string s){
	int len = s.size();
	vector<int> z(len);
	for(int l=0,i=1;i<len;++i){
		if(i<l+z[l]) z[i] = min(z[i-l], l+z[l]-i);
		while(i+z[i]<len && s[z[i]]==s[i+z[i]]) ++z[i];
		if(i+z[i]>l+z[l]) l = i;
	}
	z[0] = len;
	return z;
}