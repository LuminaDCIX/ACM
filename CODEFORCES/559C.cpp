#include<bits/stdc++.h>

#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=a;--i)
#define modp(a,b) (((a)+(b))%mod+mod)%mod;
#define modm(a,b) ((a)*(b))%mod
#define C(x,y) ((fac[(y)]*inv[(x)]%mod)*inv[(y)-(x)]%mod)
typedef long long ll;

using namespace std;

const ll mod=(ll)1e9+7;
const int maxn=2000;
const int maxn2=1e5;
ll f[maxn+5];
int n,m,c;
ll fac[2*maxn2+5];
ll inv[2*maxn2+5];
struct point {int x,y;} p[maxn+5];

bool cmp(point a,point b) {return a.x==b.x?a.y<b.y:a.x<b.x;}
ll modexp(ll a,ll x,ll p) {
  ll ret=1;
  for (ret;x;x>>=1,a=modm(a,a)) if (x&1) ret=modm(ret,a);
  return ret;
}

int main() {
  scanf("%d%d%d",&n,&m,&c);
  rep(i,0,c) scanf("%d%d",&p[i].x,&p[i].y);
  p[c].x=n,p[c++].y=m;
  sort(p,p+c,cmp);
  fac[0]=1;
  rep(i,1,2*max(n,m)+1) fac[i]=modm(fac[i-1],i);
  inv[max(n,m)*2]=modexp(fac[max(n,m)*2],mod-2,mod);
  per(i,0,max(n,m)*2) inv[i]=modm(inv[i+1],(i+1));
  rep(i,0,c) f[i]=C(p[i].x-1,p[i].x+p[i].y-2);
  rep(i,1,c) rep(j,0,i) if (p[j].x<=p[i].x&&p[j].y<=p[i].y) f[i]=modp(f[i],-modm(C(p[i].x-p[j].x,p[i].x+p[i].y-p[j].x-p[j].y),f[j]));
  printf("%lld\n",f[c-1]);     
  return 0;
}

