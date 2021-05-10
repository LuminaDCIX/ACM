#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>

using namespace std;

int n, m;
int bx, by, sx, sy, tx, ty;
int box[23][23];
int dx[] = { -1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

struct sit
{
  int x, y, p, w;
  int bx, by;
  bool operator < (const sit a) const
  {
    if (p == a.p) {
      return w > a.w;
    }
    return p > a.p;
  }
  sit(int _x = -1, int _y = 0, int _p = 0, int _w = 0, int _bx = 0, int _by = 0) {
    x = _x;
    y = _y;
    p = _p;
    w = _w;
    bx = _bx, by = _by;
    return;
  }
};

priority_queue <sit> que;
bool vis[23][23][23][23];
sit pre[23][23][23][23];
int bet[23][23][23][23][2];

bool better(sit a)
{
  if (a.p == bet[a.x][a.y][a.bx][a.by][0]) {
    return a.w < bet[a.x][a.y][a.bx][a.by][1];
  }
  return a.p < bet[a.x][a.y][a.bx][a.by][0];
}

void print(int x, int y, int bx, int by)
{
  bool is_push = 0;
  sit p = pre[x][y][bx][by];
  if (p.x != -1) {
    print(p.x, p.y, p.bx, p.by);
  }
  if (p.bx == x && p.by == y) {
    is_push = 1;
  }
  if (p.x - 1 == x && y == p.y) {
    if(is_push) {
      putchar('N');
    }
    else {
      putchar('n');
    }
  }
  if (p.x + 1 == x && y == p.y) {
    if (is_push) {
      putchar('S');
    }
    else {
      putchar('s');
    }
  }
  if (p.x == x && p.y - 1 == y) {
    if (is_push) {
      putchar('W');
    }
    else {
      putchar('w');
    }
  }
  if (p.x == x && p.y + 1 == y) {
    if (is_push) {
      putchar('E');
    }
    else {
      putchar('e');
    }
  }
  return;
}

bool bfs()
{
  sit t = sit(0, 0, 0, 0, 0, 0);
  t.x = sx;
  t.y = sy;
  t.bx = bx;
  t.by = by;
  t.w = t.p = 0;
  bet[t.x][t.y][t.bx][t.by][0] = 0;
  bet[t.x][t.y][t.bx][t.by][1] = 0;
  while (!que.empty()) {
    que.pop();
  }
  que.push(t);
  while (!que.empty()) {
    t = que.top();
    que.pop();
    if (t.x <= 0 || t.x > n || t.y <= 0 || t.y > m) {
      continue;
    }
    if (t.bx == tx && t.by == ty) {
      print(t.x, t.y, t.bx, t.by);
      return true;
    }
    for (int i = 0; i <= 3; ++i) {
      int xx = t.x + dx[i];
      int yy = t.y + dy[i];
      if (box[xx][yy]) {
        continue;
      }
      if (xx <= 0 || xx > n || yy <= 0 || yy > m || box[xx][yy]) {
        continue;
      }
      if (t.bx == xx && t.by == yy) {
        if (box[t.bx + dx[i]][t.by + dy[i]]) {
          continue;
        }
        else {
          sit p = sit(xx, yy, t.p + 1, t.w, t.bx + dx[i], t.by + dy[i]);
          if (better(p)) {
            que.push(p);
            pre[p.x][p.y][p.bx][p.by] = t;
            bet[p.x][p.y][p.bx][p.by][0] = p.p;
            bet[p.x][p.y][p.bx][p.by][1] = p.w;
          }
        }
      }
      else {
        sit p = sit(xx, yy, t.p, t.w + 1, t.bx, t.by);
        if (better(p)) {
          pre[p.x][p.y][p.bx][p.by] = t;
          bet[p.x][p.y][p.bx][p.by][0] = p.p;
          bet[p.x][p.y][p.bx][p.by][1] = p.w;
          que.push(p);
        }
      }
    }
  }
  return false;
}

void input()
{
  char t;
  for (int i = 1; i <= n; ++i) {
    while (getchar() != '\n');
    for (int j = 1; j <= m; ++j) {
      t = getchar();
      if (t == '#') {
        box[i][j] = 1;
        continue;
      }
      if (t == 'S') {
        sx = i;
        sy = j;
      }
      if (t == 'B') {
        bx = i;
        by = j;
      }
      if (t == 'T') {
        tx = i;
        ty = j;
      }
      box[i][j] = 0;
    }
  }
  return;
}
int kase = 0;
void solve()
{
  printf("Maze #%d\n", ++kase);
  if (!bfs()) {
    puts("Impossible.");
  }
  else {
    puts("");
  }
  puts("");
  return;
}

int main()
{
  while(scanf("%d%d", &n, &m) && n) {
    input();
    for (int i = 1; i <= 20; ++i) {
      for (int j = 1; j <= 20; ++j) {
        for (int m = 1; m <= 20; ++m) {
          for (int k = 1; k <= 20; ++k) {
            pre[i][j][k][m].x = -1;
            for (int l = 0; l < 2; ++l) {
              bet[i][j][k][m][l] = 1000000;
            }
          }
        }
      }
    }
    memset(vis, 0, sizeof(vis));
    solve();
  }
  return 0;
}
