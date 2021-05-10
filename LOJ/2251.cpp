#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int MAX = 31500005;
const int P = 998244353;

int read() {
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

int n;

int add(int a, int b) {
  return (a += b) >= P ? a - P : a;
}
int sub(int a, int b) {
  return (a -= b) < 0 ? a + P : a;
}
int mul(int a, int b) {
  return (long long) a * b % P;
}
int mexp(int a, int x) {
  int ret = 1;
  while (x) {
    if (x & 1) {
      ret = mul(ret, a);
    }
    a = mul(a, a);
    x >>= 1;
  }
  return ret;
}

struct sgt {
  int ta[MAX], tm[MAX];
  int lc[MAX], rc[MAX];

  int nwnode() {
    static int tot = 0;
    ++tot;
    ta[tot] = 0;
    tm[tot] = 1;
    return tot;
  }

  void set(int o, int ftm, int fta) {
    tm[o] = mul(tm[o], ftm);
    ta[o] = add(mul(ta[o], ftm), fta);
  }

  int gc(int &o) {
    return o == 0 ? o = nwnode() : o;
  }
  
  void down(int o) {
    if (tm[o] == 1 && ta[o] == 0) {
      return;
    }
    
    set(gc(lc[o]), tm[o], ta[o]);
    set(gc(rc[o]), tm[o], ta[o]);
    tm[o] = 1;
    ta[o] = 0;
  }

  void mod(int o, int ll, int rr, int l, int r, int m, int a) {
    if (ll != rr) {
      down(o);
    }
    if (ll >= l && rr <= r) {
      set(o, m, a);
      return;
    }
    int mid = (ll + rr) >> 1;
    if (l <= mid) {
      mod(gc(lc[o]), ll, mid, l, r, m, a);
    }
    if (r > mid) {
      mod(gc(rc[o]), mid + 1, rr, l, r, m, a);
    }
  }

  pair <int, int> qry(int o, int ll, int rr, int p) {
    if (o == 0) {
      return make_pair(1, 0);
    }
    if (ll != rr) {
      down(o);
    }
    if (ll == rr) {
      return make_pair(tm[o], ta[o]);
    }
    int mid = (ll + rr) >> 1;
    if (p <= mid) {
      return qry(lc[o], ll, mid, p);
    } else {
      return qry(rc[o], mid + 1, rr, p);
    }       
  }
} s;

int root[4 * N + 5];

void mod(int o, int ll, int rr, int l, int r, int pl, int pr, int mm, int aa) {
  if (ll >= l && rr <= r) {
    if (!root[o]) {
      root[o] = s.nwnode();
    }
    s.mod(root[o], 1, n, pl, pr, mm, aa);
    return;
  }
  int mid = (ll +rr) >> 1;
  if (l <= mid) {
    mod(o * 2, ll, mid, l, r, pl, pr, mm, aa);
  }
  if (r > mid) {
    mod(o * 2 + 1, mid + 1, rr, l, r, pl, pr, mm, aa);
  }
}

pair <int, int> qry(int o, int ll, int rr, int x, int y) {
  if (ll == rr) {
    return s.qry(root[o], 1, n, y);
  }
  int mid = (ll + rr) >> 1;
  pair <int, int> a;
  if (x <= mid) {
    a = qry(o * 2, ll, mid, x, y);
  }
  if (x > mid) {
    a = qry(o * 2 + 1, mid + 1, rr, x, y);
  }
  pair <int, int> b = s.qry(root[o], 1, n, y);
  a.first = mul(b.first, a.first);
  a.second = add(mul(b.first, a.second), b.second);
  return a;
}

int t;

void solve(int l, int r) {
  int p = 1;
  p = mul(p, mexp(r - l + 1, P - 2));
  if (l - 1 >= 1) {
    mod(1, 1, n, 1, l - 1, l, r, sub(1, mul(2, p)), p);
    s.mod(t, 1, n, 1, l - 1, sub(0, 1), 1);
  }
  if (r + 1 <= n) {
    mod(1, 1, n, l, r, r + 1, n, sub(1, mul(2, p)), p);
    s.mod(t, 1, n, r + 1, n, sub(0, 1), 1);
  }
  if (l != r) {
    mod(1, 1, n, l, r, l, r, sub(1, mul(4, p)), mul(2, p));
    s.mod(t, 1, n, l, r, sub(mul(2, p), 1), sub(1, p));
  }
}

int main() {
  // cerr << sizeof(s.lc) * 4 / 1000 / 1000 << endl;
  n = read();
  int m = read();
  t = s.nwnode();
  while (m--) {
    int op = read();
    int l = read(), r = read();
    if (op == 1) {
      solve(l, r);
    } else {
      // cerr << ++tot << " " << l << " " << r << endl;
      if (l == 1) {
        pair <int, int> ans = s.qry(t, 1, n, r);
        printf("%d\n", add(ans.first, ans.second));
      } else {
        --l;
        pair <int, int> ans = qry(1, 1, n, l, r);
        printf("%d\n", add(ans.first, ans.second));
      }
    }
  }
  return 0;
}
