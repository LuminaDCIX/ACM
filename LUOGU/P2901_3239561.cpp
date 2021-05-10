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

const int N = 1000 + 5;
const int M = 10000 + 5;
const int K = 100 + 5;
typedef long long ll;

int n, m, k;
int head[N], tot;
int cnt;
ll path[K];

struct edge {
	int nxt, to, val;
} e[M];

struct node {
	int u;
	ll v;
	bool operator < (const node &rhs) const {
		return v > rhs.v;
	}
	node(int _u, ll _v) {
		u = _u;
		v = _v;
	}
};

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

inline void add(int u, int v, int w) {
	e[tot].to = v;
	e[tot].nxt = head[u];
	e[tot].val = w;
	head[u] = tot++;
}

inline void solve() 
{
	priority_queue <node> que;
	que.push(node(n, 0));
	memset(path, -1, sizeof(path));
	while (!que.empty()) {
		int u = que.top().u;
		ll w = que.top().v;
		if (u == 1) {
			path[cnt++] = w;
			if (cnt == k) {
				return;
			}
		}
		que.pop();
		for (int i = head[u], v; ~i; i = e[i].nxt) {
			v = e[i].to;
			que.push(node(v, w + e[i].val));
		}
	}
}
int main()
{
	memset(head, -1, sizeof(head));
	n = read();
	m = read();
	k = read();
	for (int i = 0, u, v, w; i < m; ++i) {
		u = read();
		v = read();
		w = read();
		add(u, v, w);
	}
	solve();
	for (int i = 0; i < k; ++i) {
		printf("%lld\n", path[i]);
	}
	return 0;
}
