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

const int S=25+4;
const int N=100000+5;

int n;
int m;
int p;

int a[N];
int b[N];

int s[S];

int nxt[N];

int c0[N];
int c1[N];

inline int sum(int x) {
  int ret=0;
  rep (i,1,x+1) {
    ret+=s[i];
  }
  return ret;
}

inline bool cmp(int x,int y) {
  return c0[x]==sum(y-1)&&c1[x]==sum(y);
}

int main() {
  n=read();
  m=read();
  p=read();
  rep (i,0,n) {
    a[i]=read();
  }
  rep (i,0,m) {
    b[i]=read();
  }
  rep (i,0,m) {
    c0[i]=sum(b[i]-1);
    c1[i]=sum(b[i]);
    ++s[b[i]];
  }
  fil(s,0);
  nxt[0]=-1;
  int j=-1;
  rep (i,1,m) {
    while (j!=-1&&!cmp(j+1,b[i])) {
      rep (k,i-j-1,i-nxt[j]-1) {
        --s[b[k]];
      }
      j=nxt[j];
    }
    if (cmp(j+1,b[i])) {
      ++j;
    }
    nxt[i]=j;
    ++s[b[i]];
  }
  vi ans;
  j=-1;
  fil(s,0);
  rep (i,0,n) {
    while (j!=-1&&!cmp(j+1,a[i])) {
      rep (k,i-j-1,i-nxt[j]-1) {
        --s[a[k]];
      }
      j=nxt[j];
    }
    if (cmp(j+1,a[i])) {
      ++j;
    }

    if (j==m-1) {
      ans.pb(i-m+2);
      rep (k,i-j,i-nxt[j]) {
        --s[a[k]];
      }
      j=nxt[j];
    }
    ++s[a[i]];
  }
  printf("%d\n",siz(ans));
  rep (i,0,siz(ans)) {
    printf("%d\n",ans[i]);
  }
  return 0;
}
