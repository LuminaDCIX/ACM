#include <map>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100000 + 5;
const int LOG = 17;

int n;
int m;

char s[N];

int c[N];
int t0[N];
int t1[N];
int sa[N];

int rk[N];
int ht[N];

inline void build() {
  int *x = t0;
  int *y = t1;
  m = 256;
  s[n++] = 0;
  for (int i = 0; i < m; ++i) {
    c[i] = 0;
  }
  for (int i = 0; i < n; ++i) {
    x[i] = s[i];
    ++c[x[i]];
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

int mn[N][LOG];

inline void init_st() {
  for (int i = 0; i < n; ++i) {
    mn[i][0] = ht[i];
  }
  for (int k = 1; k < LOG; ++k) {
    for (int i = 0; i < n; ++i) {
      mn[i][k] = mn[i][k - 1];
      if (i + (1 << (k - 1)) < n) {
        mn[i][k] = min(mn[i][k], mn[i + (1 << (k - 1))][k - 1]);
      }
    }
  }
}

inline int query(int l, int r) {
  if (l > r) {
    swap(l, r);
  }
  ++l;
  int k = log(r - l + 1) / log(2);
  return min(mn[l][k], mn[r - (1 << k) + 1][k]);
}

int mx = 0;
int cur;

int main() {
  int kase = 0;
  while (true) {
    scanf("%s", s);
    if (s[0] == '#') {
      return 0;
    }
    n = strlen(s);
    build();
    init_st();
    mx = 0;
    int ans_len = 0;
    for (int l = 1; l <= n; ++l) {
      for (int i = 0; (i + 1) * l < n; ++i) {
        int p = i * l;
        int q = (i + 1) * l;
        if (s[p] != s[q]) {
          continue;
        }

        for (int j = 0; j < l; ++j) {
          int p0 = p - j;
          int q0 = q - j;
          if (p0 < 0 || s[p0] != s[q0]) {
            break;
          }
          int len = query(rk[p0], rk[q0]);
          int times = len / l + 1;
          if (times == mx) {
            if (rk[cur] > rk[p0]) {
              cur = p0;
              ans_len = times * l;
            }
          } else if (times > mx) {
            mx = times;
            cur = p0;
            ans_len = times * l;
          }
        }
      }
     
    }
    // cerr << mx << endl;
    printf("Case %d: ", ++kase);
    for (int i = cur; i < cur + ans_len; ++i) {
      putchar(s[i]);
    }
    puts("");
  }
  return 0;
}