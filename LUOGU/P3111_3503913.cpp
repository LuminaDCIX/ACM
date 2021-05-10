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

const int N = 100000 + 5;

int a[N];
int v[N];
long long len[N];

int n;
int t;

int main()
{
  n = read();
  t = read();
  for (int i = 0; i < n; ++i) {
    a[i] = read();
    v[i] = read();
    len[i] = a[i] + 1ll * v[i] * t;
  }
  int ans = n;
  for (int i = n - 2; i >= 0; --i) {
    if (len[i] >= len[i + 1]) {
      --ans;
      len[i] = len[i + 1];
    }
  }
  printf("%d\n", ans);
  return 0;
}
