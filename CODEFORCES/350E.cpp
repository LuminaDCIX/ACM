#include <bits/stdc++.h>

#define st first
#define nd second
#define make_pair com
#define sz(x) ((int)x.size())
// #define for(x) for (auto x =
// #define in(a, b) (a); i < (b); ++
#define for_(i, a, n) for (auto i = (a); i < (n); ++i)
#define for__(i, a, n) for (auto i = (a); i <= (n); ++i)
#define __for(i, a, n) for (auto i = (n); i >= (a); --i)
#define _for(i, a, n) for (auto i = (n) - 1; i >= (a); --i)

using namespace std;

const int mod = (int) 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef double dbl;
typedef pair<int, int> mti;

inline void add(int &a, int b) { a + b >= mod ? a += b - mod : a += b; }
inline void sub(int &a, int b) { a - b < 0 ? a -= b - mod : a -= b; }
inline int mul(int a, int b) { return (long long) a * b % mod; }
inline int modexp(int a, int x) {
  int res = 1;
  for (; x; x >>= 1, a = mul(a, a)) {
    if (x & 1) res = mul(res, a);
  }
  return res;
}

template <typename T>
vector<T>& operator << (vector<T> &v, T x) { return v.push_back(x), v; }
//head;

const int N = 300 + 5;

int n;
int m;
int k;

int a[N];
int fail[N];
int g[N][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> k;
  if (n - k == 0) {
    cout << -1 << endl;
    return 0;
  }
  for_ (i, 0, k) {
    cin >> a[i];
    --a[i];
    fail[a[i]] = 1;
  }
  vi v;
  for_ (i, 0, n) if (fail[i]) {
    v << i;
    break;
  }
  for_ (i, 0, n) if (!fail[i]) {
    v << i;
    break;
  }
  for_ (i, 0, n) if (fail[i] && i != v[0]) {
    v << i;
    break;
  }
  for_ (i, 0, n) if (!fail[i] && i != v[0] && i != v[1] && i != v[2]) {
    v << i;
  }
  int k = sz(v);
  for_ (i, 0, n) if (fail[i] && i != v[0] && i != v[1] && i != v[2]) {
    v << i;
  }
  for_ (i, 0, sz(v) - 1) {
    g[v[i]][v[i + 1]] = 1;
    g[v[i + 1]][v[i]] = 1;
  }
  m -= n - 1;
  int s = v[0];
  int t = v[2];
  for_ (i, 0, n) {
    if (!m) break;
    if (v[i] == s || v[i] == t) continue;
    for_ (j, i + 1, n) {
      int a = v[i];
      int b = v[j];
      if (b == s || b == t) continue;
      if (g[a][b]) continue;
      g[a][b] = g[b][a] = 1;
      --m;
      if (!m) break;
    }
    if (!m) break;
  }

  if (m) {
    for_ (i, 3, k) {
      int u = v[i];
      if (!g[u][s]) {
        g[u][s] = g[s][u] = 1;
        --m;
      }
      if (!m) break;
      if (!g[u][t]) {
        g[u][t] = g[t][u] = 1;
        --m;
      }
      if (!m) break;
    }
  }
  if (m) {
    for_ (i, k, sz(v)) {
      int u = v[i];
      if (!g[u][t]) {
        g[u][t] = g[t][u] = 1;
        --m;
      }
      if (!m) break;
    }
  }
  if (m) {
    puts("-1");
    return 0;
  }

  for_ (i, 0, n) {
    for_ (j, i, n) {
      if (g[i][j]) cout << i + 1 << " " << j + 1 << endl;
    }
  }
  
  return 0;
}
