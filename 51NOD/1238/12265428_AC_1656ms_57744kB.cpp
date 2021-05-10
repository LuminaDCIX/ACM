#include <bits/stdc++.h>

using namespace std;

const int P = 1e9 + 7;
const int LIM = 4641600;
const int N = 4641600 + 5;

long long n;

inline int add(int a, int b) {
  a += b;
  return a >= P ? a - P : a;
}

inline int sub(int a, int b) {
  a -= b;
  return a < 0 ? a + P : a;
}

inline int mul(int a, int b)  {
  unsigned long long x = (long long) a * b;
  unsigned xh = (unsigned) (x >> 32), xl = (unsigned) x, d, m;
  asm(
    "divl %4; \n\t"
    : "=a" (d), "=d" (m)
    : "d" (xh), "a" (xl), "r" (P)
  );
  return m;
}

int sum(long long x) {
  int k = x % P;
  return mul(mul(k, k + 1), 500000004);
}

int sum2(long long x) {
  int k = x % P;
  return mul(mul(mul(k, k + 1), (2 * k + 1) % P), 166666668);
}

struct LinearSieve {
  int p[N];
  int tot;
  int f[N];
  int sum[N];
  int notP[N];

  void solve(int n) {
    f[1] = 1;
    for (int i = 2; i <= n; ++i) {
      if (!notP[i]) {
        p[tot++] = i;
        f[i] = mul(mul(i, i), i - 1);
      }
      for (int j = 0; j < tot; ++j) {
        int k = p[j] * i;
        if (k > n) {
          break;
        }
        notP[k] = 1;
        if (i % p[j] == 0) {
          f[k] = mul(f[i], mul(mul(p[j], p[j]), p[j]));
          break;
        } else {
          f[k] = mul(f[i], mul(mul(p[j], p[j]), p[j] - 1));
        } 
      }
    }

    for (int i = 1; i <= n; ++i) {
      sum[i] = add(sum[i - 1], f[i]);
    }
  }
} s;

int mem[N];

int calc(long long x) {
  if (x <= LIM) {
    return s.sum[x];
  } else if (mem[n / x]) {
    return mem[n / x];
  }
  int ans = mul(sum(x), sum(x));
  for (long long i = 2; i <= x; ++i) {
    long long vi = x / i;
    long long nxt = x / vi;
    ans = sub(ans, mul(sub(sum2(nxt), sum2(i - 1)), calc(vi)));
    i = nxt;
  }
  return mem[n / x] = ans;
}

int main() {
  s.solve(LIM);
  scanf("%lld", &n);
  int ans = 0;
  for (long long i = 1; i <= n; ++i) {
    long long vi = n / i;
    long long nxt = n / vi;
    ans = add(ans, mul(sub(sum(nxt), sum(i - 1)), calc(vi)));
    i = nxt;
  }
  printf("%d\n", ans);
  return 0;
}