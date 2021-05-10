#include <bits/stdc++.h>

using namespace std;

const int N = 5000 + 5;

vector<int> g[N];
vector<int> val[N];

void addEdge(int u, int v, int w) {
  g[u].push_back(v);
  val[u].push_back(w);
  g[v].push_back(u);
  val[v].push_back(w);
}

int n, m;
int dist[N];

priority_queue<pair<int, int> > heap;

void init() {
  memset(dist, 0x3f3f, sizeof(dist));
  dist[n] = 0;
  heap.push(make_pair(0, n));
  while (!heap.empty()) {
    int u = heap.top().second;
    heap.pop();
    for (int i = 0; i < (int)g[u].size(); ++i) {
      int v = g[u][i];
      int w = val[u][i];
      if (dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        heap.push(make_pair(-dist[v], v));
      }
    }
  }
}

struct node {
  int g;
  int u;
  int pre;
  int idx;

  node(int _g, int _u, int _pre, int _idx) {
    g = _g;
    u = _u;
    pre = _pre;
    idx = _idx;
  }
  bool operator<(const node v) const { return g + dist[u] > v.g + dist[v.u]; }
};

priority_queue<node> que;
vector<node> nodes;
int idx;

void print(int idx) {
  if (nodes[idx].pre == -1) {
    cout << "1 ";
    return;
  }
  print(nodes[idx].pre);
  cout << nodes[idx].u << " ";
}

int main() {
  cin >> n >> m;
  for (int i = 0, x, y, v; i < m; ++i) {
    cin >> x >> y >> v;
    addEdge(x, y, v);
  }
  init();
  int mn = dist[1];
  nodes.push_back(node(0, 1, -1, 0));
  que.push(nodes[0]);
  while (!que.empty()) {
    int gu = que.top().g;
    int u = que.top().u;
    int preIdx = que.top().idx;
    que.pop();
    if (u == n && gu > mn) {
      cout << gu << endl;
      break;
    }
    for (int i = 0; i < (int)g[u].size(); ++i) {
      int v = g[u][i];
      int w = val[u][i];
      nodes.push_back(node(gu + w, v, preIdx, ++idx));
      que.push(nodes[idx]);
    }
  }

  return 0;
}