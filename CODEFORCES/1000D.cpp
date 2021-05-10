#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

inline void add(int &a, int b) {
  a += b;
  if (a >= mod) {
    a -= mod;
  }
}
inline void sub(int &a, int b) {
  a -= b;
  if (a < 0) {
    a += mod;
  }
}
inline int mul(int a, int b) {
  return (long long) a * b % mod;
}
inline int modexp(int a, int x) {
  int res = 1;
  while (x) {
    if (x & 1) {
      res = mul(res, a);
    }
    a = mul(a, a);
    x >>= 1;
  }
  return res;
}

// struct edge {
//   int nxt;
//   int ver;
// };
// vector<edge> e;
// void add_edge(int u, int v) {
//   e.push_back((edge){head[u], v});
//   head[u] = (int) e.size() - 1;
// }

const int N = 1000 + 5;

int f[N];

int binom[N][N];
int a[N];

inline int c(int n, int m) {
  if (m > n) {
    return 0;
  }
  return binom[n][m];
}
      
int n;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  binom[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    binom[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      binom[i][j] = binom[i - 1][j];
      add(binom[i][j], binom[i - 1][j - 1]);
    }
  }

  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  f[0] = 1;
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    int cnt = 0;
    for (int j = i - 1; j >= 0; --j) {
      add(f[i], mul(f[j], cnt));
      if (a[j] > 0) {
        add(cnt, c(i - j - 1, a[j] - 1));
      }
    }
    add(ans, f[i]);
  }
  cout << ans << endl;
  return 0;
}
