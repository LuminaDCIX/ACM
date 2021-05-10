#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline int read() {
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 20;
const int MAX = (1 << N) + 5;

int n;

long long f[MAX];

int h[N];
int w[N];
int c[N];

inline long long cnt(int s, int w[]) {
  long long ret = 0;
  for (int i = 0; i < n; ++i) {
    if (s & (1 << i)) {
      ret += w[i];
    }
  }
  return ret;
}

int tar;

inline int num(int s) {
  int ret = 0;
  while (s) {
    ++ret;
    s -= s & -s;
  }
  return ret;
}

int main() {
  n = read();
  tar = read();
  for (int i = 0; i < n; ++i) {
    h[i] = read();
    w[i] = read();
    c[i] = read();
  }
  long long ans = -1e9;
  memset(f, 0xcfcf, sizeof(f));
  f[0] = 1e9;
  int lim = (1 << n);
  for (int s = 0; s < lim; ++s) {
    long long sum = cnt(s, w);
    for (int i = 0; i < n; ++i) {
      if (s & (1 << i)) {
        continue;
      }
      if (sum > c[i]) {
        continue;
      }
      f[s | (1 << i)] = max(f[s | (1 << i)], min(f[s], c[i] - sum));
    }
    if (cnt(s, h) >= tar) {
      ans = max(ans, f[s]);
    }
  }
  if (ans == -1e9) {
    puts("Mark is too tall");
    return 0;
  }
  printf("%lld\n", ans);
  return 0;
}
