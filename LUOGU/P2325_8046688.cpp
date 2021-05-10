// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

template <typename T>
class graph {
public:
  struct edge {
    int from;
    int to;
    T val;
  };
 
  int n;
  vector<edge> edges;
  vector<vector<int> > g;
  
  graph(int _n) : n(_n) {
    g.resize(n);
  }
};

template <typename T>
class forest : public graph<T> {
public:
  using graph<T>::edges;
  using graph<T>::g;
  using graph<T>::n;

  forest(int _n) : graph<T>(_n) {
  }

  int add_edge(int from, int to, T cost = 1) {
    int id = (int) edges.size();
    g[from].push_back(id);
    g[to].push_back(id);
    edges.push_back({from, to, cost});
    return id;
  }
};

int top[1005];
int b;

template <typename T>
class tree_dec : public forest<T> {
public:
  using forest<T>::edges;
  using forest<T>::g;
  using forest<T>::n;
  
  int cnt;
  int siz;
  stack<int> stk;
  vector<int> bel;

  tree_dec(int _n) : forest<T>(_n) {
    cnt = 0;
    siz = b;
    bel.resize(n, -1);
  }
  
  void dfs(int v, int fa) {
    int cur = (int) stk.size();
    for (auto id : g[v]) {
      auto &e = edges[id];
      int u = v ^ e.from ^ e.to;
      if (u == fa) {
        continue;
      }
      dfs(u, v);
      if ((int) stk.size() - cur >= siz) {
        while ((int) stk.size() != cur) {
          int k = stk.top();
          stk.pop();
          bel[k] = cnt;
        }
        top[cnt] = v;
        cnt++;
      }
    }
    stk.push(v);
  }
  
  void solve() {
    dfs(0, -1);
    if (cnt == 0) {
      ++cnt;
    }
    while (!stk.empty()) {
      int k = stk.top();
      stk.pop();
      bel[k] = cnt - 1;
    }
  }

};


int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  int m;
  cin >> n >> b;
  tree_dec<int> t(n);
  for (int i = 0, v, u; i < n - 1; ++i) {
    cin >> v >> u;
    --v, --u;
    t.add_edge(v, u);
  }
  t.solve();
  cout << t.cnt << endl;
  for (auto i : t.bel) {
    cout << i + 1 << " ";
  }
  cout << endl;
  for (int i = 0; i < t.cnt; ++i) {
    cout << top[i] + 1 << " ";
  }
  cout << endl;
                  
  return 0;
}
