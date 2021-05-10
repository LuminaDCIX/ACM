// luogu-judger-enable-o2
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

const int N = 200000 + 5;
const int LOG = 19;
const int MAX = 19260817;

int nxtr[N], nxtl[N];

int n, m;
int a[N];

void init() {
  stack <pair <int, int> > stk;
  for (int i = 1; i <= n; ++i) {
    while (!stk.empty() && stk.top().first < a[i]) {
      nxtr[stk.top().second] = i;
      stk.pop();
    }
    stk.push(make_pair(a[i], i));
  }
  while (!stk.empty()) {
    nxtr[stk.top().second] = n + 1;
    stk.pop();
  }
  for (int i = n; i >= 1; --i) {
    while (!stk.empty() && stk.top().first < a[i]) {
      nxtl[stk.top().second] = i;
      stk.pop();
    }
    stk.push(make_pair(a[i], i));
  }
  while (!stk.empty()) {
    nxtl[stk.top().second] = 0;
    stk.pop();
  }
}

int pos[N];
int ed[N];
vector <pair <int, int> > v[N];
vector <int> val[N];

struct sgt {
  long long sum[MAX];
  long long tag[MAX];
  int lc[MAX], rc[MAX];
  int tot;
  int lst;

  int mod(int o, int ll, int rr, int l, int r, int vv) {
    int p = ++tot;
    lc[p] = lc[o];
    rc[p] = rc[o];
    sum[p] = sum[o];
    tag[p] = tag[o];
    if (ll >= l && rr <= r) {
      tag[p] += vv;
      sum[p] += (long long)(rr - ll + 1) * vv;
      return p;
    }
    int mid = (ll + rr) >> 1;
    if (l <= mid) {
      lc[p] = mod(lc[o], ll, mid, l, r, vv);
    }
    if (r > mid) {
      rc[p] = mod(rc[o], mid + 1, rr, l, r, vv);
    }
    sum[p] = sum[lc[p]] + sum[rc[p]] + (long long) (rr - ll + 1) * tag[p];
    return p;
  }
  
  int add(int l, int r, int vv) {
    lst = mod(lst, 1, n, l, r, vv);
    return lst;
  }

  long long get(int o1, int o2, int ll, int rr, int l, int r, long long stag) {
    if (ll >= l && rr <= r) {
      return sum[o2] - sum[o1] + (rr - ll + 1) * stag;
    }
    int mid = (ll + rr) >> 1;
    long long ans = 0;
    if (l <= mid) {
      ans += get(lc[o1], lc[o2], ll, mid, l, r, stag + tag[o2] - tag[o1]);
    }
    if (r > mid) {
      ans += get(rc[o1], rc[o2], mid + 1, rr, l, r, stag + tag[o2] - tag[o1]);
    }
    return ans;
  }

  long long qry(int l1, int r1, int l2, int r2) {
    long long ans = get(pos[l1], ed[r1], 1, n, l2, r2, 0);
    return ans;
  }
} s;

int p1, p2;

int main() {
  n = read();
  m = read();
  p1 = read(), p2 = read();
  for (int i = 1; i <= n; ++i) {
    a[i] = read();
  }
  init();
  for (int i = 1; i <= n; ++i) {
    if (nxtl[i] != 0 && nxtr[i] != n + 1) {
      v[nxtl[i]].push_back(make_pair(nxtr[i], nxtr[i]));
      val[nxtl[i]].push_back(p1);
    }
    if (nxtl[i] != 0) {
      v[nxtl[i]].push_back(make_pair(i + 1, nxtr[i] - 1));
      val[nxtl[i]].push_back(p2);
    }
    if (nxtr[i] != n + 1) {
      v[nxtr[i]].push_back(make_pair(nxtl[i] + 1, i - 1));
      val[nxtr[i]].push_back(p2);
    }
  }
  for (int i = 1; i <= n; ++i) {
    pos[i] = s.add(1, n, 0);
    for (int j = 0; j < (int) v[i].size(); ++j) {
      if (v[i][j].first <= v[i][j].second) {
        s.add(v[i][j].first, v[i][j].second, val[i][j]);
      }
    }
    ed[i] = s.lst;
  }
  while (m--) {
    int l = read();
    int r = read();
    printf("%lld\n", s.qry(l, r, l, r) + (long long) p1 * (r - l));
  }
  return 0;
}
