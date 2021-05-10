// luogu-judger-enable-o2
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100000 + 5;

int n;
int m;

struct LinearSieve {
  int p[N];
  bool notPrime[N];
  int mindiv[N];
  int tot;

  int phi[N];

  void solve(int n) {
    phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
      if (!notPrime[i]) {
        p[tot++] = i;
        phi[i] = i - 1;
        mindiv[i] = i;
      }
      for (int j = 0; j < tot; ++j) {
        int k = p[j] * i;
        if (k > n) {
          break;
        }
        notPrime[k] = 1;
        mindiv[k] = p[j];
        if (mindiv[i] == p[j]) {
          phi[k] = phi[i] * p[j];
          break;
        } else {
          phi[k] = phi[i] * (p[j] - 1);
        }
      }
    }
  }
};

LinearSieve l;

int main() {
  scanf("%d %d", &n, &m);
  int lim = min(n, m);
  l.solve(lim);
  long long ans = 0;
  for (int i = 1; i <= lim; ++i) {
    ans += (long long) l.phi[i] * (n / i) * (m / i);
  }
  ans = 2 * ans - (long long) n * m;
  printf("%lld\n", ans);
  return 0;
}
