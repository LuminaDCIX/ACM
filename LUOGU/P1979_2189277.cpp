#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <queue>

using namespace std;

const int inf = 0x3f3f3f3f;
int n, m, q;
int box[35][35];
int head[100005], tot, V;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
int d[35][35];
int f[35][35][4][4];
int id[35][35][4];
int ex, ey, sx, sy, tx, ty;
int s, t;
struct edge
{
  int nxt, to, val;
} edges[100005];
typedef pair<int, int> p;

inline void add_edge(int from, int to, int val)
{
  edges[++tot].to = to;
  edges[tot].nxt = head[from];
  edges[tot].val = val;
  head[from] = tot;
  return;
}

inline int bfs(int sx, int sy, int tx, int ty)
{
  if (sx == tx && sy == ty) {
    return 0;
  }
  queue <p> q;
  while (!q.empty()) {
    q.pop();
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      d[i][j] = inf;
    }
  }
  p a;
  a.first = sx;
  a.second = sy;
  q.push(a);
  d[sx][sy]=0;
  while (!q.empty()) {
    a = q.front();
    q.pop();
    int x = a.first;
    int y = a.second;
    for (int i = 0; i < 4; ++i) {
      int xx = x + dx[i];
      int yy = y + dy[i];
      if (box[xx][yy] && d[xx][yy] == inf) {
        d[xx][yy] = d[x][y] + 1;
        if (xx == tx && yy == ty) {
          //printf("%d\n", d[x][y]+1);
          return d[x][y] + 1;
        }
        a.first = xx;
        a.second = yy;
        q.push(a);
      }
    }
  }
  return inf;
}
queue <int> que;
int dis[100005];
bool vis[100005];
int spfa()
{
  for (int i = 1; i <= V; ++i) {
    dis[i] = inf;
  }
  while (!que.empty()) {
    que.pop();
  }
  dis[s] = 0;
  memset(vis, 0, sizeof(vis));
  que.push(s);
  vis[s] = 1;
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    vis[u] = 0;
    for (int p = head[u]; p; p = edges[p].nxt) {
      int v = edges[p].to;
      if (dis[v] > dis[u] + edges[p].val) {
        dis[v] = dis[u] + edges[p].val;
        if (!vis[v]) {
          que.push(v);
          vis[v] = 1;
        }
      }
    }
  }
  return dis[t] < inf ? dis[t] : -1;
}

void pre()
{
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      for (int h = 0; h < 4; ++h) {
        for (int k = 0; k < 4; ++k) {
          f[i][j][k][h] = inf;
        }
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) if (box[i][j]) {
      box[i][j] = 0;
      for (int k = 0; k < 4; ++k) if (box[i + dx[k]][j + dy[k]]) {
          for (int h = 0; h < 4; ++h) if (box[i + dx[h]][j + dy[h]]) {
            f[i][j][k][h] = bfs(i + dx[k], j + dy[k], i + dx[h], j + dy[h]) + 1;
            }
        }
      box[i][j] = 1;
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      for (int k = 0; k < 4; ++k) {
        for (int h = 0; h < 4; ++h) if (f[i][j][k][h] != inf) {
            add_edge(id[i][j][k], id[i + dx[h]][j + dy[h]][h ^ 1], f[i][j][k][h]);
          }
      }
    }
  }
  return;
}

void solve()
{
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &box[i][j]);
      for (int k = 0; k < 4; ++k) {
        id[i][j][k] = ++V;
      }
    }
  }
  pre();
  for (int i = 1; i <= q; ++i) {
    scanf("%d%d%d%d%d%d", &ex, &ey, &sx, &sy, &tx, &ty);
    if (sx == tx && sy == ty) {
      printf("%d\n", 0);
      continue;
    }
    if ((box[sx][sy] == 0) || (box[tx][ty] == 0)) {
      printf("-1\n");
      continue;
    }
    s = ++V;
    t = ++V;
    box[sx][sy] = 0;
    for (int i = 0; i < 4; ++i) if (box[sx + dx[i]][sy + dy[i]]) {
        int Dis = bfs(ex, ey, sx + dx[i], sy + dy[i]);
        if (Dis != inf) {
          add_edge(s, id[sx][sy][i], Dis);
        }
      }
    box[sx][sy] = 1;
    for (int i = 0; i < 4; ++i) if (box[tx + dx[i]][ty + dy[i]]) {
        add_edge(id[tx][ty][i], t, 0);
      }
    printf("%d\n", spfa());
  }

  return;
}

int main()
{
  solve();
  return 0;
}
