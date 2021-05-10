#pragma G++ optimize (3)

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

const int N=10000+5;//len
const int K=50000+5;  

int n;
int k;
int c;

priority_queue <pii> que;

vector <pii> up0[N];
vector <pii> up1[N];

int cnt[N];

int main() {
  k=read();
  n=read();
  c=read();

  rep (i,0,k) {
    int s=read();
    int e=read();
    int cnt=read();
    if (e>s) {
      up0[s].pb(mp(e,cnt));
    } else {
      up1[s].pb(mp(e,cnt));
    }
  }
  int ans=0;
  int all=0;
  rep (i,0,n+1) {
    ans+=cnt[i];
    all-=cnt[i];
    rep (j,0,siz(up0[i])) {
      int to=up0[i][j].fi;
      int s=up0[i][j].se;
      que.push(mp(to,s));
      cnt[to]+=s;
      all+=s;
    }
    while (all>c) {
      pii p=que.top();
      que.pop();
      if (p.se<=all-c) {
        cnt[p.fi]-=p.se;
        all-=p.se;
      } else {
        p.se-=all-c;
        cnt[p.fi]-=all-c;
        que.push(p);
        all=c;
      }
    }
  }
  
  while (!que.empty()) {
    que.pop();
  }
  fil(cnt,0);
  per (i,0,n+1) {
    ans+=cnt[i];
    all-=cnt[i];
    rep (j,0,siz(up1[i])) {
      int to=up1[i][j].fi;
      int s=up1[i][j].se;
      que.push(mp(-to,s));
      cnt[to]+=s;
      all+=s;
    }
    while (all>c) {
      pii p=que.top();
      que.pop();
      if (p.se<=all-c) {
        cnt[-p.fi]-=p.se;
        all-=p.se;
      } else {
        p.se-=all-c;
        cnt[-p.fi]-=all-c;
        que.push(p);
        all=c;
      }
    }
  }
  printf("%d\n",ans);

  return 0;
}
