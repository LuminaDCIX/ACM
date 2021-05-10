#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)
#define lowbit(x) (x&-x)

const int N=12+3;
const int MAX=(1<<12)+5;
const int inf=0x3f3f3f3f;

int read() {
  int f=1,x=0;char ch=getchar();
  while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
  while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
  return f*x;
}

int n,m;

int g[N][N];
int h[MAX][MAX];
int f[N][MAX];

int bit[N];
int inv[MAX];

int main() {
  n=read(),m=read();
  memset(g,inf,sizeof(g));
  rep (i,0,m) {
    int u=read()-1,v=read()-1;
    g[u][v]=g[v][u]=min(g[u][v],read());
  }
  rep (i,0,n) bit[i]=1<<i,inv[1<<i]=i;
  int lim=1<<n;
  rep (i,0,lim) rep (j,0,lim) h[i][j]=inf;
  rep (i,0,n) {
    int k=1<<i;
    rep (j,1,lim) h[j][k]=min(h[j-lowbit(j)][k],g[i][inv[lowbit(j)]]);
  }
  rep (i,1,lim) rep (j,1,lim) h[i][j]=min(h[i][j],h[i][j-lowbit(j)]+h[i][lowbit(j)]);
  memset(f,inf,sizeof(f));
  rep (i,0,n) f[0][1<<i]=0;
  rep (i,1,n) rep (j,0,lim) for (int k=(j-1)&j;k;k=(k-1)&j) {
    if (h[k][j^k]==inf) continue;
    f[i][j]=min(f[i][j],f[i-1][k]+i*h[k][j^k]);
  }
  int ans=inf;
  rep (i,0,n) ans=min(ans,f[i][lim-1]);
  printf("%d\n",ans);
  return 0;
}
