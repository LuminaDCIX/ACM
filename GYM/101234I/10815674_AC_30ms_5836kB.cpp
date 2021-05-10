#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

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

const int N = 1e5 + 5;

int n;

int tot;
int head[N];

struct edge {
  int nxt;
  int to;
} e[N << 1];

inline void add(int u, int v) {
  e[tot].to = v;
  e[tot].nxt = head[u];
  head[u] = tot++;
}

int two[N];
int leet[N];
int deg[N];

long long ans = 0;

void dfs(int u, int fa)
{
  bool flg = 0;
  for (int i = head[u], v; ~i; i = e[i].nxt) {
    v = e[i].to;
    if (v == fa) {
      continue;
    }
    flg = 1;
    dfs(v, u);
    two[u] += two[v];
    leet[u] += leet[v];
  }
  if (!flg) {
    leet[u] = 1;
    return;
  }
  if (two[u] >= 2) {
    ans += two[u] / 2;
    two[u] = two[u] % 2;
  }
  if (leet[u] > 2) {
    if (leet[u] % 2 == 0) {
      ans += (leet[u] - 2) / 2;
      leet[u] = 2;
    } else {
      ans += leet[u] / 2;
      leet[u] %= 2;
    }
  }
  if (two[u] && leet[u] == 2) {
    ++ans;
    leet[u] = 1;
    two[u] = 0;
  }
  if (two[u] && leet[u] == 1) {
    leet[u] = 0;
  }
  if (leet[u] == 2) {
    two[u] = 1;
    leet[u] = 0;
  }
  leet[u] += two[u] * 2;
  if (leet[u] >= 2) {
    leet[u] = 0;
    two[u] = 1;
  }
  if (fa == -1) {
    if (two[u]) {
      ++ans;
    }
  }
  return;
}
 
int main() {
  n = read();
  memset(head, -1, sizeof(head));
  for (int i = 0, u, v; i < n - 1; ++i) {
    u = read();
    v = read();
    ++deg[u];
    ++deg[v];
    add(u, v);
    add(v, u);
  }
  for (int i = 1; i <= n; ++i) {
    if (deg[i] == 1) {
      continue;
    }
    dfs(i, -1);
    break;
  }
  printf("%lld\n", max(ans, 1ll));
  return 0;
}



