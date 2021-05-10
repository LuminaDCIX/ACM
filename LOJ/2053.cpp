#include <bits/stdc++.h>

using namespace std;

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

const int N = 100000 + 5;

int n, m;

long long P;
char str[N];

long long pre[N];
int a[N];

int siz;

inline int blk(int x) {
  return (x - 1) / siz + 1;
}

struct query {
  int l, r, id;
  bool operator < (const query &rhs) const {
    return blk(l) == blk(rhs.l) ? r < rhs.r : l < rhs.l;
  }
} q[N];

long long ans[N];

long long nwans;

int cnt[N];

void add(int v, int o) {
  if (o == 1) {
    if (cnt[a[v]] > 0) {
      nwans += cnt[a[v]];
    }
    cnt[a[v]]++;
  } else {
    nwans -= cnt[a[v]] - 1;
    cnt[a[v]]--;
  }
}

map <long long, int> id;

namespace solve2 {
  long long sum[N];
  int siz[N];

  void solve() {
    for (int i = 1; i <= n; ++i) {
      int x = str[i] - '0';
      sum[i] = sum[i - 1] + (x % P == 0 ? i : 0);
      siz[i] = siz[i - 1] + (x % P == 0 ? 1 : 0);
    }
    while (m--) {
      int l = read();
      int r = read();
      printf("%lld\n", sum[r] - sum[l - 1] + (siz[r] - siz[l - 1]) * (-l + 1));
    }
  }
}
int main() {
  P = read();
  scanf("%s", str + 1);
  m = read();
  n = strlen(str + 1);
  if (P == 2 || P == 5) {
    solve2::solve();
    return 0;
  }
  siz = sqrt(n);
  pre[n] = str[n] - '0';
  int nw = 1;
  for (int i = n - 1; i >= 1; --i) {
    nw = (long long) nw * 10 % P;
    pre[i] = (pre[i + 1] + (long long) nw * (str[i] - '0')) % P;
  }
  ++n;
  {
    vector <long long> v;
    for (int i = 1; i <= n; ++i) {
      v.push_back(pre[i]);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()));
    for (int i = 0; i < (int) v.size(); ++i) {
      id[v[i]] = i + 1;
    }
    for (int i = 1; i <= n; ++i) {
      a[i] = id[pre[i]];
    }
  }
  for (int i = 1; i <= m; ++i) {
    q[i].l = read();
    q[i].r = read() + 1;
    q[i].id = i;
  }
  sort(q + 1, q + m + 1);
  int l = 1;
  int r = 0;
  for (int i = 1; i <= m; ++i) {
    while (r < q[i].r) {
      ++r;
      add(r, 1);
    }
    while (r > q[i].r) {
      add(r, -1);
      --r;
    }
    while (l < q[i].l) {
      add(l, -1);
      ++l;
    }
    while (l > q[i].l) {
      --l;
      add(l, 1);
    }
    ans[q[i].id] = nwans;
  }
  for (int i = 1; i <= m; ++i) {
    printf("%lld\n", ans[i]);
  }
  return 0;
}