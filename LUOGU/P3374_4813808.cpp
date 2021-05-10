#include <cstdio>
#include <cstring>

using namespace std;

#define rep(i,a,n) for (int i=(a);i<(n);++i)

const int N=500000+5;

inline int read() {
  int x;scanf("%d",&x);return x;
}

int n,m;

int t[N];

inline int add(int u,int x) {
  for (++u;u<=n;u+=u&-u) t[u]+=x;
}

inline int sum(int u) {
  int sum=0;
  for (++u;u;u-=u&-u) sum+=t[u];
  return sum;
}

int main() {
  n=read(),m=read();
  rep (i,0,n) add(i,read());
  rep (i,0,m) {
    int o=read(),x=read(),y=read();
    o==1?add(--x,y):printf("%d\n",sum(--y)-sum((--x)-1));
  }
  return 0;
}
