#include <bits/stdc++.h>

using namespace std;

const int N = 5e5+ 5;
const int P = 1e9 + 7;
const int bas = 3e4;
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

inline int add(int a, int b) {
  a += b;
  if (a >= P) {
    a -= P;
  } 
  return a;
}

inline int sub(int a, int b) {
  a -= b;
  if (a < 0) {
    return a += P;
  }
  return a;
}

inline int mul(int a, int b) {

  unsigned long long x = (long long) a * b;
  unsigned xh = (unsigned) (x >> 32), xl = (unsigned) x, d, m;
  asm(
    "divl %4; \n\t"
    : "=a" (d), "=d" (m)
    : "d" (xh), "a" (xl), "r" (P)
  );
  return m;
}

struct LinearSieve {
  int p[N];
  int tot;
  int notP[N];
  int phi[N];
  int sumPhi[N];
  int sumP[N];
  int len;

  void init(int n) {
    phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
      if (!notP[i]) {
        sumPhi[len] = add(sumPhi[len - 1], i - 1);
        ++len;
        p[tot++] = i;
        phi[i] = i - 1;
      }
      for (int j = 0; j < tot; ++j) {
        int k = p[j] * i;
        if (k > n) {
          break;
        }
        notP[k] = 1;
        if (i % p[j] == 0) {
          phi[k] = mul(phi[i], p[j]);
          break;
        } else {
          phi[k] = mul(phi[i], p[j] - 1);
        }
      }
    }
    sumP[0] = p[0];
    for (int i = 1; i < tot; ++i) {
      sumP[i] = add(sumP[i - 1], p[i]);
    }
  }
} s;

int l0[N];
int l1[N];
int g0[N];
int g1[N];
int f0[N];
int f1[N];
int h0[N];
int h1[N];
int cntP[N];

void calcF(int sqrtN, int sqrtP, long long n) {
  for (int i = 1; i < sqrtN; ++i) {
    f0[i] = 1;
    f1[i] = 1;
  }
  for (int i = sqrtP - 1; i >= 0; --i) {

    for (int j = 1; j < sqrtN && i < l1[j]; ++j) {
      long long x = n / j / s.p[i];
      int fac = s.p[i];
      int lst = 1;
      for (int c = 1; x; ++c) {
        if (x < sqrtN) {
          f1[j] = add(f1[j], mul(sub(fac, lst), f0[x]));
          int k = max(l0[x], i + 1);
          if (cntP[x] > k) {
            f1[j] = add(f1[j], mul(sub(fac, lst), sub(s.sumPhi[cntP[x] - 1], s.sumPhi[k - 1])));
          }
        } else {
          f1[j] = add(f1[j], mul(sub(fac, lst), f1[n / x])) % P;
          int k = max(l1[n / x], i + 1);
          if (sqrtP > k) {
            f1[j] = add(f1[j], mul(sub(fac, lst), sub(s.sumPhi[sqrtP - 1], s.sumPhi[k - 1])));
          }
        }
        x /= s.p[i];
        lst = fac;
        fac = mul(fac, s.p[i]);
      } 
    }

    for (int j = sqrtN - 1; j >= 1 && i < l0[j]; --j) {
      long long x = j / s.p[i];
      int fac = s.p[i];
      int lst = 1;
      for (int c = 1; x; ++c) {
        f0[j] = add(f0[j], mul(sub(fac, lst), f0[x]));
        int k = max(l0[x], i + 1);
        if (cntP[x] > k) {
          f0[j] = add(f0[j], mul(sub(fac, lst), sub(s.sumPhi[cntP[x] - 1], s.sumPhi[k - 1])));
        }
        x /= s.p[i];
        lst = fac;
        fac = mul(fac, s.p[i]);
      }
    }
  }
  for (int i = 1; i < sqrtN; ++i) {
    f0[i] = add(f0[i], sub(s.sumPhi[cntP[i] - 1], s.sumPhi[l0[i] - 1]));
    f1[i] = add(f1[i], sub(s.sumPhi[sqrtP - 1], s.sumPhi[l1[i] - 1]));
  }
}

void calcG(int sqrtN, int sqrtP, long long n) {
  for (int i = 1; i < sqrtN; ++i) {
    g0[i] = mul(mul(i, (i + 1)), 500000004);
    g1[i] = mul(mul((n / i) % P, n / i % P + 1), 500000004);
  }
  for (int i = 0; i < sqrtP; ++i) {
    for (int j = 1; j < sqrtN && i < l1[j]; ++j) {
      long long x = n / j / s.p[i];
      if (x < sqrtN) {
        g1[j] = sub(g1[j], mul(s.p[i], g0[x]));
        int k = min(i, cntP[x]);
        if (k > l0[x]) {
          g1[j] = add(g1[j], mul(s.p[i], sub(s.sumP[k - 1], s.sumP[l0[x] - 1])));
        }
      } else {
        g1[j] = sub(g1[j], mul(s.p[i], g1[n / x]));
        if (i > l1[n / x]) {
          g1[j] = add(g1[j], mul(s.p[i], sub(s.sumP[i - 1], s.sumP[l1[n / x] - 1])));
        }
      }
    }
    for (int j = sqrtN - 1; j >= 1 && i < l0[j]; --j) {
      int x = j / s.p[i];
      int k = min(i, cntP[x]);
      g0[j] = sub(g0[j], mul(s.p[i], g0[x]));
      if (k > l0[x]) {
        g0[j] = add(g0[j], mul(s.p[i], sub(s.sumP[k - 1], s.sumP[l0[x] - 1])));
      }
    }
  }
  for (int i = 1; i < sqrtN; ++i) {
    g0[i] = sub(sub(g0[i], sub(s.sumP[cntP[i] - 1], s.sumP[l0[i] - 1])), 1);
    g1[i] = sub(sub(g1[i], sub(s.sumP[sqrtP - 1], s.sumP[l1[i] - 1])), 1);
  }
} 

void calcH(int sqrtN, int sqrtP, long long n) {
  for (int i = 1; i < sqrtN; ++i) {
    h0[i] = i;
    h1[i] = n / i % P;
  }
  for (int i = 0; i < sqrtP; ++i) {
    for (int j = 1; j < sqrtN && i < l1[j]; ++j) {
      long long x = n / j / s.p[i];
      if (x < sqrtN) {
        h1[j] = add(sub(h1[j], h0[x]), max(0, min(i, cntP[x]) - l0[x]));
      } else {
        h1[j] = add(sub(h1[j], h1[n / x]), max(0, i - l1[n / x]));
      }
    }
    for (int j = sqrtN - 1; j >= 1 && i < l0[j]; --j) {
      int x = j / s.p[i];
      h0[j] = add(sub(h0[j], h0[x]), max(0, min(i, cntP[x]) - l0[x]));
    }
  }
  for (int i = 1; i < sqrtN; ++i) {
    h0[i] = sub(add(sub(h0[i], cntP[i]), l0[i]), 1);
    h1[i] = sub(add(sub(h1[i], sqrtP), l1[i]), 1);
  }
} 

int solve(long long n) {
  int sqrtN = 0;
  int sqrtP = 0;
  while ((long long) sqrtN * sqrtN <= n) {
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
  calcH(sqrtN, sqrtP, n);
  long long ans = f1[1];
  for (int i = 1; i < sqrtN; ++i) {
    ans = add(ans, mul(s.phi[i], sub(g1[i], h1[i])));
  }
  return ans;
}

int main() {
  s.init(3e5);
  long long n = read();
  printf("%d\n", solve(n));
  return 0;
}