#include <bits/stdc++.h>

using namespace std;

class dsu {
public:
  vector<int> p;
  int n;

  dsu(int _n) : n(_n) {
    p.resize(n);
    iota(p.begin(), p.end(), 0);
  }

  inline int get(int x) { return (x == p[x] ? x : (p[x] = get(p[x]))); }

  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x != y) {
      p[x] = y;
      return true;
    }
    return false;
  }
};

const int N = 2e5 + 5;

set<int> nodes;
set<int> g[N];
int tot;

void dfs(int u, dsu &d) {
  auto it = nodes.begin();
  vector<int> nxt;
  while (it != nodes.end()) {
    int v = *it;
    if (g[u].find(v) == g[u].end()) {
      d.unite(u, v);
      ++tot;
      nxt.push_back(v);
    }
    ++it;
  }
  for (int i = 0; i < (int) nxt.size(); ++i) {
    nodes.erase(nxt[i]);
  }
  for (int i = 0; i < (int) nxt.size(); ++i) {
    dfs(nxt[i], d);
  }
}

int main() {
  ios::sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    nodes.insert(i);
  }
  vector<tuple<int, int, int> > edges;
  int x = 0;
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    --u;
    --v;
    g[u].insert(v);
    g[v].insert(u);
    x ^= w;
    edges.push_back(make_tuple(w, u, v));
  }
  dsu d(n);
  while (!nodes.empty()) {
    int u = *nodes.begin();
    nodes.erase(u);
    dfs(u, d);
  }
  int ans = 0;
  sort(edges.begin(), edges.end());
  dsu ori(n);
  int mn = numeric_limits<int>::max();
  for (int i = 0; i < (int) edges.size(); ++i) {
    int u = get<1>(edges[i]);
    int v = get<2>(edges[i]);
    int w = get<0>(edges[i]);
    if (d.get(u) != d.get(v)) {
      d.unite(u, v);
      ori.unite(u, v);
      ans += w;
    } else if (ori.get(u) != ori.get(v)) {
      mn = min(mn, w);
    }
  }
  if (n * ((long long) n - 1) / 2 - m > tot) {
    cout << ans << endl;
  } else {
    if (x < mn) {
      cout << ans + x << endl;
    } else {
      cout << ans + mn << endl;
    }
  }
  return 0;
}
