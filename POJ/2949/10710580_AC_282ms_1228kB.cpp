#include <set>
#include <map>
#include <stack>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iostream>
 
using namespace std;

const int N = 27 * 27 + 5;
const int M = 100000 + 5;
const int S = 1000 + 5;

int n;
int head[N], tot;
char str[S];
double dist[N];
bool instk[N];

struct edge {
  int nxt, to;
  double val, len;
} e[M];

inline int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		f = (ch == '-') ? -1 : 1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 3) + (x << 1) + ch - '0';
		ch = getchar();
  }
	return x * f;
}

inline void add(int u, int v, int len) {
  e[tot].to = v;
  e[tot].nxt = head[u];
  e[tot].len = len;
  head[u] = tot++;
}

inline void init(double x) {
  for (int i = 0; i < tot; ++i) {
    e[i].val = e[i].len - x;
  }
  for (int i = 0; i < N; ++i) {
    dist[i] = 0;
  }
  memset(instk, 0, sizeof(instk));
}

bool spfa(int u)
{
  instk[u] = 1;
  for (int i = head[u], v; ~i; i = e[i].nxt) {
    v = e[i].to;
    if (dist[v] < dist[u] + e[i].val) {
      dist[v] = dist[u] + e[i].val;
      if (instk[v] || spfa(v)) {
        return true;
      }
    }
  }
  instk[u] = 0;
  return false;
}
int main() {
  while (scanf("%d", &n) && n) {
    memset(head, -1, sizeof(head));
    tot = 0;
    int maxlen = 0;
    for (int i = 0, u, v, len; i < n; ++i) {
      scanf("%s", str);
      len = strlen(str);
      if (len < 2) {
        continue;
      }
      u = (str[0] - 'a') * 26 + str[1] - 'a';
      v = (str[len - 2] - 'a') * 26 + str[len - 1] - 'a';
      add(u, v, len);
      maxlen = max(maxlen, len);
    }
    double l = 0.0;
    double r = (double) maxlen;
    int cnt = 0;
    double ans = -1;
    while (cnt < 25) {
      double mid = (l + r) * 0.5;
      init(mid);
      bool succ = 0;
      for (int i = 0; i < N; ++i) {
        if (spfa(i)) {
          succ = 1;
          break;
        }
      }
      if (succ) {
        l = mid;
        ans = mid;
      } else {
        r = mid;
      }
      ++cnt;
    }
    if (ans != -1) {
      printf("%.2f\n", ans);
    } else {
      puts("No solution.");
    }
  }
	return 0;
}
