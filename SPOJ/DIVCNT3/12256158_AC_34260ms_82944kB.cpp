#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

long long read() {
  int f = 1;
  long long x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    f = (ch == '-') ? -1 : 1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return f * x;
}

struct LinearSieve {
  int p[N];
  int tot;
  int notP[N];
  long long d3[N];
  long long nd3[N];

  void init(int n) {
    d3[1] = 1;
    for (int i = 2; i <= n; ++i) {
      if (!notP[i]) {
        p[tot++] = i;
        d3[i] = 4;
        nd3[i] = 1;
      }
      for (int j = 0; j < tot; ++j) {
        int k = p[j] * i;
        if (k > n) {
          break;
        }
        notP[k] = 1;
        if (i % p[j] == 0) {
          nd3[k] = nd3[i];
          d3[k] = d3[i] + 3 * nd3[i];
          break;
        } else {
          d3[k] = d3[i] * 4;
          nd3[k] = d3[i];
        }
      }
    }
  }
} s;

int l0[N];
int l1[N];
long long g0[N];
long long g1[N];
long long f0[N];
long long f1[N];
int cntP[N];

void calcF(int sqrtN, int sqrtP, long long n) {
  for (int i = 1; i < sqrtN; ++i) {
    f0[i] = 1;
    f1[i] = 1;
  }
  for (int i = sqrtP - 1; i >= 0; --i) {

    for (int j = 1; j < sqrtN && i < l1[j]; ++j) {
      long long x = n / j / s.p[i];
      for (int c = 1; x; ++c) {
        if (x < sqrtN) {
          f1[j] += (3 * c + 1) * (f0[x] + 4 * max(0, cntP[x] - max(l0[x], i + 1)));
        } else {
          f1[j] += (3 * c + 1) * (f1[n / x] + 4 * max(0, sqrtP - max(l1[n / x], i + 1)));
        }
        x /= s.p[i];
      } 
    }

    for (int j = sqrtN - 1; j >= 1 && i < l0[j]; --j) {
      long long x = j / s.p[i];
      for (int c = 1; x; ++c) {
        f0[j] += (3 * c + 1) * (f0[x] + 4 * max(0, cntP[x] - max(l0[x], i + 1)));
        x /= s.p[i];
      }
    }
  }
  for (int i = 1; i < sqrtN; ++i) {
    f0[i] += 4 * max(0, cntP[i] - l0[i]);
    f1[i] += 4 * (sqrtP - l1[i]);
  }
}

void calcG(int sqrtN, int sqrtP, long long n) {
  for (int i = 1; i < sqrtN; ++i) {
    g0[i] = i;
    g1[i] = n / i;
  }
  for (int i = 0; i < sqrtP; ++i) {
    for (int j = 1; j < sqrtN && i < l1[j]; ++j) {
      long long x = n / j / s.p[i];
      if (x < sqrtN) {
        g1[j] -= g0[x] - max(0, min(i, cntP[x]) - l0[x]);
      } else {
        g1[j] -= g1[n / x] - max(0, i - l1[n / x]);
      }
    }
    for (int j = sqrtN - 1; j >= 1 && i < l0[j]; --j) {
      int x = j / s.p[i];
      g0[j] -= g0[x] - max(0, min(i, cntP[x]) - l0[x]);
    }
  }
  for (int i = 1; i < sqrtN; ++i) {
    g0[i] -= cntP[i] - l0[i] + 1;
    g1[i] -= sqrtP - l1[i] + 1;
  }
  for (int i = 1; i < sqrtN; ++i) {
    g0[i] *= 4;
    g1[i] *= 4;
  }
} 

long long solve(long long n) {
  long long sqrtN = 0;
  long long sqrtP = 0;
  while (sqrtN * sqrtN <= n) {
    ++sqrtN;
  }
  while ((long long) s.p[sqrtP] * s.p[sqrtP] <= n) {
    ++sqrtP;
  }
  for (int i = 1; i < sqrtN; ++i) {
    cntP[i] = cntP[i - 1];
    while (s.p[cntP[i]] <= i) {
      ++cntP[i];
    }
  }
  l0[0] = 0;
  for (int i = 1; i < sqrtN; ++i) {
    l0[i] = l0[i - 1];
    while (s.p[l0[i]] * s.p[l0[i]] <= i) {
      ++l0[i];
    }
  } 
  l1[sqrtN] = 0;
  for (int i = sqrtN - 1; i >= 1; --i) {
    long long x = n / i;
    l1[i] = l1[i + 1];
    while ((long long) s.p[l1[i]] * s.p[l1[i]] <= x) {
      ++l1[i];
    }
  }
  calcF(sqrtN, sqrtP, n);
  calcG(sqrtN, sqrtP, n);
  long long ans = f1[1];
  for (int i = 1; i < sqrtN; ++i) {
    ans += s.d3[i] * g1[i];
  }
  return ans;
}

int main() {
  s.init(1e6);
  int T = read();
  while (T--) {
    long long n = read();
    printf("%lld\n", solve(n));
  }
  return 0;
}