// luogu-judger-enable-o2
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 50000 + 5;

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

int n;
long long l;

long long dp[N];

long long sum[N];
long long g[N];
long long c[N];

long long F(int k) {
  long long ret = g[k] * g[k];
  ret += 2 * l * g[k];
  ret += dp[k];
  return ret;
}

long long X(int x) {
  return 2 * g[x];
}

double slope(int i, int j) {
  return (double) (F(i) - F(j)) / (X(i) - X(j));
}

int que[N];

int main() {
  n = read();
  l = read() + 1;
  for (int i = 1; i <= n; ++i) {
    c[i] = read();
  }
  for (int i = 1; i <= n; ++i) {
    sum[i] = sum[i - 1] + c[i];
  }
  for (int i = 1; i <= n; ++i) {
    g[i] = sum[i] + i;
  }
  dp[0] = 0;
  int h = 0;
  int t = 0;
  que[t++] = 0;
  for (int i = 1; i <= n; ++i) {
    while (h + 1 < t && slope(que[h], que[h + 1]) <= g[i]) {
      ++h;
    }
    int k = que[h];
    dp[i] = dp[k] + (g[i] - g[k] - l) * (g[i] - g[k] - l);
    while (h + 1 < t && slope(que[t - 2], que[t - 1]) >= slope(que[t - 1], i)) {
      --t;
    }
    que[t++] = i;
  }
  printf("%lld\n", dp[n]);
  return 0;
}
