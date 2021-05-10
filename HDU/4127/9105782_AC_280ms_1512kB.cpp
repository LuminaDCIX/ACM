#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define maxn 10
#define inf 0x3f3f3f3f

using namespace std;

int n, m, ans;
int mp[maxn][maxn];
int succ, depth;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
bool vis[maxn][maxn];

struct node
{
  int x, y;
} cur, now, q[100];

struct Node
{
  int num;
  node xx[100];
};

void flood(Node &tt, int color[])
{
  int head = 0;
  int tail = -1;
  tt.num = 0;
  memset(vis, 0, sizeof(vis));
  cur.x = cur.y = 1;
  vis[1][1] = 1;
  q[++tail] = cur;
  while (head <= tail) {
    now = q[head++];
    tt.xx[++tt.num] = now;
    int nx = now.x;
    int ny = now.y;
    for (int i = 0; i < 4; ++i) {
      int tx = nx + dx[i];
      int ty = ny + dy[i];
      if (tx < 1 || tx > n || ty < 1 || ty > n || vis[tx][ty] || mp[tx][ty] != mp[nx][ny]) {
        continue;
      }
      cur.x = tx;
      cur.y = ty;
      vis[tx][ty] = 1;
      q[++tail] = cur;
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (!vis[i][j]) {
        color[mp[i][j]] |= 1;
      }
    }
  }
  return;
}

void dfs(int c, int cnt, int step)
{
  if (step > depth || succ) {
    return;
  }
  int color[6] = {0};
  Node tt;
  flood(tt, color);
  int num = tt.num;
  if (num <= cnt) {
    return;
  }
  int t = 0;
  for (int i = 0; i < 6; ++i) {
    t += color[i];
  }
  if (step + t > depth) {
    return;
  }
  if (num ==  n * n) {
    succ = 1;
    ans = step;
    return;
  }
  for (int i = 0; i < 6; ++i) {
    if (i == c) {
      continue;
    }
    for (int j = 1; j <= num; ++j) {
      mp[tt.xx[j].x][tt.xx[j].y] = i;
    }
    dfs(i, num, step + 1);
    for (int j = 1; j <= num; ++j) {
      mp[tt.xx[j].x][tt.xx[j].y] = c;
    }
  }
  return;
}

void ida()
{
  succ = 0;
  depth = 1;
  while (!succ) {
    //printf("%d\n", depth);
    dfs(mp[1][1], 0, 0);
    depth++;
  }
  return;
}
int main()
{
  while (scanf("%d", &n) && n) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        scanf("%d", &mp[i][j]);
      }
    }
    ans = inf;
    ida();
    printf("%d\n", ans);
  }
  return 0;
}