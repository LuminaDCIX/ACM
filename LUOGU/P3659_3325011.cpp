#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
typedef long long ll;

const int N = 100;

int n, t;
int val[N][N];

int d1x[] = {0, 0, 1, -1};
int d1y[] = {-1, 1, 0, 0};

inline int read() 
{
  int f = 1, x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    f = (ch == '-') ? -1 : 1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}

ll dist[N][N][3];
bool vis[N][N][3];

struct node {
  int x;
  int y;
  int p;
  ll val;

  bool operator < (const node &rhs) const {
    return val > rhs.val;
  }

  node(int _x, int _y, int _p, int _val) {
    x = _x;
    y = _y;
    p = _p;
    val = _val;
  }
};

priority_queue <node> que;

inline bool judge(int x, int y) {
  return x >= 0 && x < n && y >= 0 && y < n;
}

inline ll dijkstra() 
{
  memset(dist, 0x3f3f, sizeof(dist));
  dist[0][0][0] = 0;
  que.push(node(0, 0, 0, 0));
  while (!que.empty()) {
    int x = que.top().x;
    int y = que.top().y;
    int p = que.top().p;
    if (x == n - 1 && y == n - 1) {
      return que.top().val;
    }
    que.pop();
    if (vis[x][y][p]) {
      continue;
    }
    int v = 0;
    int to = (p + 1) % 3;
    if (!to) {
      v = 1;
    }
    for (int i = 0; i < 4; ++i) {
      int dx = x + d1x[i];
      int dy = y + d1y[i];
      if (judge(dx, dy) && dist[dx][dy][to] > dist[x][y][p] + t + v * val[dx][dy]) {
	dist[dx][dy][to] = dist[x][y][p] + t + v * val[dx][dy];
	que.push(node(dx, dy, to, dist[dx][dy][to]));
      }
    }
  }
}

int main()
{
  n = read();
  t = read();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      val[i][j] = read();
    }
  }
  printf("%lld\n", dijkstra());
  return 0;
}
