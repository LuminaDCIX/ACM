// luogu-judger-enable-o2
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 500 + 5;
const double eps = 1e-10;

int n;
int m;

inline int read() {
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

int deg[N];

double mat[N][N];

vector <int> g[N];

int sgn(double t) {
  if (abs(t) <= eps) {
    return 0;
  }
  else return t < 0 ? -1 : 1;
}

void build() {
  mat[0][n] = -1;
  for (int i = 0; i < n - 1; ++i) {
    mat[i][i] = -1;
    for (int j = 0; j < (int) g[i].size(); ++j) {
      int v = g[i][j];
      if (v == n - 1) {
	continue;
      }
      mat[i][v] = 1.0 / deg[v];
    }
  }
  mat[n - 1][n - 1] = -1;
  for (int j = 0; j < (int) g[n - 1].size(); ++j) {
    int v = g[n - 1][j];
    mat[n - 1][v] = 1.0 / deg[v];
  }
}

double f[N];

void gaussJordan() {
  for (int i = 0; i < n; ++i) {
    int r = i;
    for (int j = i; j < n; ++j) {
      if (abs(mat[j][i]) > abs(mat[r][i])) {
	r = j;
      }
    }
    for (int j = i; j <= n; ++j) {
      swap(mat[r][j], mat[i][j]);
    }
    for (int j = n; j >= i; --j) {
      mat[i][j] /= mat[i][i];
    }
    for (int j = 0; j < n; ++j) {
      if (sgn(mat[j][i]) == 0 || j == i) {
	continue;
      }
      double t = mat[j][i];
      for (int k = i; k <= n; ++k) {
	mat[j][k] -= mat[i][k] * t;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    f[i] = mat[i][n];
  }
}

struct node {
  int u;
  int v;
  double f;

  bool operator < (const node a) const {
    return f > a.f;
  }
} p[N * N];

int main() {
  n = read();
  m = read();
  for (int i = 0; i < m; ++i) {
    int u = read() - 1;
    int v = read() - 1;
    ++deg[u];
    ++deg[v];
    g[u].push_back(v);
    g[v].push_back(u);
    p[i].u = u;
    p[i].v = v;
  }
  build();
  gaussJordan();
  for (int i = 0; i < m; ++i) {
    int u = p[i].u;
    int v = p[i].v;
    if (u != n - 1) {
      p[i].f += 1.0 / deg[u] * f[u];
    }
    if (v != n - 1) {
      p[i].f += 1.0 / deg[v] * f[v];
    }
  }
  sort(p, p + m);
  double ans = 0;
  for (int i = 0; i < m; ++i) {
    ans = ans + p[i].f * (i + 1);
  }
  printf("%.3f\n", ans);
  return 0;
}
