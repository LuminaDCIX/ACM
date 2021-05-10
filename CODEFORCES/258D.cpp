#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int n;
int m;
int a[N];

double f[N][N];

int x[N];
int y[N];

inline int read() {
  int x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x;
}

int main() {
  n = read();
  m = read();
  for (int i = 0; i < n; ++i) {
    a[i] = read();
  }
  for (int i = 0; i < m; ++i) {
    x[i] = read() - 1;
    y[i] = read() - 1;
    if (x[i] > y[i]) {
      swap(x[i], y[i]);
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (a[i] > a[j]) {
	f[i][j] = 1;
      } else {
	f[i][j] = 0;
      }
    }
  }
 
  for (int i = 0; i < m; ++i) {
    int a = x[i];
    int b = y[i];
    f[a][b] = 0.5;
    for (int j = 0; j < a; ++j) {
      double t = 0.5 * (f[j][a] + f[j][b]);
      f[j][a] = t;
      f[j][b] = t;
    }
    for (int j = b + 1; j < n; ++j) {
      double t = 0.5 * (f[b][j] + f[a][j]);
      f[b][j] = t;
      f[a][j] = t;
    }
    for (int j = a + 1; j < b; ++j) {
      double t = f[j][b];
      f[j][b] = 0.5 * (f[j][b] + 1 - f[a][j]);
      f[a][j] = 0.5 * (f[a][j] + 1 - t);
    }
  }
  double ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      ans += f[i][j];
    }
  }
  printf("%.7f\n", ans);;
  return 0;
}

