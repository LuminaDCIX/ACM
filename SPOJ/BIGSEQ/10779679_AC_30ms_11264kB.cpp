#include <ctime>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)

using namespace std;
typedef long long ll;

const int N=100+5;
const int base=100000000;

int n,m;

struct bigint {
  ll s[25];
  int len;

  void init(int x) {
    memset(s,0,sizeof(s)); len=1,s[0]=x;
  }

  void print() {
    printf("%lld",s[len-1]);
    per (i,0,len-1) printf("%08lld",s[i]); puts("");
  }
};

bigint operator + (bigint a,bigint b) {
  bigint c; c.init(0);
  c.len=max(a.len,b.len)+2;
  rep (i,0,c.len) c.s[i]+=a.s[i]+b.s[i],c.s[i+1]+=c.s[i]/base,c.s[i]%=base;
  while (c.len>1&&c.s[c.len-1]==0) --c.len; return c;
}

bigint operator - (bigint a,bigint b) {
  bigint c; c.init(0);
  c.len=max(a.len,b.len)+2;
  rep (i,0,c.len) {
    c.s[i]+=a.s[i]-b.s[i];
    if (c.s[i]<0) c.s[i]+=base,c.s[i+1]-=1;
  }
  while (c.len>1&&c.s[c.len-1]==0) --c.len; return c;
}

bigint operator * (bigint a,bigint b) {
  bigint c; c.init(0);
  rep (i,0,a.len) rep (j,0,b.len) c.s[i+j]+=a.s[i]*b.s[j],c.s[i+j+1]+=c.s[i+j]/base,c.s[i+j]%=base;
  c.len=a.len+b.len+2;
  while (c.len>1&&c.s[c.len-1]==0) --c.len; return c;
}

bool operator <= (bigint a,bigint b) {
  if (a.len!=b.len) return a.len<b.len;
  per (i,0,a.len) if (a.s[i]!=b.s[i]) return a.s[i]<b.s[i];
  return 1;
}

bool operator < (bigint a,bigint b) {
  if (a.len!=b.len) return a.len<b.len;
  per (i,0,a.len) if (a.s[i]!=b.s[i]) return a.s[i]<b.s[i];
  return 0;
}

bigint operator / (bigint a,int b) {
  bigint c; c.init(0);
  ll last=0;
  if (b==2) { 
    per (i,0,a.len) c.s[i]=(a.s[i]+last)>>1,last=((a.s[i]+last)&1)*base;
    c.len=a.len;
    while (c.len>1&&c.s[c.len-1]==0) --c.len; return c;
  }
  per (i,0,a.len) c.s[i]=(a.s[i]+last)/b,last=(last+a.s[i])%b*base;
  c.len=a.len;
  while (c.len>1&&c.s[c.len-1]==0) --c.len; return c;
}

bigint f[N<<1][N<<1];
bigint fac[N<<1];
bigint num[N<<1];

int bin[N<<1];

bigint count(bigint p) {
  int tot=0;
  while (!(p.len==1&&p.s[0]==0)) bin[tot++]=p.s[0]&1,p=p/2;
  bigint ret,one,exi; ret.init(0),one.init(1),exi.init(0);
  per (i,0,tot) {
    if (bin[i]==1) ret=ret+exi*fac[i]+num[i]+one,exi=exi+one;
  }
  return ret;
}

bigint findnxt(bigint p) {
  int cnt=0;
  // puts(""),p.print();
  bigint exi,one,ret; exi.init(0),one.init(1),ret.init(0);
  per (i,0,n+1) {
    bigint t=num[i]+(fac[i])*exi;
    if (t<=p) p=p-t,exi=exi+one,ret=ret+fac[i];
  }
  return ret;
}

inline bool judge(bigint s) {
  int cnt=0; bigint p; p.init(1);
  bigint one; one.init(1);
  while (true) {
    ++cnt;
    p=findnxt(count(p-one)+s);
    if (fac[n]<=p) {return true;}
    if (cnt>=m) {return false;} 
  }
  return false;
}


int main() {
  scanf("%d%d",&n,&m);
  rep (i,0,N+6) {
    f[i][0].init(1); rep (j,1,i+1) f[i][j]=f[i-1][j-1]+f[i-1][j];
  }
  fac[0].init(1); bigint x; x.init(2);
  rep (i,1,N+6) fac[i]=fac[i-1]*x;
  num[0].init(0);
  rep (i,1,N+6) {rep (j,1,i+1) x.init(j),num[i]=num[i]+x*f[i][j];}
  bigint l; l.init(0);
  rep (i,1,n+1) {
    x.init(i),l=l+x*f[n][i];
  }

  l=l/m;
  x.init(100);
  bigint r=l+x;
  bigint one,ans; one.init(1);ans.init(0);
  while (l<=r) {
    bigint mid=(l+r)/2;
    if (judge(mid)) ans=mid,r=mid-one;
    else l=mid+one;
  }

  ans.print();
  return 0;
}
