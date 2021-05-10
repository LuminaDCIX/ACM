// luogu-judger-enable-o2
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 1e5 + 5;

struct lucas {
  int inv[N];
  int fac[N];
  int P;
  inline int modexp(int a, int x) {
    int ret = 1;
    while (x) {
      if (x & 1) {
        ret = (long long) ret * a % P;
      }
      a = (long long) a * a % P;
      x >>= 1;
    }
    return ret;
  }

  int calc(int n, int m) {
    if (m > n) {
      return 0;
    }
    if (n < P) {
      return (long long) fac[n] * inv[m] % P * inv[n - m] % P;
    }
    return (long long) calc(n % P, m % P) * calc(n / P, m / P) % P;
  }

  void init(int _P) {
    P = _P;
    fac[0] = 1;
    for (int i = 1; i < P; ++i) {
      fac[i] = (long long) fac[i - 1] * i % P;
    }
    inv[P - 1] = modexp(fac[P - 1], P - 2);
    for (int i = P - 2; i >= 0; --i) {
      inv[i] = (long long) inv[i + 1] * (i + 1) % P;
    }
  }
} s;

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m, p;
    scanf("%d %d %d", &n, &m, &p);
    s.init(p);
    printf("%d\n", s.calc(n + m, m));
  }
  return 0;
}
