#include <stack>
#include <cstdio>
#include <cstring>
#include <algorithm>

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
  return x * f;
}

using namespace std;

const int N = 500 + 5;
const int MAX = 1000 + 5;

int n;
int tot;

struct rec {
  int x[2], y[2];
  int cnt;
  int siz;

  rec(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, int _cnt = 0) {
    x[0] = x1;
    x[1] = x2;
    y[0] = y1;
    y[1] = y2;
    cnt = _cnt;
  }
} r[MAX * MAX];

int lmin[MAX];
int rmin[MAX];

int len[MAX][MAX];
int sum[MAX][MAX];

int s[MAX][MAX];

int stk[1005];
int top;

inline void solvel(int i)
{
  top = 0;
  for (int j = 1000, h; j >= 0; --j) {
    h = len[i][j];
    while (top != 0 && len[i][stk[top - 1]] > h) {
      lmin[stk[top - 1]] = j;
      --top;
    }
    stk[top++] = j;
  }
  while (top != 0) {
    lmin[stk[top - 1]] = -1;
    --top;
  }
}

inline void solver(int i)
{
  top = 0;
  for (int j = 0, h; j <= 1000; ++j) {
    h = len[i][j];
    while (top != 0 && len[i][stk[top - 1]] > h) {
      rmin[stk[top - 1]] = j;
      --top;
    }
    stk[top++] = j;
  }
  while (top != 0) {
    rmin[stk[top - 1]] = -1;
    --top;
  }
}

inline int getcnt(rec r) {
  return sum[r.x[1]][r.y[1]] - sum[r.x[1]][r.y[0] - 1] - sum[r.x[0] - 1][r.y[1]] + sum[r.x[0] - 1][r.y[0] - 1];
}

inline int getcnt(int x0, int y0, int x1, int y1) {
  return sum[x1][y1] - sum[x1][y0 - 1] - sum[x0 - 1][y1] + sum[x0 - 1][y0 - 1];
}

inline int cutu(int x0, int y0, int x1, int y1)
{
  //printf("(%d, %d) (%d, %d)\n", x0, y0, x1, y1);
  int low = x0;
  int high = x1;
  int ret = -1;
  while (low <= high) {
    int mid = low + high >> 1;
    if (!getcnt(x0, y0, mid, y1)) {
      ret = mid;
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return ret == -1 ? x0 : ret + 1;
}

inline int cutd(int x0, int y0, int x1, int y1)
{
  int low = x0;
  int high = x1;
  int ret = -1;
  while (low <= high) {
    int mid = low + high >> 1;
    if (!getcnt(mid, y0, x1, y1)) {
      ret = mid;
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return ret == -1 ? x1 : ret - 1;
}

inline int cutl(int x0, int y0, int x1, int y1)
{
  int low = y0;
  int high = y1;
  int ret = -1;
  while (low <= high) {
    int mid = low + high >> 1;
    if (!getcnt(x0, y0, x1, mid)) {
      ret = mid;
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return ret == -1 ? y0: ret + 1;
}

inline int cutr(int x0, int y0, int x1, int y1)
{
  int low = y0;
  int high = y1;
  int ret = -1;
  while (low <= high) {
    int mid = low + high >> 1;
    if (!getcnt(x0, mid, x1, y1)) {
      ret = mid;
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return ret == -1 ? y1 : ret - 1;
}

int main()
{
  n = read();
  char c[3];
  for (int i = 0, x, y; i < n; ++i) {
    x = read();
    y = read();
    scanf("%s", c);
    if (c[0] == 'H') {
      s[x][y] = 1;
    } else {
      s[x][y] = -1;
    }
  }
  for (int i = 0; i <= 1000; ++i) {
    for (int j = 0; j <= 1000; ++j) {
      if (s[i][j] == -1) {
	len[i][j] = 0;
	continue;
      }
      len[i][j] = len[i - 1][j] + 1;
    }
  }
  for (int i = 0; i <= 1000; ++i) {
    for (int j = 0; j <= 1000; ++j) {
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (s[i][j] == 1);
    }
  }
  for (int i = 0; i <= 1000; ++i) {
    solvel(i);
    solver(i);
    for (int j = 0; j <= 1000; ++j) {
      r[tot++] = rec(i - len[i][j] + 1, lmin[j] + 1, i, rmin[j] - 1);
      //printf("(%d, %d) (%d, %d)\n", i - len[i][j] + 1, lmin[j] + 1, i, rmin[j] - 1);
      r[tot - 1].cnt = getcnt(r[tot - 1]);
    }
  }
  int ans = 0;
		
  for (int i = 0; i < tot; ++i) {
    ans = max(ans, r[i].cnt);
  }
  printf("%d\n", ans);

  int siz = N * N;
  for (int i = 0; i < tot; ++i) {
    if (i && r[i].x[0] == r[i - 1].x[0] && r[i].x[1] == r[i - 1].x[1] && r[i].y[1] == r[i - 1].y[1] && r[i].y[0] == r[i - 1].y[0]) {
      continue;
    }
    if (r[i].cnt != ans) {
      continue;
    }
    int u = cutu(r[i].x[0], r[i].y[0], r[i].x[1], r[i].y[1]);
    int d = cutd(r[i].x[0], r[i].y[0], r[i].x[1], r[i].y[1]);
    int l = cutl(r[i].x[0], r[i].y[0], r[i].x[1], r[i].y[1]);
    int rgt = cutr(r[i].x[0], r[i].y[0], r[i].x[1], r[i].y[1]);
    //    printf("%d %d %d %d\n", u, d, l, rgt);
    siz = min((d - u) * (rgt - l), siz);
  }
  printf("%d\n", siz);
  return 0;
}
