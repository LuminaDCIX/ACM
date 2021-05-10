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

const int N=500000+5;
const int mod=1e9+7;

int n;
int q;

int hs[N];
int fac[N];

int mindiv[N];

vi p;
bool not_prime[N];

inline void pre() {
  mindiv[1]=1;
  rep (i,2,n) {
    if (!not_prime[i]) {
      p.pb(i);
      mindiv[i]=i;
    }
    rep (j,0,siz(p)) {
      int k=p[j]*i;
      if (k>n) {
        break;
      }
      not_prime[k]=1;
      mindiv[k]=p[j];
      if (mindiv[i]==p[j]) {
        break;
      }
    }
  }
}

char str[N];

inline int get(int l,int r) {
  int k=hs[r]-(ll)hs[l-1]*fac[r-l+1]%mod;
  if (k<0) {
    k+=mod;
  }
  return k;
}

inline bool judge(int l,int r,int k) {
  return get(l+k,r)==get(l,r-k);
}

int main() {
  n=read();
  char ch=getc();
  while (ch<'a'||ch>'z') {
    ch=getc();
  }
  str[0]=ch;
  rep (i,1,n) {
    str[i]=getc();
  }
  pre();
  hs[0]=str[0]-'a'+1;
  rep (i,1,n) {
    hs[i]=((ll)hs[i-1]*13131%mod+str[i]-'a'+1)%mod;
  }
  fac[0]=1;
  rep (i,1,n+1) {
    fac[i]=(ll)fac[i-1]*13131%mod;
  }
  q=read();

  rep (i,0,q) {
    int l=read()-1;
    int r=read()-1;
    int len=r-l+1;
    int x=len;
    while (x!=1) {
      int now=mindiv[x];
      if (judge(l,r,len/now)) {
        len/=now;
      }
      x/=now;
    }
    printf("%d\n",len);
  }
  return 0;
}
