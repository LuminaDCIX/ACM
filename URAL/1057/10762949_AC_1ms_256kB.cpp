#include <cstdio>

#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)

using namespace std;
typedef long long ll;

const int N=31+3;

int k, b;
int l, r;

int f[N][N];

int trs[N];
int cnt;

inline int solve(int x) {
  cnt=0;
  while (x) trs[cnt++]=x%b, x/=b;
  per (i,0,cnt) if (trs[i]!=0&&trs[i]!=1) {
    trs[i]=1;
    rep(j,0,i) trs[j]=1;
  }
  int tot=k;
  int ret=0;
  per (i,0,cnt) {
    if (trs[i]==1) ret+=f[i][tot], --tot;
    if (!tot) break;
  }
  if (!tot) ++ret;
  return ret;
}

int main() {
  scanf("%d%d%d%d",&l,&r,&k,&b);
  f[0][0]=1;
  rep (i,1,N) {
    f[i][0]=1;
    rep (j,0,i+1) f[i][j]=f[i-1][j]+f[i-1][j-1];
  }
  printf("%d\n",solve(r)-solve(l-1));
  return 0;
}
