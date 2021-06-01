#include <bits/stdc++.h>

using namespace std;

std::string to_string(std::string s) { return '"' + s + '"'; }

std::string to_string(const char* s) { return to_string((std::string)s); }

std::string to_string(bool b) { return (b ? "true" : "false"); }

template <typename A, typename B>
std::string to_string(std::pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A>
std::string to_string(A v) {
  using ::to_string;
  using std::to_string;
  bool first = true;
  std::string res = "{";
  for (const auto& x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}

void debug_out() { std::cerr << std::endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  using ::to_string;
  using std::to_string;
  std::cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef LOCAL
#define debug(...)                                    \
  std::cerr << __FUNCTION__ << "(" << __LINE__ << ")" \
            << "[" << #__VA_ARGS__ << "]:",           \
      debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

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

  virtual void set_ignore_edge_rule(const function<bool(int)>& f) {
    ignore = f;
  }

  virtual void reset_ignore_edge_rule() { ignore = nullptr; }
};

template <typename T>
class forest : public graph<T> {
 public:
  using graph<T>::edges;
  using graph<T>::g;
  using graph<T>::n;

  forest(int _n) : graph<T>(_n) {}

  int add(int from, int to, T cost = 1) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    int id = (int)edges.size();
    assert(id < n - 1);
    g[from].push_back(id);
    g[to].push_back(id);
    edges.push_back({from, to, cost});
    return id;
  }
};

template <typename T>
class dfs_forest : public forest<T> {
 public:
  using forest<T>::edges;
  using forest<T>::g;
  using forest<T>::n;
  using forest<T>::ignore;

  vector<int> pv;
  vector<int> pe;
  vector<int> order;
  vector<int> pos;
  vector<int> end;
  vector<int> sz;
  vector<int> root;
  vector<int> depth;
  vector<T> dist;

  dfs_forest(int _n) : forest<T>(_n) {}

  void init() {
    pv = vector<int>(n, -1);
    pe = vector<int>(n, -1);
    order.clear();
    pos = vector<int>(n, -1);
    end = vector<int>(n, -1);
    sz = vector<int>(n, 0);
    root = vector<int>(n, -1);
    depth = vector<int>(n, -1);
    dist = vector<T>(n);
  }

  void clear() {
    pv.clear();
    pe.clear();
    order.clear();
    pos.clear();
    end.clear();
    sz.clear();
    root.clear();
    depth.clear();
    dist.clear();
  }

 private:
  void do_dfs(int v) {
    pos[v] = (int)order.size();
    order.push_back(v);
    sz[v] = 1;
    for (int id : g[v]) {
      if (id == pe[v] || (ignore != nullptr && ignore(id))) {
        continue;
      }
      auto& e = edges[id];
      int to = e.from ^ e.to ^ v;
      depth[to] = depth[v] + 1;
      dist[to] = dist[v] + e.cost;
      pv[to] = v;
      pe[to] = id;
      root[to] = (root[v] != -1 ? root[v] : to);
      do_dfs(to);
      sz[v] += sz[to];
    }
    end[v] = (int)order.size() - 1;
  }

  void do_dfs_from(int v) {
    depth[v] = 0;
    dist[v] = T{};
    root[v] = v;
    pv[v] = pe[v] = -1;
    do_dfs(v);
  }

 public:
  void dfs(int v, bool clear_order = true) {
    if (pv.empty()) {
      init();
    } else {
      if (clear_order) {
        order.clear();
      }
    }
    do_dfs_from(v);
  }

  void dfs_all() {
    init();
    for (int v = 0; v < n; v++) {
      if (depth[v] == -1) {
        do_dfs_from(v);
      }
    }
    assert((int)order.size() == n);
  }
};

template <typename T>
class lca_forest : public dfs_forest<T> {
 public:
  using dfs_forest<T>::edges;
  using dfs_forest<T>::g;
  using dfs_forest<T>::n;
  using dfs_forest<T>::pv;
  using dfs_forest<T>::pos;
  using dfs_forest<T>::end;
  using dfs_forest<T>::depth;

  int h;
  vector<vector<int> > pr;

  lca_forest(int _n) : dfs_forest<T>(_n) {}

  inline void build_lca() {
    assert(!pv.empty());
    int max_depth = 0;
    for (int i = 0; i < n; i++) {
      max_depth = max(max_depth, depth[i]);
    }
    h = 1;
    while ((1 << h) <= max_depth) {
      h++;
    }
    pr.resize(n);
    for (int i = 0; i < n; i++) {
      pr[i].resize(h);
      pr[i][0] = pv[i];
    }
    for (int j = 1; j < h; j++) {
      for (int i = 0; i < n; i++) {
        pr[i][j] = (pr[i][j - 1] == -1 ? -1 : pr[pr[i][j - 1]][j - 1]);
      }
    }
  }

  inline bool anc(int x, int y) {
    return (pos[x] <= pos[y] && end[y] <= end[x]);
  }

  inline int lca(int x, int y) {
    assert(!pr.empty());
    if (anc(x, y)) {
      return x;
    }
    if (anc(y, x)) {
      return y;
    }
    for (int j = h - 1; j >= 0; j--) {
      if (pr[x][j] != -1 && !anc(pr[x][j], y)) {
        x = pr[x][j];
      }
    }
    return pr[x][0];
  }
};

template <typename T>
tuple<int, forest<T>, vector<int> > vtree(lca_forest<T>& g, vector<int> id) {
  assert(id.size() > 1);
  sort(id.begin(), id.end(),
       [&](int i, int j) -> bool { return g.pos[i] < g.pos[j]; });
  vector<array<int, 2> > edges;
  vector<int> stk(id.size() * 2);
  int top = 0;
  for (auto v : id) {
    if (!top) {
      stk[top++] = v;
      continue;
    }
    int l = g.lca(v, stk[top - 1]);
    if (l != stk[top - 1]) {
      while (top > 1 && g.pos[l] <= g.pos[stk[top - 2]]) {
        edges.push_back({stk[top - 2], stk[top - 1]});
        --top;
      }
      if (g.pos[l] < g.pos[stk[top - 1]]) {
        edges.push_back({l, stk[top - 1]});
        --top;
      }
      if (!top || stk[top - 1] != l) {
        stk[top++] = l;
      }
    }
    stk[top++] = v;
  }
  int root = stk[0];
  for (int i = 0; i < top - 1; ++i) {
    edges.push_back({stk[i], stk[i + 1]});
  }
  map<int, int> ori;
  forest<T> res(edges.size() + 1);
  vector<int> rev(edges.size() + 1);
  int tot = 0;
  for (auto e : edges) {
    if (ori.find(e[0]) == ori.end()) {
      ori[e[0]] = tot++;
    }
    if (ori.find(e[1]) == ori.end()) {
      ori[e[1]] = tot++;
    }
    int u = ori[e[0]];
    int v = ori[e[1]];
    res.add(u, v, g.dist[e[1]] - g.dist[e[0]]);
  }
  for (auto p : ori) {
    rev[p.second] = p.first;
  }
  return {ori[root], res, rev};
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  lca_forest<int> g(n);
  vector<int> col(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    --u;
    --v;
    g.add(u, v);
  }
  g.dfs(0);
  g.build_lca();
  int m;
  cin >> m;
  for (int i = 0; i < m; ++i) {
    int k;
    cin >> k;
    vector<int> nodes(k);
    for (int j = 0; j < k; ++j) {
      cin >> nodes[j];
      --nodes[j];
    }
    if (k == 1) {
      cout << 0 << endl;
      continue;
    }

    for (auto u : nodes) {
      col[u] = 1;
    }
    auto foo = vtree(g, nodes);
    forest<int>& f = get<1>(foo);
    vector<int>& id = get<2>(foo);
    int root = get<0>(foo);
    int ans = 0;
    bool ok = true;
    function<int(int, int)> dfs = [&](int u, int fa) -> int {
      int cnt = 0;
      for (int o : f.g[u]) {
        auto& e = f.edges[o];
        int to = e.from ^ e.to ^ u;
        if (to == fa) {
          continue;
        }
        if (dfs(to, u)) {
          if (col[id[u]]) {
            if (e.cost > 1 || !col[id[to]]) {
              ++ans;
            } else {
              ok = false;
            }
          } else {
            ++cnt;
          }
        }
      }
      if (!col[id[u]]) {
        if (cnt > 1) {
          ++ans;
          return 0;
        }
      }
      return col[id[u]] || cnt == 1;
    };
    dfs(root, -1);
    for (auto v : nodes) {
      col[v] = 0;
    }
    cout << (ok ? ans : -1) << endl;
  }
  return 0;
}