// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int MAX = 1e6 + 6;
const int LOG = 23;

inline int read() {
  int f = 1;
  int x = 0;
  char ch =  getchar();
  while (ch < '0' || ch > '9') {
    f = (ch == '-') ? -1 :1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return f * x;
}

int n;;
int a[N], mx;
int s[N];

struct bit {
  int t[MAX];

  void clear() {
    memset(t, 0, sizeof(t));
  }

  void add(int x) {
    ++x;
    for (; x <= mx + 1 ;x += x & -x) {
      t[x] += 1;
    }
  }

  int sum(int x) {
    ++x;
    int ret = 0;
    for (; x >= 1; x -= x & -x) {
      ret += t[x];
    }
    return ret;
  }
} z, o;

int msk[LOG];

int main() {
  n = read();
  ++n;
  for (int i = 0; i < LOG; ++i) {
    msk[i] = (1 << (i + 1)) - 1;
  }
  for (int i = 2; i <= n; ++i) {
    a[i] = read();
    s[i] = s[i - 1] + a[i];
  }
  mx = s[n];
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (s[i] & 1) {
      ans ^= z.sum(0) & 1;
      o.add(0);
    } else {
      ans ^= o.sum(0) & 1;
      z.add(0);
    }
  }
  for (int i = 1; i < LOG; ++i) {
    z.clear();
    o.clear();
    long long nw = 0;
    int nb = 1 << i;
    for (int j = 1; j <= n; ++j) {
      if (s[j] & nb) {
        nw += o.sum(mx) - o.sum(s[j] & (msk[i - 1]));
        nw += z.sum(s[j] & msk[i - 1]);
        o.add(s[j] & msk[i - 1]);
      } else {
        nw += o.sum(s[j] & msk[i - 1]);
        nw += z.sum(mx) - z.sum(s[j] & msk[i - 1]);
        z.add(s[j] & msk[i - 1]);
      }
    }
    if (nw & 1) {
      ans |= nb;
    }
  }
  printf("%d\n", ans);
  return 0;
}
