// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

inline int read() {
  int f = 1;
  int x = 0;
  char ch = getchar();
  while (!isdigit(ch)) {
    f = (ch == '-') ? -1 : 1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return f * x;
}

const int N = 1e5 + 5;
const int M = 262144 + 5;
const int P = 998244353;

inline int add(int a, int b) {
  return a + b >= P ? a + b - P : a + b;
}
inline int sub(int a, int b) {
  return a - b < 0 ? a - b + P : a - b;
}
inline int mul(int a, int b) {
  return (long long) a * b % P;
}
inline int modexp(int a, int x) {
  int ret = 1;
  while (x) {
    if (x & 1) {
      ret = mul(ret, a);
    }
    a = mul(a, a);
    x >>= 1;
  }
  return ret;
}

int n;
vector <int> a;

struct poly {
  int g[M];
  int rbit[M];

  inline int invbit(int x, int m) {
    int ret = 0;
    for (int i = 0; i < m; ++i) {
      ret <<= 1;
      ret |= x & 1;
      x >>= 1;
    }
    return ret;
  }


  inline void init(int m, int lim) {
    g[0] = 1;
    g[1] = modexp(3, (P - 1) / lim);
    for (int i = 2; i < lim; ++i) {
      g[i] = mul(g[i - 1], g[1]);
    }
    for (int i = 0; i < lim; ++i) {
      rbit[i] = invbit(i, m);
    }
  }

  inline void dft(vector <int> &p, int m, int lim, int mod, int o) {
    p.resize(mod);
    p.resize(lim, 0);
    for (int i = 0; i < lim; ++i) {
      if (rbit[i] > i) {
        swap(p[rbit[i]], p[i]);
      }
    }
    for (int i = 0; i < m; ++i) {
      int len = 1 << i;
      for (int j = 0; j < lim; j += len * 2) {
        int gn = 0;
        for (int k = j; k < j + len; ++k) {
          int t = mul(p[k + len], g[gn]);
          p[k + len] = sub(p[k], t);
          p[k] = add(p[k], t);
          gn += o * (1 << (m - i - 1));
          if (gn < 0) {
            gn += lim;
          }
        }
      }
    }
    if (o == -1) {
      int inv = modexp(lim, P - 2);
      for (int i = 0; i < lim; ++i) {
        p[i] = mul(p[i], inv);
      }
    }
  }

  vector <int> inverse(vector <int>  &a, int n) {
    if (n == 1) {
      return vector <int> (1, modexp(a[0], P - 2));
    }
    vector <int> p = inverse(a, (n + 1) / 2);
    vector <int> q = a;
    int m = 0;
    int lim = 0;
    while ((1 << m) < n * 2) {
      ++m;
    }
    lim = 1 << m;
    init(m, lim);
    dft(p, m, lim, n, 1);
    dft(q, m, lim, n, 1);
    vector <int> ret;
    for (int i = 0; i < lim; ++i) {
      ret.push_back(mul(sub(2, mul(p[i], q[i])), p[i]));
    }
    dft(ret, m, lim, lim, -1);
    ret.resize(n);
    return ret;
  }
}
p;

int main() {
  n = read();
  for (int i = 1; i <= n; ++i) {
    int x = read();
    a.push_back(x);
  }
  vector <int> inv = p.inverse(a, n);
  for (int i = 0; i < (int) inv.size(); ++i) {
    printf("%d ", inv[i]);
  }
  puts("");
  return 0;
}