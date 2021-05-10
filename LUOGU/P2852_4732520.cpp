#include <map>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 20000 + 5;

int n;
int m;
int k;

int s[N];

int c[N];
int t0[N];
int t1[N];
int sa[N];

int rk[N];
int ht[N];

inline void build() {
  int *x = t0;
  int *y = t1;
  m = n;
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

inline bool judge(int x) {
  for (int i = 0; i < n; ++i) {
    int l = i;
    int r = i;
    while (r + 1 < n && ht[r + 1] >= x) {
      ++r;
    }
    if (r - l + 1 >= k) {
      return true;
    }
    i = r;
  }
  return false;
}

map <int, int> mp;


int main() {
  scanf("%d %d", &n, &k);
  vector <int> v;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &s[i]);
    v.push_back(s[i]);
  }
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
  int len = v.size();
  for (int i = 0; i < len; ++i) {
    mp[v[i]] = i + 1;
  }
  for (int i = 0; i < n; ++i) {
    s[i] = mp[s[i]];
  }
  build();
  // for (int i = 0; i < n; ++i) {
  //   cerr << ht[i] << " ";
  // }
  // cerr << endl;
  int ans = 0;
  int low = 0;
  int high = n;
  // cerr << k << endl;
  while (low <= high) {
    int mid = low + high >> 1;
    if (judge(mid)) {
      ans = mid;
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  printf("%d\n", ans);
  return 0;
}
