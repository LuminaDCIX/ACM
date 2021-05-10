// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

inline int read() {
  int f(1), x(0);
  char ch(getchar());
  while (ch < '0' || ch > '9') {
    f = (ch == '-') ? -1 : 1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return f * x;
}

const int N = 100 + 5;
const int V = N * N + N + 5;
const int M = 2 * (N + N + N + N * N * N + N * N) + 5;
const int s = V - 2;
const int t = V - 1;
const int inf = 1e9;

int n, m;

int a[N], val[N];

int head[V], cur[V];
int nxt[M], ver[M], cap[M];

void add_edge(int u, int v, int c) {
  static int tot = 0;
  nxt[tot] = head[u];
  ver[tot] = v;
  cap[tot] = c;
  head[u] = tot++;
}
void add(int u, int v, int c) {
  add_edge(u, v, c);
  add_edge(v, u, 0);
}

bool vis[V];
int dist[V];

inline bool bfs() {
  queue <int> que;
  que.push(s);
  memset(vis, 0, sizeof(vis));
  vis[s] = 1;
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    for (int o = head[u]; ~o; o = nxt[o]) {
      int v = ver[o];
      if (!vis[v] && cap[o]) {
        vis[v] = 1;
        dist[v] = dist[u] + 1;
        que.push(v);
      }
    }
  }
  return vis[t];
} 

int dfs(int u, int flow) {
  if (u == t || flow == 0) {
    return flow;
  }
  int tot = 0;
  for (int &o = cur[u]; ~o; o = nxt[o]) {
    int v = ver[o];
    if (dist[v] == dist[u] + 1 && cap[o]) {
      int now = dfs(v, min(flow, cap[o]));
      if (!now) {
        continue;
      }
      cap[o] -= now;
      cap[o ^ 1] += now;
      flow -= now;
      tot += now;
      if (!flow) {
        break;
      }
    }
  }
  return tot;
}

inline int dinic() {
  int ans = 0;
  while (bfs()) {
    memcpy(cur, head, sizeof(head));
    ans += dfs(s, inf);
  }
  return ans;
}

int main() {
  memset(head, -1, sizeof(head));
  n = read();
  m = read();
  for (int i = 0; i < n; ++i) {
    a[i] = read();
  }
  int siz = 0;
  { 
    vector <int> v;
    for (int i = 0; i < n; ++i) {
      v.push_back(a[i]);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    siz = (int) v.size();
    for (int i = 0; i < siz; ++i) {
      val[i] = v[i];
    } 
    for (int i = 0; i < n; ++i) {
      a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
    }
  }
  for (int i = 0; i < siz; ++i) {
    add(s, i, m * val[i] * val[i]);
  }
  for (int i = 0; i < n; ++i) {
    int v = n + i * n + i;
    add(s, v, val[a[i]]);
    add(a[i], v, inf);
  }
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      int v = n + i * n + j;
      int k(read());
      if (k > 0) {
        ans += k;
        add(v, t, k);
      } else {
        add(s, v, -k);
      }
      if (i == j) {
        continue;
      }
      int len = j - i;
      for (int l = i; l <= n - len && l <= j - len + 1; ++l) {
        int u = n + l * n + (l + len - 1);
        add(u, v, inf);
      }
    }
  }
  ans -= dinic();
  printf("%d\n", ans);
  return 0;
}