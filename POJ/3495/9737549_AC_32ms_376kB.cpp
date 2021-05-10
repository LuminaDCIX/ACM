#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;
long long x, y, z;

long long calc(long long a, long long b, long long c, long long n)
{
  if (n == 0) {
    return 0ll;
  }
  return n * (b / c) + (a / c) * n * (n - 1) / 2 + calc(c, (a * n + b) % c, a % c, ((a % c) * n + b % c) / c);
}

int main()
{
  while (~scanf("%lld",&x)) {
    scanf("%lld%lld", &y, &z);
    long long n = (y - x) / z + 1;
    long long ret = 0;
    for (int i = 0; (1ll << i) <= (x + (n - 1) * z); ++i) {
      ret += (calc(z, x, 1ll << i, n) % 2) << i;
    }
    printf("%lld\n", ret);
  }
  return 0;
}
