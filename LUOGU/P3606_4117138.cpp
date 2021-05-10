#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;
#define rep(i,a,n) for (int i=(a);i<(n);++i)
typedef long long ll;

inline ll read() { ll x; scanf("%lld",&x); return x; }

const int N=1e5+5;

int n;
ll a[N],k;

inline ll calc(double x) { ll tot=0; rep (i,0,n) tot+=(ll)((sqrt(1+4*a[i]/x)-1)/2); return tot;}

inline double lbd() {
  double low=0,high=1e18,mid;
  rep (i,0,200) { mid=(low+high)/2; if (calc(mid)>=k) low=mid; else high=mid; }
  return low;
}

int main() {
  n=read(),k=read(); k-=n;
  rep (i,0,n) a[i]=read();
  double det=lbd();
  ll tot=0;
  double sum=0; 
  rep (i,0,n) { ll x=(ll)((sqrt(1+4*a[i]/det)-1)/2); sum+=1.0*a[i]/(x+1); tot+=x; }
  printf("%lld\n",(ll)round(sum-(k-tot)*det));
  return 0;
}
 
