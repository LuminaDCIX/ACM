#include <bits/stdc++.h>

using namespace std;

inline int read()  {
  int f = 1;
  int x = 0;
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

const int N = 1e5 + 5;
const int MAX = 262144 + 5;
const int P = 998244353;

inline int add(int a, int b) {
  return (a += b) >= P ? a - P : a;
}
inline int sub(int a, int b) {
  return (a -= b) < 0 ? a + P : a;
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
    x >>= 1;
    a = mul(a, a);
  }
  return ret;
}


struct ntt {
  int f1[MAX];
  int f2[MAX];
  int g[MAX];
  int rev[MAX];
  int lim, bit;

  inline int revbit(int x) {
    int ret = 0;
    for (int i = 0; i < bit; ++i) {
      ret <<= 1;
      ret |= x & 1;
      x >>= 1;
    }
    return ret;
  }

  void dft(int *f, int o) {
    for (int i = 0; i < lim; ++i) {
      if (i < rev[i]) {
        swap(f[i], f[rev[i]]);
      }
    }
    for (int i = 0; i < bit; ++i) {
      int len = 1 << i;
      for (int j = 0; j < lim; j += len * 2) {
        int wn = 0;
        for (int k = j; k < j + len; ++k) {
          int t = mul(f[k + len], g[wn]);
          f[k + len] = sub(f[k], t);
          f[k] = add(f[k], t);
          wn += o * (1 << (bit - i - 1));
          if (wn < 0) {
            wn += lim;
          }
        }
      }
    }
  }

  vector <int> solve(vector <int> x, vector <int> y) {
    int n = x.size();
    int m = y.size();
    bit = 0;
    while ((1 << bit) < n + m - 1) {
      ++bit;
    }
    lim = 1 << bit;
    for (int i = 0; i < lim; ++i) {
      f1[i] = 0;
      f2[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
      f1[i] = x[i];
    }
    for (int i = 0; i < m; ++i) {
      f2[i] = y[i];
    }
    for (int i = 0; i < lim; ++i) {
      rev[i] = revbit(i);
    }
    g[0] = 1;
    g[1] = modexp(3, (P - 1) / lim);
    for (int i = 2; i < lim; ++i) {
      g[i] = mul(g[i - 1], g[1]);
    }
    dft(f1, 1);
    dft(f2, 1);
    for (int i = 0; i < lim; ++i) {
      f1[i] = mul(f1[i], f2[i]);
    }
    dft(f1, -1);
    int inv = modexp(lim, P - 2);
    vector <int> ans;
    for (int i = 0; i < lim; ++i) {
      f1[i] = mul(f1[i], inv);
      ans.push_back(f1[i]);
    }
    return ans;
  }
            
} nttt;

int main() {
  int n = read() + 1;
  int m = read() + 1;
  vector <int> x, y;
  for (int i = 0; i < n; ++i) {
    int k = read();
    x.push_back(k);
  }
  for (int i = 0; i < m; ++i) {
    int k = read();
    y.push_back(k);
  }
  x = nttt.solve(x, y);
  for (int i = 0; i < n + m - 1; ++i) {
    printf("%d ", x[i]);
  }
  puts("");
  return 0;
}
