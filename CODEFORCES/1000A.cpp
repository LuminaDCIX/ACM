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

string a[105];
string b[105];

int cnta[10];
int cntb[10];

int mp[200];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;

  mp['X'] = 0;
  mp['S'] = 1;
  mp['L'] = 2;
  mp['M'] = 3;
  
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  for (int i = 0; i < n; ++i) {
    cin >> b[i];
  }
  int ans = 0;
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      cnta[j] = 0;
      cntb[j] = 0;
    }
    for (int j = 0; j < n; ++j) {
      if (a[j].length() > i) {
        cnta[mp[a[j][i]]]++;
      }
    }
    for (int j = 0; j < n; ++j) {
      if (b[j].length() > i) {
        cntb[mp[b[j][i]]]++;
      }
    }
    for (int j = 0; j < 5; ++j) {
      ans += abs(cnta[j] - cntb[j]);
    }
  }
  cout << ans / 2 << endl;
  return 0;
}
