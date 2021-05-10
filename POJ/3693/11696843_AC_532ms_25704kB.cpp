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

struct suffix_array {
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

};

suffix_array pre;
suffix_array suf;

int mx = 0;
int cur;

int mn[N][LOG];

inline void init_rk() {
  for (int i = 0; i < n; ++i) {
    mn[i][0] = suf.rk[i];
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

inline int query_rk(int l, int r) {
  int k = log(r - l + 1) / log(2);
  return min(mn[l][k], mn[r - (1 << k) + 1][k]);
}

int main() {
  int kase = 0;
  while (true) {
    scanf("%s", s);
    if (s[0] == '#') {
      return 0;
    }
    n = strlen(s);
    
    memcpy(suf.s, s, sizeof(s));
    suf.build();
    suf.init_st();
    reverse(s, s + n);
    memcpy(pre.s, s, sizeof(s));
    pre.build();
    pre.init_st();
    reverse(s, s + n);

    init_rk();

    mx = 0;
    int ans_len = 0;
    for (int l = 1; l <= n; ++l) {
      for (int i = 0; (i + 1) * l < n; ++i) {
        int p = i * l;
        int q = (i + 1) * l;
        if (s[p] != s[q]) {
          continue;
        }
        int suf_max = suf.query(suf.rk[p], suf.rk[q]);
        int pre_max = pre.query(pre.rk[n - p - 1], pre.rk[n - q - 1]);
        if (p - pre_max + 1 <= (i - 1) * l) {
          pre_max = l;
        }
        int low = max((i - 1) * l + 1, p - pre_max + 1);
        int t = (suf_max + pre_max - 1) / l + 1;
        int t0 = l * t - l - 1;
        int high = min((p + suf_max - 1 - t0), p);
        if (high < low) {
          continue;
        }
        // if (low > high || low > p || low <= (i - 1) * l) {
        //   while (1);
        // }
        int mn_rk = suf.sa[query_rk(low, high)];

        // if (p == 0 && q == 4) {
        //   cerr << low << " " << high << endl;
        //   cerr << "t = " << t << endl;
        //   cerr << "mn_rk = " << mn_rk << endl;
        //   cerr << pre_max << " " << suf_max << endl;
        // }
        if (t == mx) {
          if (suf.rk[cur] > suf.rk[mn_rk]) {
            // if (mn_rk == 4) {
            //   cerr << "modified when " << cur << endl;
            //   cerr << p << " " << q << endl;
            //   cerr << suf_max << " " << pre_max << endl;
            //   cerr << low << " " << high << endl;
            //   cerr << t0 << endl;
            //   cerr << p + suf_max - 1 - t0 << endl;
            // }
            cur = mn_rk;
            ans_len = t * l;
          }
        } else if (t > mx) {
          mx = t;
          cur = mn_rk;
          ans_len = t * l;
        }
      }
     
    }
    // cerr << mx << endl;
    // cerr << cur << endl;
    printf("Case %d: ", ++kase);
    for (int i = cur; i < cur + ans_len; ++i) {
      putchar(s[i]);
    }
    puts("");
  }
  return 0;
}
