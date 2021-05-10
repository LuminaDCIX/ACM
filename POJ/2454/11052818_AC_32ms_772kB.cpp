#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cmath>
#include <vector>
#include <cstdio>
#include <bitset>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

#define y0 y0z
#define y1 y1z
#define yn ynz
#define j0 j0z
#define j1 j1z
#define jn jnz
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define siz(x) ((int)(x).size())
#define fil(a,b) memset((a),(b),sizeof(a))
#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)
#define fore(i,e) for (int i=e;~i;i=e[i].nxt)
#ifdef MiracleEEEE
#define debug(...) fprintf(stderr,__VA_ARGS__)
#else 
#define debug(...) 
#endif
using namespace std;

typedef long long ll;
typedef vector <int> vi;
typedef pair <int,int> pii;

char xB[1<<15],*xS=xB,*xT=xB;  
#define getc() (xS==xT&&(xT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xT)?0:*xS++)  
inline ll read() {
  ll x=0;
  int f=1;
  char ch=getc();
  for (;ch<'0'||ch>'9';f=(ch=='-')?-1:1,ch=getc());
  for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getc());
  return f*x;
}

inline void timer() {
#ifdef MiracleEEEE
  clock_t s_=clock();
  if (s_/1000<=5) {
  fprintf(stderr,"time=%ldmicrosecond\n",s_);
} else {
  fprintf(stderr,"time=%ldmillisecond\n",s_/1000);
}
#endif
}

inline void file(string name) {
  freopen((name+".in").c_str(),"r",stdin);
  freopen((name+".out").c_str(),"w",stdout);
}

//head

const int N=200+5;

int a[N];

int n;

int p0[N];
int p1[N];

int main() {
  n=read();
  vector <pii> v;
  rep (i,0,3*n) {
    a[i]=read();
    v.pb(mp(a[i],i));
  }
  sort(all(v));
  rep (i,0,n) {
    printf("%d\n",v[i].se+1);
  }
  int s0=0;
  int s1=0;
  srand(20010609ll);
  rep (i,n,n*2) {
    s0+=v[i].fi;
    p0[i-n]=v[i].se;
  }
  rep (i,n*2,n*3) {
    s1+=v[i].fi;
    p1[i-2*n]=v[i].se;
  }
  while (s0<=500*n||s1<=500*n) {
    int k1=rand()%n;
    int k2=rand()%n;
    s0+=-a[p0[k1]]+a[p1[k2]];
    s1+=-a[p1[k2]]+a[p0[k1]];
    swap(p0[k1],p1[k2]);
  }

  rep (i,0,n) {
    printf("%d\n",p0[i]+1);
  }
  rep (i,0,n) {
    printf("%d\n",p1[i]+1);
  }

  return 0;
}
