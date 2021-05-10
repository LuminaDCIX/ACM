#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

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
    x =  x * 10 + ch - '0';
    ch = getchar();
  }
  return f * x;
}

const int N = 300 + 5;

int n;
int cnt[N][N];

int x[N];
int y[N];

int tot;

int ans[N];

struct node {
  int x;
  int y;
  bool operator < (const node &rhs) {
    return x == rhs.x ? y < rhs.y : x < rhs.x;
  }
} t[N];

int main()
{
  n = read();
  for (int i = 0; i < n; ++i) {
    x[i] = read();
    y[i] = read();
    t[i].x = x[i];
    t[i].y = y[i];
  }
  sort(t, t + n);
  for (int i = 0; i < n; ++i) {
    x[i] = t[i].x;
    y[i] = t[i].y;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (x[j] == x[i]) {
	continue;
      }
      double k = 1.0 * (y[j] - y[i]) / (x[j] - x[i]);
      double b = y[i] - k * x[i];
      int mn = min(x[j], x[i]);
      int mx = max(x[j], x[i]);
      for (int l = 0; l < n; ++l) {
	if (i == l || j == l || !(x[l] <= mx && x[l] >= mn)) {
	  continue;
	}
	if (x[l] == mn) {
	  continue;
	}
	double c = k * x[l] + b;
	if (y[l] >= c) {
	  ++cnt[i][j];
	  ++cnt[j][i];
	}
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (x[j] == x[i]) {
	continue;
      }
      int mn = min(x[i], x[j]);
      int mx = max(x[i], x[j]);
      double k = 1.0 * (y[j] - y[i]) / (x[j] - x[i]);
      double b = y[i] - k * x[i];
      for (int l = 0; l < n; ++l) {
	if (l == i || l == j || !(x[l] >= mn && x[l] <= mx)) {
	  continue;
	}
	double bar = k * x[l] + b;

	if (x[j] == x[l]) {
	  if (y[l] < y[j]) {
	    continue;
	  }
	  ++ans[cnt[i][j] - cnt[i][l] - cnt[j][l] - 1];
	  continue;
	}

	if (x[i] == x[l]) {
	  if (y[l] < y[i]) {
	    continue;
	  }
	  ++ans[cnt[i][j] - cnt[i][l] - cnt[j][l]];
	  continue;
	}
	
	if (bar < y[l]) {
	  ++ans[cnt[i][j] - cnt[i][l] - cnt[j][l] - 1];
	  if (cnt[i][j] - cnt[i][l] - cnt[j][l] - 1 * (x[l] != x[i])< 0) {
	  }
	} else {
	  ++ans[cnt[i][l] + cnt[j][l] - cnt[i][j]];
	}
      }
    }
  }
  for (int i = 0; i < n - 2; ++i) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
