#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;
const long long P = 1e9 + 7;

int n;
int m;

long long fac[N];
long long inv[N];

long long modexp(long long a, long long x, long long P) {
  long long ret = 1;
  while (x) {
    if (x & 1) {
      ret = ret * a % P;
    }
    a = a * a % P;
    x >>= 1;
  }
  return ret;
}

long long C(int n, int m) {
  return fac[n] * inv[n - m] % P * inv[m] % P;
}

long long S(int n, int m) {
  long long ret = 0;
  int o = 1;
  for (int i = 0; i <= m; ++i) {
    ret = (ret + o * C(m, i) * modexp(m - i, n, P) % P) % P;
    o = -o;
  }
  ret = ret * inv[m] % P;
  return (ret + P) % P;
}

int main() {
  scanf("%d %d", &n, &m);
  if (m > n) {
    printf("%d\n", 0);
    return 0;
  }
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * i % P;
  }
  inv[n] = modexp(fac[n], P - 2, P);
  for (int i = n - 1; i >= 0; --i) {
    inv[i] = inv[i + 1] * (i + 1) % P;
  }
  long long ans = C(n, m) * S(n - 2, n - m) % P * fac[n - m] % P;
  printf("%lld\n", ans);
  return 0;
}