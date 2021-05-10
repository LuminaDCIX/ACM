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


const int N=100+5;
const int MAX=12000+5;

int n;
int t;

int c[N];
int v[N];

int f[MAX];

int g[MAX];

deque <pii> que;

int main() {
  n=read();
  t=read();
  rep (i,0,n) {
    v[i]=read();
  }
  rep (i,0,n) {
    c[i]=read();
  }
  fil(f,0x3f);
  f[0]=0;
  rep (i,0,n) {
    rep (j,v[i],MAX) {
      f[j]=min(f[j],f[j-v[i]]+1);
    }
  }
  fil(g,0x3f);
  g[0]=0;
  rep (i,0,n) {
    rep (r,0,v[i]) {
      que.clear();
      rep (p,0,MAX/v[i]+1) {
        int k=v[i]*p+r;
        if (k>MAX) {
          break;
        }
        while (!que.empty()&&p-que.front().se>c[i]) {
          que.pop_front();
        }
        int lst=g[k];
        if (!que.empty()) {
          g[k]=min(g[k],que.front().fi+p);
        }
        while (!que.empty()&&que.back().fi>lst-p) {
          que.pop_back();
        }
        que.push_back(mp(lst-p,p));
      }
    }
  }
  int ans=1e9;
  rep (i,t,MAX) {
    ans=min(ans,g[i]+f[i-t]);
  }
  if (ans==1e9) {
    puts("-1");
    return 0;
  }
  printf("%d\n",ans);
  return 0;
}
