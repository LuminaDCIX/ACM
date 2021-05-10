#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 1e6 + 5;

long long l;
long long r;

bool not_prime[MAX];
int p[100105];
int tot;

inline void init() {
  int lim = (int) sqrt(r);
  for (int i = 2; i <= lim; ++i) {
    if (!not_prime[i]) {
      p[tot++] = i;
    }
    for (int j = 0; j < tot; ++j) {
      int k = p[j] * i;
      if (k > lim) {
        break;
      }
      not_prime[k] = 1;
      if (i % p[j] == 0) {
        break;
      }
    }
  }
}

long long num[MAX];
long long phi[MAX];

const long long mod = 666623333;

int main() {
  scanf("%lld%lld", &l, &r);
  init();
  for (long long i = l; i <= r; ++i) {
    num[i - l] = i;
    phi[i - l] = i;
  }
  for (int i = 0; i < tot; ++i) {
    int pi = p[i];
    long long cur = l / pi;
    for (; ; ++cur) {
      long long to = cur * pi;
      if (to > r) {
        break;
      } else if (to >= l) {
        int s = to - l;
        long long &nums = num[s];
        while (nums % pi == 0) {
          nums /= pi;
        }
        phi[s] -= phi[s] / pi;
      }
    }
  }
  int n = r - l + 1;
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    ans += (i + l) % mod;
    if (ans > mod) {
      ans -= mod;
    }
    if (num[i] != 1) {
      phi[i] -= phi[i] / num[i];
    }
    ans -= phi[i] % mod;
    if (ans < 0) {
      ans += mod;
    }
  }
  if (ans < 0) {
    ans += mod;
  }
  printf("%lld\n", ans);

  return 0;
}
