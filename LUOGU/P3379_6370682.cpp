// luogu-judger-enable-o2
#include <bits/stdc++.h>

inline int read() {
  int x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x;
}

using namespace std;


const int N = 500000 + 5;
const int LOGN = 21;
const int Q = 500000 + 5;

vector <int> ver[N];


int n, m;

struct tarjan_lca {
  int ans[Q];
  int col[N], pre[N];
  int fa[N];
  vector < pair <int, int> > *q;

  int find(int x) {
    return pre[x] == x ? x : pre[x] = find(pre[x]);
  }

  void dfs(int u) {
    col[u] = 1;
    for (int o = 0; o < (int) ver[u].size(); ++o) {
      int v = ver[u][o];
      if (v == fa[u]) {
        continue;
      }
      fa[v] = u;
      dfs(v);
      pre[v] = u;
    }
    col[u] = 2;
    for (int i = 0; i < (int) q[u].size(); ++i) {
      int v = q[u][i].first;
      if (col[v] == 2) {
        ans[q[u][i].second] = find(v);
      }
    }
  }

  void solve(int s, vector <pair <int, int> > *v) {
    q = v;
    for (int i = 1; i <= n; ++i) {
      pre[i] = i;
    }
    memset(col, 0, sizeof(col));
    fa[s] = 0;
    dfs(s);
  }
};

tarjan_lca lca;

vector < pair <int, int> > q[N];

int main() {
  n = read();
  m = read();
  int s = read();
  for (int i = 0; i < n - 1; ++i) {
    int u = read();
    int v = read();
    ver[u].push_back(v);
    ver[v].push_back(u);
  }
  for (int i = 1; i <= m; ++i) {
    int x = read();
    int y = read();
    q[x].push_back(make_pair(y, i));
    q[y].push_back(make_pair(x, i));
  }
  lca.solve(s, q);
  for (int i = 1; i <= m; ++i) {
    printf("%d\n", lca.ans[i]);
  }
  return 0;
}
