// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

const int N = 5000 + 5;
const int MAXN = 5000 + 5;
const int MAXM = 2 * 50000 + 5;
const int inf = 0x3f3f3f3f;

int read() {
  int f = 1;
  int x = 0;
  char ch = getchar();
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

struct edge {
  edge *nxt;
  edge *r;
  int to;
  int cap;
  int cost;
  int from; 

  edge *set(int _to, int _cap, int _cost, int _from, edge *_nxt) {
    to = _to;
    cap = _cap;
    from = _from;
    cost = _cost;
    nxt = _nxt;
    return this;
  }

  void update(int f) {
    cap -= f;
    r->cap += f;
  }
};

edge e[MAXM];
edge *top = e;
edge *head[MAXN];
edge *pre[MAXN];

edge* makeEdge(int u, int v, int cap, int cost) {
  return head[u] = (top++)->set(v, cap, cost, u, head[u]);
}

void addEdge(int u, int v, int cap, int cost) {
  edge *st = makeEdge(u, v, cap, cost);
  edge *ts = makeEdge(v, u, 0, -cost);
  st->r = ts;
  ts->r = st;
}  

int n;
int m;
int s;
int t;

int dist[MAXN];
int inq[MAXN];

int que[60005];

bool spfa() {
  int h = 0;
  int r = 1;
  que[h] = s;
  inq[s] = 1;
  memset(dist, inf, sizeof(dist));
  dist[s] = 0;
  while (h < r) {
    int u = que[h++];
    inq[u] = 0;
    for (edge *o = head[u]; o; o = o->nxt) {
      int v = o->to;
      int w = o->cost;
      if (dist[v] > dist[u] + w && o->cap) {
        dist[v] = dist[u] + w;
        pre[v] = o;
        if (inq[v] == 0) {
          inq[v] = 1;
          que[r++] = v;
        }
      }
    }
  }
  return dist[t] != inf;
}

void MCFC() {
  int ans = 0;
  int tot = 0;
  while (spfa()) {
    int f = inf;
    for (register edge *o = pre[t]; o; o = pre[o->from]) {
      f = min(f, o->cap);
    }
    for (register edge *o = pre[t]; o; o = pre[o->from]) {
      o->update(f);
      ans += f * o->cost;
    }
    tot += f;
  }
  printf("%d %d\n", tot, ans);
}

int main() {
  n = read();
  m = read();  
  s = read() - 1;
  t = read() - 1;
  for (int i = 0; i < m; ++i) {
    int u = read() - 1;
    int v = read() - 1;
    int c = read();
    int w = read();
    addEdge(u, v, c, w);
  }
  MCFC();
  return  0;
}