#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 200 + 5;
const int M = 1000 + 5;
const int MAX = 1000 * 2 + 200 * 2 + 5;
const int S = N - 2;
const int T = N - 1;
const int inf = 1e9;

int u[M];
int v[M];
int t[M];

int ind[N];
int outd[N];

int n;
int m;

struct Edge {
  Edge *nxt;
  Edge *r;
  int to;
  int cap;

  Edge *set(int _to, int _cap, Edge *_nxt) {
    to = _to;
    cap = _cap;
    nxt = _nxt;
    return this;
  }
};

Edge e[MAX];
Edge *top = e;
Edge* head[N];
Edge* cur[N];

Edge *makeEdge(int u, int v, int cap) {
  return head[u] = (top++)->set(v, cap, head[u]);
}

void add(int u, int v, int cap) {
  Edge *st = makeEdge(u, v, cap);
  Edge *ts = makeEdge(v, u, 0);
  st->r = ts;
  ts->r = st;
}

int dist[N];
int vis[N];

bool bfs() {
  queue <int> que;
  que.push(S);
  memset(vis, 0, sizeof(vis));
  vis[S] = 1;
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    for (Edge *o = head[u]; o; o = o->nxt) {
      int v = o->to;
      if (!vis[v] && o->cap) {
        vis[v] = 1;
        dist[v] = dist[u] + 1;
        que.push(v);
      }
    }
  }
  return vis[T];
}

int dfs(int u, int f) {
  if (u == T || f == 0) {
    return f;
  }
  int sum = 0;
  for (Edge *&o = cur[u]; o; o = o->nxt) {
    int v = o->to;
    int s = 0;
    if (dist[v] == dist[u] + 1 && o->cap && (s = dfs(v, min(f, o->cap))) > 0) {
      o->cap -= s;
      o->r->cap += s;
      f -= s;
      sum += s;
      if (!f) {
        break;
      }
    }
  }
  return sum;
}

int dinic() {
  int ret = 0;
  while (bfs()) {
    for (int i = 0; i <= T; ++i) {
      cur[i] = head[i];
    }
    ret += dfs(S, inf);
  }
  return ret;
}


void solve() {
  memset(head, 0, sizeof(head));
  top = e;
  scanf("%d %d", &n, &m);
  memset(ind, 0, sizeof(ind));
  memset(outd, 0, sizeof(outd));
  for (int i = 0; i < m; ++i) {
    scanf("%d %d %d", &u[i], &v[i], &t[i]);
    --u[i];
    --v[i];
    ++outd[u[i]];
    ++ind[v[i]];
  }
  for (int i = 0; i < n; ++i) {
    if (abs(ind[i] - outd[i]) & 1) {
      puts("impossible");
      return;
    }
  }
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    int k = ind[i] - outd[i];
    if (k < 0) {
      add(S, i, -k / 2);
    } else if (k > 0) {
      add(i, T, k / 2);
      sum += k / 2;
    }
  }
  for (int i = 0; i < m; ++i) {
    if (t[i] == 0) {
      add(u[i], v[i], 1);
    }
  }
  sum -= dinic();
  puts(sum == 0 ? "possible" : "impossible");
  return;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    solve();
  }
  return 0;
}
