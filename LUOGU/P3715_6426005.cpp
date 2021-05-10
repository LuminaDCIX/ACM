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

const int N = 50 + 5;
const int LEN = 100 + 5;
const int MAX = 200 + 5;
const int P = 1e9 + 7;


int n, m, L;

char ok[N][LEN];
char f[N][LEN];

int root, tot;
int nxt[MAX][26], fail[MAX];
bool die[MAX];

void mul(int &a, int b) {
  a = (long long) a * b % P;
}
void sub(int &a, int b) {
  (a -= b) < 0 ? a += P : a;
}
void add(int &a, int b) {
  (a += b) >= P ? a -= P : a;
}

void init() {
  root = ++tot;;
}

void ins(char *s) {
  int len = strlen(s + 1);
  int nw = root;
  for (int i = 1; i <= len; ++i) {
    int x = s[i] - 'a';
    if (nxt[nw][x] == 0) {
      nxt[nw][x] = ++tot;
    }
    nw = nxt[nw][x];
  }
  die[nw] = 1;
  
}

void build() {
  queue <int> que;
  for (int i = 0; i < 26; ++i) {
    if (nxt[root][i]) {
      int p = nxt[root][i];
      fail[p] = root;
      que.push(p);
    } else {
      nxt[root][i] = root;
    }
  }
  while (!que.empty()) {
    int x = que.front();
    que.pop();
    for (int i = 0; i < 26; ++i) {
      if (nxt[x][i]) {
        int p = nxt[x][i];
        fail[p] = nxt[fail[x]][i];
        die[p] |= die[fail[p]];
        que.push(p);
        } else {
        nxt[x][i] = nxt[fail[x]][i];
      }
    }
  }
}

int go(int x, char *s) {
  int len = strlen(s + 1);
  if (die[x]) {
    return -1;
  }
  int nw = x;
  for (int i = 1; i <= len; ++i) {
    nw = nxt[nw][s[i] - 'a'];
    if (die[nw]) {
      return -1;
    }
  }
  return nw;
}

namespace solve1 {
  int dp[LEN][MAX];

  void solve() {
    dp[0][1] = 1;
    for (int i = 0; i < L; ++i) {
      for (int j = 1; j <= tot; ++j) {
        int t = dp[i][j];
        for (int k = 1; k <= n; ++k) {
          int ver = go(j, ok[k]);
          if (ver != -1) {
            add(dp[i + strlen(ok[k] + 1)][ver], t);
          }
        }
      }
    }
    int s = 0;
    for (int i = 1; i <= tot; ++i) {
      if (!die[i]) {
        add(s, dp[L][i]);
      }
    }
    printf("%d\n", s);
  }
}

namespace solve2 {

  struct mat {
    int n;
    int s[MAX * 2][MAX * 2];
    mat(int x) {
      n = x;
      memset(s, 0, sizeof(s));
    }
    mat(int x, int p) {
      n = x;
      memset(s, 0, sizeof(s));
      for (int i = 1; i <= n; ++i) {
        s[i][i] = 1;
      }
    }
  };

  mat operator * (const mat a, const mat b) {
    mat r = mat(a.n);
    for (int k = 1; k <= a.n; ++k) {
      for (int i = 1; i <= a.n; ++i) {
        for (int j = 1; j <= a.n; ++j) {
          int v = a.s[i][k];
          mul(v, b.s[k][j]);
          add(r.s[i][j], v);
        }
      }
    }
    return r;;
  }

  mat fac(mat a, int x) {
    mat r = (mat(a.n, 1));
    while (x) {
      
      if (x & 1) {
        r = r * a;
      }
      a = a * a;
      x >>= 1;
    }
    return r;
  }
  
  void solve() {
    mat v = mat(tot * 2);
    for (int i = 1; i <= tot; ++i) {
      for (int j = 1; j <= n; ++j) {
        int k = go(i, ok[j]);
        if (k == -1) {
          continue;
        }
        if (strlen(ok[j] + 1) == 1) {
          ++v.s[i][k];
        } else {
          ++v.s[i + tot][k];
        }
      }
    }
    for (int i = 1; i <= tot; ++i) {
      v.s[i][tot + i] = 1;
    }
    v = fac(v, L);
    int s = 0;
    for (int i = 1; i <= tot; ++i) {
      add(s, v.s[1][i]);
    }
    printf("%d\n", s);
  }
}

int main() {
  n = read();
  m = read();
  L = read();
  for (int i = 1; i <= n; ++i) {
    scanf("%s", ok[i] + 1);
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%s", f[i] + 1);
  }
  init();
  for (int i = 1; i <= m; ++i) {
    ins(f[i]);
  }
  build();
  if (L <= 100) {
    solve1::solve();
  } else {
    solve2::solve();
  }
  return 0;
}
