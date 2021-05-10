#include <cstdio>
#include <cstring>
#include <algorithm>

#define rep(i,a,n) for (int i=(a);i<(n);++i)

using namespace std;
typedef long long ll;


const ll mod=1e9+7;
const int N=20+3;

int n;
ll f[N], s;
ll inv[N];
ll ans;

inline ll C(ll n,ll m) {
  ll ret=1;
  rep (i,0,m) ret=ret*inv[m-i]%mod*((n-i)%mod)%mod;
  return ret;
}

void dfs(int x,ll sumf,int o) {
  if (x==n) {
    if (s+n-1-sumf<n-1) return;
    ans=(ans+o*C(s+n-1-sumf,n-1))%mod;
    return;
  }
  dfs(x+1,sumf,o);
  dfs(x+1,sumf+f[x]+1,o*-1);
}

int main()
{
  scanf("%d%lld",&n,&s);
  inv[1]=1;
  rep (i,2,n+1) inv[i]=-inv[mod%i]*(mod/i)%mod;
  rep (i,0,n) scanf("%lld",&f[i]);
  dfs(0,0,1);
  printf("%lld\n",ans<0?ans+mod:ans);
  return 0;
}
