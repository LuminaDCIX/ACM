#include <bits/stdc++.h>

using namespace std;

template <typename T>
class graph {
 public:
  struct edge {
    int from;
    int to;
    T cost;
  };

  vector<edge> edges;
  vector<vector<int> > g;
  int n;

  function<bool(int)> ignore;

  graph(int _n) : n(_n) {
    g.resize(n);
    ignore = nullptr;
  }

  virtual int add(int from, int to, T cost) = 0;

  virtual void set_ignore_edge_rule(const function<bool(int)> &f) {
    ignore = f;
  }

  virtual void reset_ignore_edge_rule() { ignore = nullptr; }
};

template <typename T>
class digraph : public graph<T> {
 public:
  using graph<T>::edges;
  using graph<T>::g;
  using graph<T>::n;
  using graph<T>::ignore;

  digraph(int _n) : graph<T>(_n) {}

  int add(int from, int to, T cost = 1) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    int id = (int)edges.size();
    g[from].push_back(id);
    edges.push_back({from, to, cost});
    return id;
  }

  digraph<T> reverse() const {
    digraph<T> rev(n);
    for (auto &e : edges) {
      rev.add(e.to, e.from, e.cost);
    }
    if (ignore != nullptr) {
      rev.set_ignore_edge_rule([&](int id) { return ignore(id); });
    }
    return rev;
  }
};

template <typename T>
vector<T> bellman(const graph<T> &g, int start) {
  assert(0 <= start && start < g.n);
  int inf = numeric_limits<T>::max();
  vector<T> dist(g.n, inf);
  dist[start] = 0;
  for (int i = 1; i < g.n; ++i) {
    bool flg = false;
    for (auto e: g.edges) {
      if (dist[e.from] != inf && dist[e.to] > dist[e.from] + e.cost) {
        dist[e.to] = dist[e.from] + e.cost;
        flg = true;
      }
    }
    if (!flg) {
      break;
    }
  }
  return dist;
};

int main() {
  ios::sync_with_stdio(false);
  int n, m, s;
  cin >> n >> m >> s;
  --s;
  digraph<int> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    --u;
    --v;
    g.add(u, v, w);
  }
  vector<int> dist = bellman(g, s);
  for (int i = 0; i < n; ++i) {
    cout << dist[i] << " " ;
  }
  return 0;
}
