#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

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

const int N = 1e5 + 5;

long long a[N];
long long sum[N];
int n;

long long rev(int i) {
  return a[n - 1] - a[i] - (sum[n - 1] - sum[i]);
}
int main() {
  
  ios::sync_with_stdio(false);
  cin.tie(0);
  int m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    if (i & 1) {
      sum[i] = sum[i - 1] + a[i] - a[i - 1];
    } else {
      sum[i] = sum[i - 1];
    }
  }
  ++n;
  a[n] = m;
  if (n & 1) {
    sum[n] = sum[n - 1] + a[n] - a[n - 1];
  } else {
    sum[n] = sum[n - 1];
  }
  ++n;
  long long ans = sum[n - 1];

  for (int i = 1; i < n - 1; ++i) {
    if (i & 1) {
      int k = a[i] - 1;
      if (k != a[i - 1]) {
        ans = max(ans, sum[i] - 1 + rev(i));
      }
      k = a[i] + 1;
      if (k != a[i + 1]) {
        ans = max(ans, sum[i] + rev(i) - 1);
      }
    } else {
      int k = a[i - 1];
      if (k != a[i - 1]) {
        ans = max(ans, sum[i] + 1 + rev(i));
      }
      k = a[i] + 1;
      if (k != a[i + 1]) {
        ans = max(ans, sum[i] + rev(i) + 1);
      }
    }
  }
  if (a[0] + 1 != a[1]) {
    ans = max(ans, sum[0] + rev(0) + 1);
  }
  if (a[n - 1] - 1 != a[n - 2]) {
    
    ans = max(ans, sum[n - 1] - 1 + rev(n - 1));
  }
  cout << ans << endl;
  return 0;
}
