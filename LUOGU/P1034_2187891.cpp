#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>

using namespace std;

int n, k;
int ans;
int bel[55];
const int inf = 0x3f3f3f3f;
struct point
{
  int x, y;
} pts[55];
struct mat
{
  int u, d, l, r;
} squ[5];

void input()
{
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &pts[i].x, &pts[i].y);
  }
  return;
}

inline int siz(int x)
{
  return (squ[x].u - squ[x].d) * (squ[x].r - squ[x].l);
}

inline bool cross(int l1, int r1, int l2, int r2)
{
  return (l2 <= r1 && r2 >= r1) || (l2 <= l1 && r2 >= l1) || (l1 >= l2 && r1 <= r2) || (l1 <= l2 && r2 <= r1) || (l1 <= l2 && r1 >= l2) || (l2 <= l1 && r2 >= l1);
}

bool cover(mat a, mat b)
{
  return (cross(a.l, a.r, b.l, b.r) && cross(a.d, a.u, b.d, b.u));
}

void dfs(int x)
{
  //printf("%d\n",x);
  for (int i = 1; i <= k; ++i) {
    for (int j = 1; j <= k; ++j) {
      if (i != j && squ[i].u != -1000 && squ[j].u != -1000 && cover(squ[i], squ[j])) {
        //printf("%d %d\n", squ[i].u, squ[j].u);
        //puts("stop");
        return;
      }
    }
  }

  if (x == n) {
    int tot = 0;
    if (cover(squ[1], squ[2])) {
      return;
    }
    for (int i = 1; i <= k; ++i) {
      //printf("u=%d d=%d l=%d r=%d\n", squ[i].u, squ[i].d, squ[i].l, squ[i].r);
      tot += siz(i);
    }
    //putchar('\n');
    ans = min(ans, tot);
    return;
  }

  int tot = 0;
  for (int i = 1; i <= k; ++i) {
    tot += siz(i);
  }
  if (tot >= ans) {
    return;
  }

  int now = x + 1;
  for (int i = 1; i <= k; ++i) {
    mat t = squ[i];
    if (squ[i].u == -1000) {
      squ[i].u = squ[i].d = pts[now].y;
      squ[i].l = squ[i].r = pts[now].x;
    } else {
      squ[i].u = max(squ[i].u, pts[now].y);
      squ[i].d = min(squ[i].d, pts[now].y);
      squ[i].l = min(squ[i].l, pts[now].x);
      squ[i].r = max(squ[i].r, pts[now].x);
    }
    dfs(now);
    squ[i] = t;
  }
  return;
}

void solve()
{
  ans = inf;
  for (int i = 1; i <= k; ++i) {
    squ[i].u = squ[i].d = squ[i].l = squ[i].r = -1000;
  }
  dfs(0);
  printf("%d", ans);
  return;
}

int main()
{
  input();
  solve();
  return 0;
}

/*
10
3
-3 3
-3 1
1 1
2 2
3 3
4 5
6 3
4 1
4 -4
4 -2
*/
