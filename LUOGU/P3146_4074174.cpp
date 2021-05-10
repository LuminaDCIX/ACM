#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define rep(i,a,n) for (int i=(a);i<(n);++i)

const int N=248+5;

int f[N][N];

int a[N], n;

int main() {
  scanf("%d",&n);
  rep (i,0,n) scanf("%d",&a[i]);
  memset(f,-1,sizeof(f));
  int ans=0;
  rep (i,0,N) f[i][a[i]]=i+1;
  rep (j,1,N) rep (i,0,n) rep (k,0,j) if (f[i][j-1]!=-1) {
    f[i][j]=f[f[i][j-1]][j-1];
    if (f[i][j]!=-1) ans=max(ans,j);
  }

  printf("%d\n",ans);
  return 0;
}
