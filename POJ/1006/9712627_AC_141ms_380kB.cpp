#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>

using namespace std;

long long a[3] = {23, 28, 33};
long long r[3];
long long c[3];
long long M;
int kase;
inline void extgcd(long long a, long long b, long long &x, long long &y)
{
  if (!b) {
    x = 1;
    y = 0;
    return;
  }
  extgcd(b, a % b, y, x);
  y -= (a / b) * x;
}

inline long long inv(long long a, long long p)
{
  long long x, y;
  extgcd(a, p, x, y);
  return (x % p + p) % p; 
}

inline long long crt()
{
  long long ret = 0;
  for (int i = 0; i < 3; ++i) { 
    ret = (ret + c[i] * r[i])% M;
  }
  return ret;
}

int main()
{
  M = 28 * 33 * 23;
  for (int i = 0; i < 3; ++i) {
    c[i] = inv(M / a[i], a[i]) * M / a[i];
  }
  while (true) {
    long long x1, x2, x3, k;
    scanf("%lld%lld%lld%lld", &x1, &x2, &x3, &k);
    if (x1 + x2 + x3 + k == -4) {
      return 0;
    }
    r[0] = x1 % 23;
    r[1] = x2 % 28;
    r[2] = x3 % 33;
    long long ans = crt();
    if (x1 == 0 && x2 == 0 && x3 == 0) {
      ans = M;
    }
    while(ans <= k) {  
      ans += M;
    }
    printf("Case %d: the next triple peak occurs in %lld days.\n", ++kase, ans - k);
  }
  return 0;
}
