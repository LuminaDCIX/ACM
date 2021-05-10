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

const int N=100000+5;
const int P=500000+5;

int n;
int k;
int p;

int a[P];

int in[N];

int nxt[P];
int pos[N];

int main() {
  n=read();
  k=read();
  p=read();
  rep (i,0,p) {
    a[i]=read();
  } 
  fil(pos,-1); 
  rep (i,0,p) {
    if (pos[a[i]]!=-1) {
      nxt[pos[a[i]]]=i;
    }
    pos[a[i]]=i;
  }
  rep (i,1,n+1) {
    if (pos[i]!=-1) {
      nxt[pos[i]]=p;
    }
  }
  int cnt=0;
  int siz=0;
  priority_queue <pii> que;
  rep (i,0,p) {
    int x=a[i];
    if (!in[x]) {
      ++cnt;
      if (siz==k) {
        int l=que.top().se;
        while (true) {
          if (in[l]) {
            break;
          }
          que.pop();
          l=que.top().se;
        }
        in[l]=0;
      } else {
        ++siz;
      }
      in[x]=1;
    }
    que.push(mp(nxt[i],x));
  }
  printf("%d\n",cnt);
  return 0;
}
