#include <set>
#include <map>
#include <stack>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
 
using namespace std;

const int N = 50000 + 5;
const int M = 100000 + 5;

int n, m, d;
char str[N];
vector <int> freex;
int idi[M], idj[M];
int hi[M], hj[M];
bool vis[N << 1];
int low[N << 1], dfn[N << 1];
int dfn_cnt;
int scc_cnt;
int scc[N << 1];
int in[N << 1];
int ops[N << 1];
int exi[N << 1];
int que[N << 1];
int h, t;
stack <int> stk;

struct graph {
	int head[N << 1], tot;

	struct edge {
		int nxt, to;
	} e[M << 1];

	inline void add(int u, int v) {
		e[tot].nxt = head[u];
		e[tot].to = v;
		head[u] = tot++;
	}

	inline void clear() {
		memset(head, -1, sizeof(head));
		tot = 0;
	}
} g1, g2;

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

inline int getpoint(char c, int x)
{
	if (str[x] == 'a') {
		return (c == 'B') ? (x << 1) : (x << 1 | 1);
	}
	if (str[x] == 'b') {
		return (c == 'A') ? (x << 1) : (x << 1 | 1);
	}
	if (str[x] == 'c') {
	  return (c == 'A') ? (x << 1) : (x << 1 | 1);
	}
}

void dfs1(int u) 
{
	vis[u] = 1;
	low[u] = dfn[u] = ++dfn_cnt;
	stk.push(u);
	for (int i = g1.head[u], v; ~i; i = g1.e[i].nxt) {
		v = g1.e[i].to;
		if (!dfn[v]) {
			dfs1(v);
			low[u] = min(low[u], low[v]);
		}
		else if (vis[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (low[u] == dfn[u]) {
		++scc_cnt;
		int y;
		do {
			y = stk.top();
			stk.pop();
			vis[y] = 0;
			scc[y] = scc_cnt;
		} while (y != u);
	}
}

inline void build()
{
	g1.clear();
	memset(exi, -1, sizeof(exi));
	for (int i = 0; i < m; ++i) {
		if (hi[i] + 32 == str[idi[i]]) {
			continue;
		}
		int u = getpoint(hi[i], idi[i]);
		if (hj[i] + 32 == str[idj[i]]) {
			g1.add(u, u ^ 1);
		}
		int v = getpoint(hj[i], idj[i]);
		g1.add(u, v);
		g1.add(v ^ 1, u ^ 1);
	}
	scc_cnt = dfn_cnt = 0;
	memset(dfn, 0, sizeof(dfn));
	for (int i = 0; i < (n << 1); ++i) {
		if (!dfn[i]) {
			dfs1(i);
		}
	}
}


inline bool succ() {
	memset(in, 0, sizeof(in));
	for (int i = 0; i < n; ++i) {
		if (scc[i << 1] == scc[i << 1 | 1]) {
			return false;
		}
	}
	g2.clear();
	for (int u = 0; u < (n << 1); ++u) {
		for (int i = g1.head[u], v; ~i; i = g1.e[i].nxt) {
			v = g1.e[i].to;
			if (scc[v] != scc[u]) {
				g2.add(scc[v], scc[u]);
				++in[scc[u]];
			}
		}
	}
	return true;
}

inline bool print() {
	h = t = 0;
	for (int i = 1; i <= scc_cnt; ++i) {
		if (in[i] == 0) {
			que[t++] = i;
		}
	}
	for (int i = 0; i < n; ++i) {
		ops[scc[i << 1]] = scc[i << 1 | 1];
		ops[scc[i << 1 | 1]] = scc[i << 1];
	}
	while (h < t) {
		int u = que[h++];
		for (int i = g2.head[u], v; ~i; i = g2.e[i].nxt) {
		  v = g2.e[i].to;
			--in[v];
			if (in[v] == 0) {
				que[t++] = v;
			}
		}
	}
	for (int i = 0; i < t; ++i) {
		int u = que[i];
		if (exi[u] == 0) {
			continue;
		}
		exi[u] = 1;
		u = ops[u];
		exi[u] = 0;
		for (int j = g2.head[u], v; ~j; j = g2.e[j].nxt) {
			v = g2.e[j].to;
			exi[v] = 0;
		}
	}
	for (int i = 0; i < n; ++i) {
		if (str[i] == 'a') {
			putchar(exi[scc[i << 1]] ? 'B' : 'C');
		}
		if (str[i] == 'b') {
			putchar(exi[scc[i << 1]] ? 'A' : 'C');
		}
		if (str[i] == 'c') {
			putchar(exi[scc[i << 1]] ? 'A' : 'B');
		}
	}
	puts("");
	return true;
}

bool dfs(int now) 
{
	if (now == freex.size()) {
		build();
		if (succ() && print()) {
			return true;
		}
		return false;
	}
	str[freex[now]] = 'a';
 	if (dfs(now + 1)) {
		return true;
	}
	str[freex[now]] = 'b';
	if (dfs(now + 1)) {
		return true;
	}
	return false;
}

int main() {
	n = read();
	d = read();
	scanf("%s", str);
	for (int i = 0; i < n; ++i) {
		if (str[i] == 'x') {
			freex.push_back(i);
		}
	}
	m = read();
	for (int i = 0; i < m; ++i) {
		idi[i] = read() - 1;
		hi[i] = getchar();
		idj[i] = read() - 1;
		hj[i] = getchar();
	}
	if (!dfs(0)) {
		puts("-1");
	}
	return 0;
}

