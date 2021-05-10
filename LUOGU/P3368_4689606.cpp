#include <cstdio>

using namespace std;

#define rep(i,a,n) for (int i=(a);i<(n);++i)

inline int read() {
  int x;
  scanf("%d",&x);
  return x;
}

const int N=500000+5;

int n;
int m;

int a[N];
int t[N];

inline void add(int x,int v) {
  ++x;
  while (x<=n) {
    t[x]+=v;
    x+=x&-x;
  }
}

inline int query(int x) {
  int sum=0;
  ++x;
  while (x) {
    sum+=t[x];
    x-=x&-x;
  }
  return sum;
}

int main() {
  n=read();
  m=read();
  rep (i,0,n) {
    a[i]=read();
  }
  rep (i,0,m) {
    int o=read();
    if (o==1) {
      int l=read()-1;
      int r=read()-1;
      int v=read();
      add(l,v);
      add(r+1,-v);
    } else {
      int x=read()-1;
      printf("%d\n",query(x)+a[x]);
    }
  }
  return 0;
}
