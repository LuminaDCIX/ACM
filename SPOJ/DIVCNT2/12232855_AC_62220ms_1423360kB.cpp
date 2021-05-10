#include <bits/stdc++.h>

using namespace std;

const int N = 1e8 + 5;

int lim;

struct LinearSieve {
  long long fac2w[N];
  int p[N / 10];
  int tot;
  bool notPrime[N];
  char mu[N];
  int summu2[N];

  void solve(int n) {
    mu[1] = 1;
    fac2w[1] = 1;
    lim = n;
    for (int i = 2; i <= n; ++i) {
      if (!notPrime[i]) {
        p[tot++] = i;
        mu[i] = -1;
        fac2w[i] = 2;
      }
      for (int j = 0; j < tot; ++j) {
        int k = p[j] * i;
        if (k > n) {
          break;
        }
        notPrime[k] = 1;
        if (i %  p[j] == 0) {
          fac2w[k] = fac2w[i];
          mu[k] = 0;
          break;
        } else {
          fac2w[k] = fac2w[i] * 2;
          mu[k] = mu[i] * -1;
        }
      }
    }
    for (int i = 1; i <= n; ++i) {
      summu2[i] = summu2[i - 1] + mu[i] * mu[i];
      fac2w[i] += fac2w[i - 1];
    }
  }
};

LinearSieve s;

long long g[10005];
long long h[10005];

long long nn;

long long H(long long n) {
  if (n <= lim) {
    return s.summu2[n];
  }
  if (h[nn / n]) {
    return h[nn / n];
  }
  long long ans = 0;
  long long lim = sqrt(n);
  for (long long i = 1; i <= lim; ++i) {
    ans += s.mu[i] * (n / (i * i));
  }
  return h[nn / n] = ans;
}

long long G(long long n) {
  if (n <= lim) {
    return s.fac2w[n];
  }
  if (g[nn / n]) {
    return g[nn / n];
  }
  long long ans = 0;
  for (long long i = 1; i <= n; ++i) {
    long long vi = n / i;
    long long nxt = n / vi;
    ans += (H(nxt) - H(i - 1)) * vi;
    i = nxt;
  }
  return g[nn / n] = ans;
}

long long F(long long n) {
  long long ans = 0;
  for (long long i = 1; i <= n; ++i) {
    long long vi = n / i;
    long long nxt = n / vi;
    ans += (G(nxt) - G(i - 1)) * vi;
    i = nxt;
  }
  return ans;
}

long long q[100005];

int main() {
  int T;

  scanf("%d", &T);
  long long mx = 0;
  for (int i = 0; i < T; ++i) {
    scanf("%lld", &q[i]);
    mx = max(mx, q[i]);
  }
  s.solve(pow(mx, 2.0 / 3));

  for (int i = 0; i < T; ++i) {
    nn = q[i];
    memset(g, 0, sizeof(g));
    memset(h, 0, sizeof(h));
    printf("%lld\n", F(q[i]));
  }
  return 0;
}
