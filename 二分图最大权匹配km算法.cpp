#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<vector>
#define LL long long
using namespace std;
const int INF=0x3f3f3f3f;
const int mxn=411;

int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

void write(LL x){
    if(x>9)write(x/10);
    putchar(x%10+'0');
    return;
}

inline int mini(int a,int b){return a<b?a:b;}
inline int maxi(int a,int b){return a>b?a:b;}
int nL,nR,bl,br,m;
int visL[mxn],visR[mxn];
int exL[mxn],exR[mxn];
int link[mxn],pre[mxn],lx[mxn];
int slack[mxn];
int mp[mxn][mxn];
//
LL ans=0;
int a[mxn];
int dtime=0;
int q[mxn<<1],hd,tl;
void Aug(int rt){
    if(!rt)return;
    link[rt]=pre[rt];
    Aug(lx[pre[rt]]);
    lx[pre[rt]]=rt;
    return;
}
void BFS(int S){
    int i,j,tmp;++dtime;
    memset(slack,0x3f,sizeof slack);
    hd=tl=1;q[tl]=S;
    while(1){
        while(hd<=tl){
            int u=q[hd];++hd;
            visL[u]=dtime;
            for(int i=1;i<=nR;i++){
                if(visR[i]^dtime){
                    tmp=exL[u]+exR[i]-mp[u][i];
                    if(!tmp){
                        visR[i]=dtime;pre[i]=u;
                        if(!link[i]){
                            Aug(i);
                            return;
                        }
                        q[++tl]=link[i];
                        //
                    }
                    else if(tmp<slack[i])slack[i]=tmp,pre[i]=u;
                }
            }
        }
        tmp=INF;
        for(i=1;i<=nR;i++)if(visR[i]^dtime)tmp=mini(tmp,slack[i]);
        for(i=1;i<=nL;i++){
            if(visL[i]==dtime)exL[i]-=tmp;
            if(visR[i]==dtime)exR[i]+=tmp;
            else slack[i]-=tmp;
        }
        for(i=1;i<=nR;i++){
            if(visR[i]^dtime && !slack[i]){
                visR[i]=dtime;
                if(!link[i]){
//                    link[i]=pre[i];
                    Aug(i);
                    return;
                }
                q[++tl]=link[i];
            }
        }
    }
    return;
}
void KM(){
    for(int i=1;i<=nL;i++){
        exL[i]=0;
        for(int j=1;j<=nR;j++)
            exL[i]=max(exL[i],mp[i][j]);
    }
    for(int i=1;i<=nL;i++) BFS(i);
    ans=0;
    nL=bl;nR=br;
    
    for(int i=1;i<=nR;i++){
        if(mp[link[i]][i]){
            a[link[i]]=i;
            ans+=mp[link[i]][i];
        }
    }
    printf("%lld\n",ans);
    for(int i=1;i<=nL;i++){
        write(a[i]);
        putchar(' ');
    }
    printf("\n");
    return;
}
int main(){
    int i,j;
    nL=read();
    nR=read();
    bl=nL;br=nR;
    nL=max(nL,nR);
    nR=nL;
    m=read();
    int u,v,w;
    for(i=1;i<=m;i++){
        u=read();v=read();w=read();
        mp[u][v]=w;
    }
    KM();
    return 0;
}
