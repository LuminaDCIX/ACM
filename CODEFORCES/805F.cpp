#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

inline int read()
{
  int f = 1;
  int x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    ch = (ch == '-') ? -1 : 1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return f * x;
}

const int N = 1e5 + 5;

int n;
int m;
int q;

int head[N];
int tot;

struct edge {
  int v;
  int nxt;
} e[N << 1];

bool vis[N];

inline void add(int u, int v) {
  e[tot].nxt = head[u];
  e[tot].v = v;
  head[u] = tot++;
}

void dfs(int u, int fa)
{
  vis[u] = 1;
  for (int o = head[u], v; ~o; o = e[o].nxt) {
    v = e[o].v;
    if (v == fa) {
      continue;
    }
    dfs(v, u);
  }
}

int len[N];
int f[N][2];
int son[N][2];

int cnt;
int belong[N];

void dfs1(int u, int fa, int bel)
{
  belong[u] = bel;
  for (int o = head[u], v; ~o ; o = e[o].nxt) {
    v = e[o].v;
    if (v == fa) {
      continue;
    }
    dfs1(v, u, bel);
    if (f[v][0] + 1 > f[u][0]) {
      f[u][1] = f[u][0];
      son[u][1] = son[u][0];
      f[u][0] = f[v][0] + 1;
      son[u][0] = v;
    } else if (f[v][0] + 1 >= f[u][1]) {
      f[u][1] = f[v][0] + 1;
      son[u][1] = v;
    }
  }
  len[bel] = max(len[bel], f[u][0] + f[u][1]);
}

vector <int> dist[N];

void dfs2(int u, int fa, int cnt, int mx)
{
  dist[cnt].push_back(max(mx, f[u][0]));
  for (int o = head[u], v; ~o; o = e[o].nxt) {
    v = e[o].v;
    if (v == fa) {
      continue;
    }
    if (v == son[u][0]) {
      dfs2(v, u, cnt, max(mx, f[u][1]) + 1);
      continue;
    }
    dfs2(v, u, cnt, max(mx, f[u][0]) + 1);
  }
}

map <int, double> ans[N];

inline double solve(int x, int y)
{
  if (dist[x].size() > dist[y].size() || (dist[x].size() == dist[y].size() && x > y)) {
    swap(x, y);
  }
  if (ans[x].find(y) != ans[x].end()) {
    return ans[x][y];
  }
  double ret = 0;
  int sizx = dist[x].size();
  int sizy = dist[y].size();
  int ptr = dist[y].size();
  int sumy = 0;
  int lenmx = max(len[x], len[y]);
  
  for (int i = 0; i < (int) dist[x].size(); ++i) {
    while (ptr > 0 && dist[y][ptr - 1] + dist[x][i] + 1 > lenmx) {
      --ptr;
      sumy += dist[y][ptr];
    }
    ret += 1.0 * ptr * lenmx + (sizy - ptr) * (dist[x][i] + 1) + sumy;
  }
  if (ret == 0) {
    ret += lenmx;
    return ans[x][y] = ret;
  }
  return ans[x][y] = ret / sizx / sizy;
}

void print(int x)
{
  for (int i = 1; i <= n; ++i) {
    if (belong[i] != x) {
      continue;
    }
    for (int o = head[i]; ~o; o = e[o].nxt) {
      printf("%d %d\n", i, e[o].v);
    }
  }
  for (int i = 0; i < dist[x].size(); ++i) {
    printf("%d ", dist[x][i]);
  }
  puts("");
}

int main()
{
  memset(head, -1, sizeof(head));
  n = read();
  m = read();
  q = read();
  for (int i = 0, u, v; i < m; ++i) {
    u = read();
    v = read();
    add(u, v);
    add(v, u);
  }
  for (int i = 1; i <= n; ++i) {
    if (!vis[i]) {
      dfs(i, -1);
      dfs1(i, -1, ++cnt);
      dfs2(i, -1, cnt, 0);
    }
  }
  for (int i = 1; i <= cnt; ++i) {
    sort(dist[i].begin(), dist[i].end());
  }
  for (int i = 0, x, y; i < q; ++i) {
    x = read();
    y = read();
    if (belong[x] == belong[y]) {
      puts("-1");
      continue;
    }
    printf("%.10f\n", solve(belong[x], belong[y]));
  }
  return 0;
}
