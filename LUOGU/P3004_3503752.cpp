#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
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
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return f * x;
}

const int N = 5000 + 5;

int n;
int a[N];

int f[N];
int g[N];

int f1[N];
int g1[N];

int main()
{
  n = read();
  for (int i = 0; i < n; ++i) {
    a[i] = read();
  }
  for (int j = 0; j < n; ++j) {
    f[j] = a[j];
  }
  for (int len = 2; len <= n; ++len) {
    for (int l = 0; l < n; ++l) {
      int r = l + len - 1;
      if (r >= n) {
        break;
      }
      f1[l] = max(g[l] + a[r], g[l + 1] + a[l]);
      //g[l][r] = min(f[l][r - 1], f[l + 1][r]);
      if (g[l] + a[r] > g[l + 1] + a[l]) {
        g1[l] = f[l];
      } else {
        g1[l] = f[l + 1];
      }
      //      printf("f[%d][%d] = %d\n", l, r, f[l][r]);
      //      printf("g[%d][%d] = %d\n", l, r, g[l][r]);
    }
    memcpy(g, g1, sizeof(g));
    memcpy(f, f1, sizeof(f));
    memset(f1, 0, sizeof(f1));
    memset(g1, 0, sizeof(g1));
  }
  printf("%d\n", f[0]);
  return 0;
}
