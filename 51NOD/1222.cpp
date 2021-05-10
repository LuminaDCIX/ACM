#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
const int SQRTN = 316300 + 5;
long long n;

struct LinearSieve {
  int p[SQRTN];
  int tot;
  int notP[SQRTN];
  int mu[SQRTN];

  void solve(int n) {
    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
      if (!notP[i]) {
        p[tot++] = i;
        mu[i] = -1;
      }
      for (int j = 0; j < tot; ++j) {
        int k = p[j] * i;
        if (k > n) {
          break;
        }
        notP[k] = 1;
        if (i % p[j] == 0) {
          mu[k] = 0;
          break;
        } else {
          mu[k] = mu[i] * -1;
        }
      }
    }
  }
} s;

long long calc(long long n) {
  // cerr << n << " ";
  long long lim = 0;
  long long f1 = 0;
  long long fi = 0;
  long long fj = 0;
  for (int i = 1; i; ++i) {
    if ((long long) i * i * i > n) {
      break;
    }
    ++lim;
    for (int j = i; j <= n; ++j) {
      long long k = n / i / j;
      if (k >= j) {
        f1 += k - j + 1;
      } else {
        break;
      }
      if (i == j && k != j) {
        fi += k - j;
      }
      if (i != j && k >= j) {
        ++fj;
      }
    }
  }
  long long ret = f1 * 6 - fi * 3 - fj * 3 - 5 * lim;
  // cerr << " " << f1 << " " << fi << " " << fj << " " << lim << " " << ret << endl;
  return ret;
}

long long solve(long long n) {
  int lim = sqrt(n);
  long long ret = 0;
  for (int d = 1; d <= lim; ++d) {
    long long sum = s.mu[d];
    sum *= calc(n / d / d);
    ret += sum;
  }

  return (ret + n) / 2;
}

int main() {

  s.solve(SQRTN - 1);
  scanf("%lld", &n);
  long long ans = -solve(n - 1);
  scanf("%lld", &n);
  ans += solve(n);
  printf("%lld\n", ans);
  return 0;
}
