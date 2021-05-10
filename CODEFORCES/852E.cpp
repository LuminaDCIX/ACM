#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
const int mod = (int) 1e9 + 7;

int n;

void add(int &a, int b) {
  a += b;
  if (a >= mod) {
    a -= mod;
  }
}

void sub(int &a, int b) {
  a -= b;
  if (a < 0) {
    a += mod;
  }
}

int mul(int a, int b) {
  return (long long) a * b % mod;
}

int modexp(int a, int x) {
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

vector<int> g[N];
vector<int> son[N];

vector<int> pre[N][2];
vector<int> suf[N][2];

int f[N][2][2];

void dfs(int v, int fa) {
  for (auto u : g[v]) {
    if (u == fa) {
      continue;
    }
    dfs(u, v);
    son[v].push_back(u);
  }
  if ((int)son[v].size() == 0) {
    f[v][0][0] = 1;
    f[v][1][1] = 1;
  } else {
    int n = son[v].size();
    pre[v][0].resize(n);
    pre[v][1].resize(n);
    suf[v][0].resize(n);
    suf[v][1].resize(n);
    for (int i = 0; i < n; ++i) {
      int u = son[v][i];
      for (int j = 0; j < 2; ++j) {
        pre[v][j][i] = (f[u][j][0] + f[u][j][1]) % mod;
        suf[v][j][i] = (f[u][j][0] + f[u][j][1]) % mod;
      }
    }
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < 2; ++j) {
        pre[v][j][i] = mul(pre[v][j][i], pre[v][j][i - 1]);
      }
    }
    for (int i = n - 2; i >= 0; --i) {
      for (int j = 0; j < 2; ++j) {
        suf[v][j][i] = mul(suf[v][j][i], suf[v][j][i + 1]);
      }
    }
    f[v][0][0] = pre[v][0][n - 1];
    f[v][0][1] = pre[v][1][n - 1];
    f[v][1][0] = pre[v][1][n - 1];
    f[v][1][1] = pre[v][0][n - 1];
  }
}

inline int prod(int v, int i, int c) {
  if ((int)son[v].size() == 1) {
    return 1;
  }
  if (i == 0) {
    return suf[v][c][i + 1];
  }
  if (i == (int)son[v].size() - 1) {
    return pre[v][c][i - 1];
  }
  return mul(pre[v][c][i - 1], suf[v][c][i + 1]);
}

int f2[N][2][2];

void dfs2(int v, int fa) {
  // cerr << v << endl;
  // for (int i = 0; i < 2; ++i) {
  //   for (int j = 0; j < 2; ++j) {
  //     cerr<< f2[v][i][j] << " ";
  //   }
  //   cerr << endl;
  // }
  for (int i = 0; i < (int)son[v].size(); ++i) {
    int u = son[v][i];
    add(f2[u][0][0], mul(f2[v][0][0], prod(v, i, 0)));
    add(f2[u][0][0], mul(f2[v][0][1], prod(v, i, 1)));
    add(f2[u][0][1], mul(f2[v][1][0], prod(v, i, 1)));
    add(f2[u][0][1], mul(f2[v][1][1], prod(v, i, 0)));
    add(f2[u][1][0], mul(f2[v][1][0], prod(v, i, 1)));
    add(f2[u][1][0], mul(f2[v][1][1], prod(v, i, 0)));
    add(f2[u][1][1], mul(f2[v][1][0], prod(v, i, 0)));
    add(f2[u][1][1], mul(f2[v][1][1], prod(v, i, 1)));
  }
  for (auto u : son[v]) {
    dfs2(u, v);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  cin >> n;
  static int deg[N];
  for (int i = 0, u, v; i < n - 1; ++i) {
    cin >> v >> u;
    --v;
    --u;
    g[u].push_back(v);
    g[v].push_back(u);
    ++deg[u];
    ++deg[v];
  }

  if (n == 1) {
    cout << 1 << endl;
    return 0;
  }
  if (n == 2) {
    cout << 4 << endl;
    return 0;
  }
  
  int root = 0;
  while (deg[root] == 1) {
    ++root;
  }
  dfs(root, -1);
  
  f2[root][0][0] = 1;
  f2[root][0][1] = 1;
  f2[root][1][0] = 1;
  f2[root][1][1] = 1;
  dfs2(root, -1);

  int ans = 0;

  for (int i = 0; i < n; ++i) {
    if ((int)son[i].size() > 0) {
      add(ans, mul(f2[i][0][0], f[i][0][0]));
      add(ans, mul(f2[i][0][1], f[i][0][1]));
    } else {
      add(ans, f2[i][0][0]);
      add(ans, f2[i][0][1]);
    }
  }

  cout << ans << endl;
  return 0;
}
