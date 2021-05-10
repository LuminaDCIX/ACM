#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

inline int read()
{
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

using namespace std;

const int N = 1000 + 5;
typedef long long ll;

struct atom {
  ll cst;
  ll cnt;
};

bool operator < (const atom &a, const atom &b) {
  return a.cst == b.cst ? a.cnt < b.cnt : a.cst < b.cst;
}

atom operator + (const atom &a, const atom &b) {
  atom x;
  x.cst = a.cst + b.cst;
  x.cnt = a.cnt + b.cnt;
  return x;
}

atom G[N][N];

int s, t;
int n, m;

atom dist[N];
bool vis[N];

inline void dijkstra()
{
  memset(dist, 0x3f3f, sizeof(dist));
  dist[s].cst = 0;
  dist[s].cnt = 0;
  for (int i = 1; i < n; ++i) {
    atom x;
    x.cst = x.cnt = 0x3f3f3f3f3f3f3f3fll;
    int u = -1;
    for (int j = 1; j <= n; ++j) {
      if (!vis[j] && dist[j] < x) {
	x = dist[j];
	u = j;
      }
    }
    if (u == -1) {
      return;
    }
    vis[u] = 1;
    for (int v = 1; v <= n; ++v) {
      if (v == u || vis[v]) {
	continue;
      }
      if (dist[u] + G[u][v] < dist[v]) {
	dist[v] = G[u][v] + dist[u];
      }
    }
  }
}

int main()
{
  memset(G, 0x3f3f, sizeof(G));
  s = read();
  t = read();
  m = read();
  vector <int> v;
  for (int i = 0; i < m; ++i) {
    atom a;
    v.clear();
    a.cst = read();
    int siz = read();
    for (int j = 0, c; j < siz; ++j) {
      c = read();
      n = max(n, c);
      v.push_back(c);
    }
    for (int j = 0, x; j < siz; ++j) {
      x = v[j];
      for (int k = j + 1, y; k < siz; ++k) {
	a.cnt = k - j;
	y = v[k];
	if (a < G[x][y]) {
	  G[x][y] = a;
	}
      }
    }
  }
  dijkstra();
  if (dist[t].cst == 0x3f3f3f3f3f3f3f3fll) {
    puts("-1 -1");
    return 0;
  }
  printf("%lld %lld\n", dist[t].cst, dist[t].cnt);
  return 0;
}
