#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 250 + 5;
const int M = 250 + 5;
const int MAXN = 250 * 7 + 250 + 105;
const int MAXM = 2 * (250 * 250 + 250 * 6 * 2) + 1005;
const int S = MAXN - 2;
const int T = MAXN - 1;
const long long inf = 0x3f3f3f3f3f3f3f3fll;

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

struct Edge {
  int nxt;
  int to;
  int from;
  long long cap;
  long long cost;

  Edge(int _nxt = 0, int _to = 0, int _from = 0, long long _cap = 0, long long _cost = 0):nxt(_nxt), to(_to), from(_from), cap(_cap), cost(_cost) {};
};

int head[MAXN];
int tot;
Edge e[MAXM];

void add(int u, int v, long long cap, long long cost) {
  e[tot] = Edge(head[u], v, u, cap, cost);
  head[u] = tot++;
  e[tot] = Edge(head[v], u, v, 0, -cost);
  head[v] = tot++;
}

int from[MAXN];
long long dist[MAXN];
bool inq[MAXN];

int n;
int m;

bool spfa() {
  memset(dist, 0x3f3f, sizeof(dist));
  dist[S] = 0 ;
  queue <int> que;
  que.push(S);
  inq[S] = 1;
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    inq[u] = 0;
    for (int o = head[u]; ~o; o = e[o].nxt) {
      int v = e[o].to;
      if (e[o].cap && dist[v] > dist[u] + e[o].cost) {
        dist[v] = dist[u] + e[o].cost;
        from[v] = o;
        if (!inq[v]) {
          inq[v] = 1;
          que.push(v);
        }
      }
    }
  }
  return dist[T] == inf ? 0 : 1;
}

long long MCMF() {
  long long ans = 0;
  memset(from, -1, sizeof(from));
  while (spfa()) {
    long long now = inf;
    for (int o = from[T]; ~o; o = from[e[o].from]) {
      now = min(now, e[o].cap);
    }
    for (int o = from[T]; ~o; o = from[e[o].from]) {
      e[o].cap -= now;
      e[o ^ 1].cap += now;
      ans += (long long) now * e[o].cost;
    }
  }
  return ans;
}

int main() {
  memset(head, -1, sizeof(head));
  n = read();
  m = read();
  int base = n * 7;
  for (int i = 0; i < m; ++i) {
    int c = read();
    add(base + i, T, c, 0);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      bool o = read();
      if (o) {
        add(i * 7 + 6, base + j, inf, 0);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    int cnt = read();
    vector <int> W(cnt + 1);
    vector <int> T(cnt + 1);
    for (int j = 0; j < cnt; ++j) {
      T[j] = read();
    }
    for (int j = 0; j <= cnt; ++j) {
      W[j] = read();
    }
    int T_lst = 0;
    for (int j = 0; j < cnt; ++j) {
      int T_now = T[j];
      add(S, i * 7 + j, T_now - T_lst, W[j]);
      add(i * 7 + j, i * 7 + 6, inf, 0);
      T_lst = T_now;
    }
    add(S, i * 7 + 5, inf, W[cnt]);
    add(i * 7 + 5, i * 7 + 6, inf, 0);
  }
  long long ans = MCMF();
  printf("%lld\n", ans);
  return 0;
}
