#include <cmath>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

long long gcd(long long a, long long b)
{
  return !b ? a : gcd(b, a % b);
}

void extgcd(long long a, long long b, long long &x, long long &y)
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

int main()
{
  int k;
  while (~scanf("%d", &k)) {
    k--;
    long long a1, a2;
    long long r1, r2;
    scanf("%lld%lld", &a1, &r1);
    bool flag = 0;
    while (k--) {
      scanf("%lld%lld", &a2, &r2);
      if (flag) {
        continue;
      }
      long long d = gcd(a1, a2);
      if ((r2 - r1) % d) {
        flag = 1;
        continue;
      }
      long long t = (a1 * a2) / d;
      long long K = inv(a1 / d, a2 / d) * ((r2 - r1) / d) % (a2 / d);
      r1 = (r1 + a1 * K % t + t) % t;
      a1 = t; 
    }
    printf("%lld\n", flag ? -1ll : r1);
  }
  return 0;
}