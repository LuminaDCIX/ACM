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

const int N = 100 + 5;

const int P = 1e6 + 7;

struct st {
  int l, d, t;
  st (int _l, int _d, int _t) {
    l = _l;
    d = _d;
    t = _t;
  }
};

struct hash {
  vector <st> v[P];
  int siz;
  
  bool ins(st s) {
    int idx = s.d % P;
    for (int i = 0; i < (int) v[idx].size(); ++i) {
      if (v[idx][i].l == s.l && v[idx][i].d == s.d) {
        return false;
      }
    }
    v[idx].push_back(s);
    ++siz;
    return true;
  };
} h;

int mx;

void bfs() {
  queue <st> que;
  que.push(st(0, 1, 0));
  h.ins(st(0, 1, 0));
  while (!que.empty()) {
    
    st u = que.front();
    que.pop();
    ++u.t;
    st v = u;
    if ((long long)v.d * v.l > 1e8 || u.t >= mx) {
      continue;
    }

    ++v.l;
    if (h.ins(v)) {
      que.push(v);
    }
    v = u;
    if (v.l) {
      v.d *= v.l;
      if (h.ins(v)) {
        que.push(v);
      }
    }
  }
}

int dp[N][N];

int n, mc, m;
int a[N], w[N];

vector <pair <int, int> > v2, v;

const int MAX = 8000005;

int mn[MAX];

void init() {
  for (int i = 0; i < P; ++i) {
    for (int j = 0; j < (int) h.v[i].size(); ++j) {
      v2.push_back(make_pair(h.v[i][j].d, h.v[i][j].t + 1));
    }
  }
  v2.push_back(make_pair(0, 0));
  sort(v2.begin(), v2.end());
  v.push_back(v2[0]);
  for (int i = 1; i < (int) v2.size(); ++i) {
    if (v2[i].first != v2[i - 1].first) {
      v.push_back(v2[i]);
    }
  }
  mn[0] = v[0].second - v[0].first;
  for (int i = 1; i < (int) v.size(); ++i) {
    mn[i] = min(mn[i - 1], v[i].second - v[i].first);
  }
}

bool solve(int c) {
  int ptr = v.size() - 1;
  for (int i = 0; i < (int) v.size(); ++i) {
    while (ptr >= 0 && v[i].first + v[ptr].first > c) {
      --ptr;
    }
    if (ptr < 0) {
      return false;
    }
    if (v[i].second - v[i].first + mn[ptr] + c <= mx) {
      return true;
    }
  }
  return false;
}

int main() {
  n = read();
  m = read();
  mc = read();
  for (int i = 1; i <= n; ++i) {
    a[i] = read();
  }
  for (int j = 1; j <= n; ++j) {
    w[j] = read();
  }
  memset(dp, 0xcf, sizeof(dp));
  dp[0][0] = mc;
  for (int i = 0; i <= n - 1; ++i) {
    for (int j = 0; j <= n; ++j) {
      if (dp[i][j] >= a[i + 1]) {
        dp[i + 1][j] = max(dp[i + 1][j], min(dp[i][j] - a[i + 1] + w[i + 1], mc));
        dp[i + 1][j + 1] = max(dp[i + 1][j + 1], min(dp[i][j] - a[i + 1], mc));
      }
    }
  }
  
   mx = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= n; ++j) {
      if (dp[i][j] >= 0) {
        mx = max(mx, j);
      }
    }
  }
  bfs();
  init();
  for (int i = 1; i <= m; ++i)  {
    int x = read();
    puts(solve(x) ? "1" : "0");
  }
  return 0;
}
