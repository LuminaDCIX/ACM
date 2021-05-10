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

const int N = 100000 + 5;
const int MAX = N * 2 * 4 + 5;

int n, lim;
vector <pair <int, int> > v;
map <int, int> id;
map <int, int> pre;

struct sgt {
  long long sum[MAX];
  int siz[MAX];

  int kth(int o, int ll, int rr, int k) {
    if (ll == rr) {
      return ll;
    }
    int mid = (ll + rr) >> 1;
    int lc = o * 2;
    int rc = o * 2 + 1;
    if (siz[lc] >= k) {
      return kth(lc, ll, mid, k);
    } else {
      return kth(rc, mid + 1, rr, k - siz[lc]);
    }
  }

  pair <int, long long> qry(int o, int ll, int rr, int l, int r) {
    if (ll >= l && rr <= r) {
      return make_pair(siz[o], sum[o]);
    }
    int mid = (ll + rr) >> 1;
    int rsiz = 0;
    long long rsum = 0;
    if (l <= mid) {
      pair <int, long long> ret = qry(o << 1, ll, mid, l, r);
      rsiz += ret.first;
      rsum += ret.second;
    }
    if (r > mid) {
      pair <int, long long> ret = qry(o << 1 | 1, mid + 1, rr, l, r);
      rsiz += ret.first;
      rsum += ret.second;
    }
    return make_pair(rsiz, rsum);
  }

  void add(int o, int ll, int rr, int p, int v) {
    if (ll == rr) {
      siz[o] += v;
      sum[o] += pre[p] * v;
      return;
    }
    int mid = (ll + rr) >> 1;
    int lc = o << 1;
    int rc = o << 1 | 1;
    if (p <= mid) {
      add(lc, ll, mid, p, v);
    } else {
      add(rc, mid + 1, rr, p, v);
    }
    siz[o] = siz[lc] + siz[rc];
    sum[o] = sum[lc] + sum[rc];
  }

  long long getans() {
    if (siz[1] < 2) {
      return 0ll;
    }
    int mid = kth(1, 1, lim, siz[1] >> 1);
    long long ans = 0;
    pair <int, long long> t = qry(1, 1, lim, 1, mid);
    ans = (long long) pre[mid] * t.first - t.second;
    t = qry(1, 1, lim, mid, lim);
    ans += t.second - (long long) pre[mid] * t.first;
    return ans;
  }
} sl, sr;

struct node {
  int x, y, m;
  bool operator < (const node &rhs) const {
    return m < rhs.m;
  }
  node(int _x, int _y) {
    x = _x;
    y = _y;
    m = (x + y) >> 1;
  }
};

int main() {
  int k = read();
  int n = read();  
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    char s[3][3];
    int p[3];
    scanf("%s %d %s %d", s[1] + 1, &p[1], s[2] + 1, &p[2]);
    if (s[1][1] == s[2][1]) {
      ans += abs(p[1] - p[2]);
    } else {
      ++ans;
      v.push_back(make_pair(p[1], p[2]));
    }
  }
  if (k == 1) {
    vector <int> t;
    for (int i = 0; i < (int) v.size(); ++i) {
      t.push_back(v[i].first);
      t.push_back(v[i].second);
    }
    sort(t.begin(), t.end());
    if (t.size() != 0) {
      int mid = t[t.size() / 2];
      for (int i = 0; i < (int) t.size(); ++i) {
        ans += abs(mid - t[i]);
      }
    }
    printf("%lld\n", ans);
  } else {
    vector <int> t;
    for (int i = 0; i < (int) v.size(); ++i) {
      t.push_back(v[i].first);
      t.push_back(v[i].second);
    }
    sort(t.begin(), t.end());
    t.erase(unique(t.begin(), t.end()), t.end());
    lim = t.size();
    for (int i = 0; i < (int) t.size(); ++i) {
      id[t[i]] = i + 1;
      pre[i + 1] = t[i];
    }
    vector <node> nw;
    for (int i = 0; i < (int) v.size(); ++i) {
      nw.push_back(node(v[i].first, v[i].second));
      sr.add(1, 1, lim, id[v[i].first], 1);
      sr.add(1, 1, lim, id[v[i].second], 1);
    }
    sort(nw.begin(), nw.end());
    long long more = ans;
    ans = more + sl.getans() + sr.getans();
    for (int i = 0; i < (int) nw.size(); ++i) {
      sr.add(1, 1, lim, id[nw[i].x], -1);
      sr.add(1, 1, lim, id[nw[i].y], -1);
      sl.add(1, 1, lim, id[nw[i].x], 1);
      sl.add(1, 1, lim, id[nw[i].y], 1);
      ans = min(ans, more + sl.getans() + sr.getans());
    }
    printf("%lld\n", ans);
    
  }
  return 0;
}
