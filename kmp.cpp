/*
	KMP(文本串，模式串)
*/
int kmp[maxn];
inline void KMP(char *a,char *b){
	int lena=strlen(a+1),lenb=strlen(b+1);
	for(int i=2,j=0;i<=lenb;i++){
		while(j&&b[j+1]!=b[i]) j=kmp[j];
		if(b[j+1]==b[i]) j++;
		kmp[i]=j;
	}
	for(int i=1,j=0;i<=lena;i++){
		while(j&&b[j+1]!=a[i]) j=kmp[j];
		if(b[j+1]==a[i]) j++;
		if(j==lenb){
			printf("%d\n",i-j+1);
			j=kmp[j];
		}
	}
}

int main(){
	scanf("%s",a+1);
	scanf("%s",b+1);
	KMP(a,b);
	return 0;
}