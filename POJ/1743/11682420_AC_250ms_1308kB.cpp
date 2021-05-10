#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 20000 + 5;

int n;
int m;

int a[N];
int s[N];

int c[N];
int t0[N];
int t1[N];
int sa[N];

inline void build() {
  int *x = t0;
  int *y = t1;
  m = 300;
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
  for (int i = 0; i < n - 1; ++i) {
    sa[i] = sa[i + 1];
  }
  --n;
}

int rk[N];
int ht[N];

inline void init() {
  for (int i = 0; i < n; ++i) {
    rk[sa[i]] = i;
  }
  int k = 0;
  for (int i = 0; i < n - 1; ++i) {
    if (k) {
      --k;
    }
    int j = sa[rk[i] - 1];
    while (s[i + k] == s[j + k]) {
      ++k;
    }
    ht[rk[i]] = k;
  }
}

inline bool judge(int x) {
  for (int i = 1; i < n; ++i) {
    int l = i;
    int r = i;
    int mn = sa[i];
    int mx = sa[i];
    while (r + 1 < n && ht[r + 1] >= x) {
      ++r;
      mn = min(mn, sa[r]);
      mx = max(mx, sa[r]);
    }
    if (mx - mn > x) {
      return true;
    }
    i = r;
  }
  return false;
}

inline int solve() {
  int low = 0;
  int high = n;
  int ans = 0;
  while (low <= high) {
    int mid = low + high >> 1;
    if (judge(mid)) {
      ans = mid;
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return ans;
}

int main() {
  while (scanf("%d", &n) && n) {
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
    }
    if (n == 1) {
      printf("%d\n", 0);
      continue;
    }
    
    --n;
    for (int i = 0; i < n; ++i) {
      s[i] = a[i + 1] - a[i] + 88;
    }
    build();
    init();
    int k = solve();
    printf("%d\n", k + 1 >= 5 ? k + 1 : 0);
  }
  return 0;
}
