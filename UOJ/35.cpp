#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

char s[N];
int t[N];

struct suffix_array {
  int x[N], y[N], c[N];
  int sa[N], rk[N], ht[N];

  void build(int *s, int n, int m) {
    s[++n] = 0;
    for (int i = 1; i <= n; ++i) {
      x[i] = s[i];
      ++c[x[i]];
    }
    for (int i = 1; i <= m; ++i) {
      c[i] += c[i - 1];
    }
    for (int i = 1; i <= n; ++i) {
      sa[c[x[i]]--] = i;
    }
    for (int k = 1; k <= n; k <<= 1) {
      int p = 0;
      for (int i = n - k + 1; i <= n; ++i) {
        y[++p] = i;
      }
      for (int i = 1; i <= n; ++i) {
        if (sa[i] > k) {
          y[++p] = sa[i] - k;
        }
      }
      for (int i = 0; i <= m; ++i) {
        c[i] = 0;
      }
      for (int i = 1; i <= n; ++i) {
        ++c[x[i]];
      }
      for (int i = 1; i <= m; ++i) {
        c[i] += c[i - 1];
      }
      for (int i = n; i >= 1; --i) {
        sa[c[x[y[i]]]--] = y[i];
      }
      p = 1;
      swap(x, y);
      x[sa[1]] = 1;
      for (int i = 2; i <= n; ++i) {
        if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) {
          x[sa[i]] = p;
        } else {
          x[sa[i]] = ++p;
        }
      }
      if (p >= n) {
        break;
      }
      m = p;
    }
    --n;
    for (int i = 1; i <= n; ++i) {
      sa[i] = sa[i + 1];
    }
    for (int i = 1; i <= n; ++i) {
      rk[sa[i]] = i;
    }
    int k = 0;
    for (int i = 1; i <= n; ++i) {
      if (k) {
        --k;
      }
      if (rk[i] == 0) {
        k = 0;
      } else {
        int j = sa[rk[i] - 1];
        while (s[j + k] == s[i + k]) {
          ++k;
        }
      }
      ht[rk[i]] = k;
    }
  }
} h;

int main() {
  scanf("%s", s + 1);
  int n = strlen(s + 1);
  for (int i = 1; i <= n; ++i) {
    t[i] = s[i];
  }
  h.build(t, n, (int) 'z');
  for (int i = 1; i <= n; ++i) {
    printf("%d ", h.sa[i]);
  }
  puts("");
  for (int i = 2; i <= n; ++i) {
    printf("%d ", h.ht[i]);
  }
  puts("");
  return 0;
}
