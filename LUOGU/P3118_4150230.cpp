#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

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

const int N = 20;
const int MAX = (1 << 20) + 5;
const int MAXC = 2000 + 5;
const int inf = 0xcfcfcfcf;

int n;
int l;

int f[MAX];

int d[N];
int num[N];
int c[N][MAXC];

inline int cnt(int s) {
  int ret = 0;
  while (s) {
    ++ret; 
    s -= s & -s;
  }
  return ret;
}

inline int lbd(int i, int low, int high, int k) {
  int ret = high;
  --high;
  while (low <= high) { 
    int mid = low + high >> 1;
    if (c[i][mid] >= k) {
      high = mid - 1;
      ret = mid;
    } else {
      low = mid + 1;
    }
  }
  return ret;
}

int main() {
  n = read();
  l = read();
  for (int i = 0; i < n; ++i) {
    d[i] = read();
    num[i] = read();
    int k = num[i];
    for (int j = 0; j < k; ++j) {
      c[i][j] = read();
    }
  }
  memset(f, 0xcfcf, sizeof(f));
  for (int i = 0; i < n; ++i) {
    if (c[i][0] == 0) {
      f[1 << i] = max(f[1 << i], d[i]);
    }
  }
  int lim = (1 << n);
  int ans = 1e9;
  for (int s = 0; s < lim; ++s) {
    for (int i = 0; i < n; ++i) {
      if (f[s] == inf) {
        continue;
      }
      if (s & (1 << i)) {
        continue;
      }
      int k = lbd(i, 0, num[i], f[s]);
      if (c[i][k] > f[s]) {
        --k;
      }
      if (k == -1) {
        continue;
      }
      f[s | (1 << i)] = max(f[s | (1 << i)], c[i][k] + d[i]);
    }
    if (f[s] >= l) {
      ans = min(ans, __builtin_popcount(s));
    }
  }
  printf("%d\n", ans == 1e9 ? -1 : ans);
  return 0;
}
