#include <bits/stdc++.h>

using namespace std;

const int N = 800 + 5;
const int M = 15000 + 5;
const int MAXN = 800 * 2 + 5;
const int MAXM = 2 * (15000 + 800 * 3) + 105;
const int S = MAXN - 2;
const int T = MAXN - 1;

int read() {
  int x;
  scanf("%d", &x);
  return x;
}

struct edge {
  edge *nxt;
  edge *r;
  int to;
  int from;
  int cap;
  int cost;
  edge* set(int _from, int _to, int _cap, int _cost, edge *_nxt) {
    to = _to;
    from = _from;
    cap = _cap;
    cost = _cost;
    nxt = _nxt;
    return this;
  }
};

edge e[MAXM];
edge *top = e;
edge *head[MAXN];

edge* make(int u, int v, int cap, int cost) {
  return head[u] = (top++)->set(u, v, cap, cost, head[u]);
}

edge* add(int u, int v, int cap, int cost) {
  edge *st = make(u, v, cap, cost);
  edge *ts = make(v, u, 0, -cost);
  st->r = ts;
  ts->r = st;
}

edge *from[MAXN];

long long dist[MAXN];
bool inq[MAXN];

bool spfa() {
  queue <int> que;
  inq[S] = 1;
  memset(dist, 0x3f3f, sizeof(dist));
  dist[S] = 0;
  que.push(S);
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    inq[u] = 0;
    for (edge *o = head[u]; o; o = o->nxt) {
      int v = o->to;
      if (o->cap && dist[v] > dist[u] + o->cost) {
        dist[v] = dist[u] + o->cost;
        from[v] = o;
        if (!inq[v]) {
          inq[v] = 1;
          que.push(v);
        }
      }
    }
  }
  return dist[T] == 0x3f3f3f3f3f3f3f3fll ? 0 : 1;
}

int MCFC() {
  int ans = 0;
  while (spfa()) {
    int now = 0x3f3f3f3f;
    for (edge *o = from[T]; o; o = from[o->from]) {
      now = min(now, o->cap);
    }
    for (edge *o = from[T]; o; o = from[o->from]) {
      ans += o->cost * now;
      o->cap -= now;
      o->r->cap += now;
    }
  }
  return ans;
}

int n;
int m;

int main() {
  n = read();
  m = read();
  for (int i = 0; i < n; ++i) {
    int c = read();
    add(S, i, 1, c);
    add(S, i + n, 1, 0);
    add(i, T, 1, 0);
  }
  for (int i = 0; i < m; ++i) {
    int u = read();
    int v = read();
    int c = read();
    if (u > v) {
      swap(u, v);
    }
    --u;
    --v;
    add(u + n, v, 1, c);
  }
  long long ans = MCFC();
  printf("%lld\n", ans);
  return 0;
}
