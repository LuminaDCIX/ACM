#include <bits/stdc++.h>
#include <limits>
#include <utility>

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
      return dist;
    }
  }
  return vector<int> ();
};

template <typename T>
vector<T> dijkstra(const graph<T> &g, int start) {
  assert(0 <= start && start < g.n);
  vector<T> dist(g.n, numeric_limits<T>::max());
  priority_queue<pair<T, int>, vector<pair<T, int> >, greater<pair<T, int> > >
      s;
  dist[start] = 0;
  s.emplace(dist[start], start);
  while (!s.empty()) {
    T expected = s.top().first;
    int i = s.top().second;
    s.pop();
    if (dist[i] != expected) {
      continue;
    }
    for (int id : g.g[i]) {
      if (g.ignore != nullptr && g.ignore(id)) {
        continue;
      }
      auto &e = g.edges[id];
      int to = e.from ^ e.to ^ i;
      if (dist[i] + e.cost < dist[to]) {
        dist[to] = dist[i] + e.cost;
        s.emplace(dist[to], to);
      }
    }
  }
  return dist;
};


template <typename T>
vector<vector<T> > johnson(const graph<T> &g) {
  int n = g.n;
  digraph<T> t(g.n + 1);
  for (auto e: g.edges) {
    t.add(e.from, e.to, e.cost);
  }
  for (int i = 0; i < n; ++i) {
    t.add(n, i, 0);
  }
  vector<int> h = bellman(t, n);
  if (!h.size()) {
    return vector<vector<int> > ();
  }
  for (auto &e: t.edges) {
    if (e.from != n) {
      e.cost += h[e.from] - h[e.to];
    }
  }
  t.set_ignore_edge_rule([&](int x) -> bool { return t.edges[x].from == n; });
  vector<vector<T> > dist;
  for (int i = 0; i < n; ++i) {
    dist.push_back(dijkstra(t, i));
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (dist[i][j] != numeric_limits<T>::max()) {
        dist[i][j] -= h[i] - h[j];
      }
    }
  }
  return dist;
}

int main() {
  ios::sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  digraph<int> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    --u;
    --v;
    g.add(u, v, w);
  }
  vector<vector<int> > dist = johnson(g);
  if (dist.size() == 0) {
    cout << -1 << endl;
    return 0;
  }
  for (int i = 0; i < n; ++i) {
    long long sum = 0;
    for (int j = 0; j < n; ++j) {
      sum += (j + 1) * (long long) (dist[i][j] == numeric_limits<int>::max() ? 1e9 : dist[i][j]);
    }
    cout << sum << endl;
  }
  return 0;
}
