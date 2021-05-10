#include <cstdio>
#include <cstring>
#include <algorithm>

#define rep(i,a,n) for (int i=(a);i<(n);++i)

using namespace std;

const int N=18+3;

int n,m;
int a[N];

struct node {
  int cnt;
  int left;

  bool operator < (const node &rhs) const {
    return cnt==rhs.cnt?left>rhs.left:cnt<rhs.cnt;
  }
} f[(1<<18)+5];

int main()
{
  scanf("%d",&n);
  scanf("%d",&m);
  rep (i,0,n) scanf("%d",&a[i]);
  memset(f,0x3f3f,sizeof(f));
  int lim=(1<<n)-1;
  f[0].cnt=1, f[0].left=m;
  rep (s,0,lim) rep (i,0,n) if (!(s&(1<<i))) {
    node x;
    if (f[s].left<a[i]) x.cnt=f[s].cnt+1, x.left=m-a[i];
    else x.cnt=f[s].cnt, x.left=f[s].left-a[i];
    if (x<f[s|(1<<i)]) f[s|(1<<i)]=x;
  }
  printf("%d\n",f[lim].cnt);
  return 0;
}
