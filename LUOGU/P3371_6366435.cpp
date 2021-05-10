// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;


const int N = 1000005;
const int M = 10000005;

int n, m;

typedef vector <int> vi;
vi ver[N];
vi val[N];

inline void add(int u, int v, int c) {
  ver[u].push_back(v);
  val[u].push_back(c);
}

typedef pair <int, int> pii;

struct dijkstra {
  bool vis[N];
  int dist[N];

  void solve(int s) {
    priority_queue <pii, vector <pii>, greater <pii> > que;
    memset(dist, 0x3f3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    dist[s] = 0;
    que.push(make_pair(0, s));
    while (!que.empty()) {
      int u = que.top().second;
      que.pop();
      if (vis[u]) {
        continue;
      }
      vis[u] = 1;
      for (int o = 0; o < (int) ver[u].size(); ++o) {
        int v = ver[u][o];
        if (val[u][o] + dist[u] < dist[v]) {
          dist[v] = val[u][o] + dist[u];
          que.push(make_pair(dist[v], v));
        }
      }
    }
  }
};

dijkstra ss;

int main() {
  int s;
  scanf("%d %d %d", &n, &m, &s);
  for (int i = 1, u, v, c; i <= m; ++i) {
    scanf("%d %d %d", &u, &v, &c);
    add(u, v, c);
  }
  ss.solve(s);
  for (int i = 1; i <= n; ++i) {
    if (ss.dist[i] == 0x3f3f3f3f)  {
      printf("%d ", 2147483647);
    } else {
      printf("%d ", ss.dist[i]);
    }
  }
  puts("");
  return 0;
}
