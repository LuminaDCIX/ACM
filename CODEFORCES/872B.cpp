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

const int N=1e5+5;

int n;
int k;

int a[N];
int b[N];

int pre[N];
int fix[N];

int main() {
  n=read();
  k=read();
  rep (i,0,n) {
    a[i]=read();
  }
  if (k==1) {
    int mn=1e9;
    rep (i,0,n) {
      mn=min(mn,a[i]);
    }
    printf("%d\n",mn);
    return 0;
  }
  if (k==2) {
    pre[0]=a[0];
    rep (i,1,n) {
      pre[i]=min(pre[i-1],a[i]);
    }
    fix[n-1]=a[n-1];
    per (i,0,n-1) {
      fix[i]=min(fix[i+1],a[i]);
    }
    int mx=-1e9;
    rep (i,1,n) {
      mx=max(max(pre[i-1],fix[i]),mx);
    }
    printf("%d\n",mx);
    return 0;
  } 
  int mx=-1e9;
  rep (i,0,n) {
    mx=max(mx,a[i]);
  }
  printf("%d\n",mx);

  return 0;
}
