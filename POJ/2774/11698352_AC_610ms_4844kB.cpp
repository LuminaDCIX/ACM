#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100000 + 5;
const int MAX = 200000 + 5;

int n;

char s[MAX];

int c[MAX];
int t0[MAX];
int t1[MAX];
int sa[MAX];

int rk[MAX];
int ht[MAX];

char str[N];

int n0;
int n1;

inline void build() {
  n = n0 + n1 + 1;
  int *x = t0;
  int *y = t1;
  int m = 256;
  s[n++] = 0;
  for (int i = 0; i < n; ++i) {
    x[i] = s[i];
    ++c[s[i]];
  }
  for (int i = 1; i < m; ++i) {
    c[i] += c[i - 1];
  }
  for (int i = n - 1; i >= 0; --i) {
    int t = --c[x[i]];
    sa[t] = i;
  }
  for (int k = 1; k <= n; k <<= 1) {
    int p = 0;
    for (int i = n - k; i < n; ++i) {
      y[p++] = i;
    }
    for (int i = 0; i < n; ++i) {
      if (sa[i] >= k) {
        y[p++] = sa[i] - k;
      }
    }
    for (int i = 0; i < m; ++i) {
      c[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
      ++c[x[y[i]]];
    }
    for (int i = 1; i < m; ++i) {
      c[i] += c[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
      int t = --c[x[y[i]]];
      sa[t] = y[i];
    }
    p = 1;
    swap(x, y);
    x[sa[0]] = 0;
    for (int i = 1; i < n; ++i) {
      if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) {
        x[sa[i]] = p - 1;
      } else {
        x[sa[i]] = p++;
      }
    }
    if (p >= n) {
      break;
    }
    m = p;
  }

  --n;
  for (int i = 0; i < n; ++i) {
    sa[i] = sa[i + 1];
  }
  for (int i = 0; i < n; ++i) {
    rk[sa[i]] = i;
  }
  int k = 0;
  for (int i = 0; i < n; ++i) {
    if (k) {
      --k;
    }
    if (rk[i] == 0) {
      k = 0;
      continue;
    }
    int j = sa[rk[i] - 1];
    while (s[i + k] == s[j + k]) {
      ++k;
    }
    ht[rk[i]] = k;
  }
}

int main() {
  scanf("%s", str);
  n0 = strlen(str);
  memcpy(s, str, sizeof(str));
  scanf("%s", str);
  n1 = strlen(str);
  s[n0] = '#';
  memcpy(s + n0 + 1, str, sizeof(str));

  build();

  int mx = 0;
  for (int i = 1; i < n; ++i) {
    if ((sa[i] < n0 && sa[i - 1] > n0) || (sa[i] > n0 && sa[i - 1] < n0)) {
      mx = max(mx, ht[i]);
    }
  }
  printf("%d\n", mx);
  return 0;
}
