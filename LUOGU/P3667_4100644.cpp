#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
#define rep(i,a,n) for (int i=(a);i<(n);++i)

inline int read() { int x; scanf("%d",&x); return x; }

const int N=500+5;
const int MAX=N<<1;

int n,m;

char str[MAX][N];

const int mod=1e9+7;
const int base=13131;
const int lnk=7393913;

int hs[MAX][N],v[lnk],fac[N];

inline int get(int k,int l,int r) { return (l==0)?(hs[k][r]):((hs[k][r]-1ll*hs[k][l-1]*fac[r-l+1]%mod)%mod+mod)%mod; }

inline bool check(int l,int r) {
  rep (i,0,n) v[get(i,l,r)%lnk]=1;
bool flg=1; rep (i,n,n*2) if (v[get(i,l,r)%lnk]==1) flg=0;
  rep (i,0,n) v[get(i,l,r)%lnk]=0;
  return flg;
}

inline int lbd(int x) {
  int l=x,r=m-1,ret=1e9,mid;
  while (l<=r) {
    mid=(l+r)>>1;
    if (check(x,mid)) r=mid-1,ret=mid; else l=mid+1;
  }
  return ret;
}

int main() {
  n=read(),m=read();
  rep (i,0,n*2) scanf("%s",str[i]);
  rep (i,0,n*2) { hs[i][0]=str[i][0]-'A'; rep (j,1,m) hs[i][j]=(1ll*hs[i][j-1]*base+str[i][j]-'A')%mod; }
  fac[0]=1; rep (i,1,m+1) fac[i]=1ll*fac[i-1]*base%mod;

  int ans=1e9; rep (i,0,m) ans=min(ans,lbd(i)-i+1);
  printf("%d\n",ans);
  return 0;
}
