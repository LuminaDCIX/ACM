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

const int N = 200000 + 5;
int n, col[N], k;
int head[N], tot;
int siz[N], f[N];
int dep[N], depmx[N], dist[N];
int mx[N];
bool vis[N];
bool update[N];
vector <int> vec;
vector <int> all;
int root, sum;

struct edge {
	int nxt, to;
} e[N << 1];


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

inline void add(int u, int v) {
	e[tot].to = v;
	e[tot].nxt = head[u];
	head[u] = tot++;
}

void getroot(int u, int fa)
{
	siz[u] = 1;
	f[u] = 0xcfcfcfcf;
	for (int i = head[u], v; ~i; i = e[i].nxt) {
		v = e[i].to;
		if (vis[v] || fa == v) {
			continue;
		}
	  getroot(v, u);
		siz[u] += siz[v];
		f[u] = max(f[u], siz[v]);
	}
	f[u] = max(f[u], sum - siz[u]);
	if (root == -1 || f[u] < f[root]) {
		root = u;
	}
}

void calc(int u, int fa)
{
	if (depmx[col[u]] == -1) {
		vec.push_back(col[u]);
	}
	depmx[col[u]] = max(depmx[col[u]], dep[u]);
	for (int i = head[u], v; ~i; i = e[i].nxt) {
		v = e[i].to;
		if (v == fa || vis[v]) {
			continue;
		}
		dep[v] = dep[u] + 1;
		calc(v, u);
	}
}

void solve(int u)
{
	vis[u] = 1;
	for (int i = head[u], v; ~i; i = e[i].nxt) {
		v = e[i].to;
		dep[v] = 0;
		calc(v, u);
		for (int j = 0, now; j < vec.size(); ++j) {
			now = vec[j];
			if (col[u] == now) {
				mx[now] = max(mx[now], depmx[now] + 1);
			}
			if (!update[now]) {
				all.push_back(now);
				update[now] = 1;
				dist[now] = depmx[now];
			}
			else {
				mx[now] = max(mx[now], dist[now] + depmx[now] + 2);
				dist[now] = max(dist[now], depmx[now]);
			}
			depmx[now] = -1;
		}
		vec.clear();
	}
	for (int i = 0, now; i < all.size(); ++i) {
		now = all[i];
		update[now] = 0;
	}
	all.clear();
	for (int i = head[u], v; ~i; i = e[i].nxt) {
		v = e[i].to;
		if (vis[v]) {
			continue;
		}
		root = -1;
		sum = siz[u];
		getroot(v, u);
		solve(root);
	}
}

int main() {
	memset(head, -1, sizeof(head));
  n = read();
	k = read();
	int rec = 1;
	for (int i = 1, v; i <= n; ++i) {
		col[i] = read();
		v = read();
		if (v == 0) {
			rec = i;
			continue;
		}
		add(i, v);
		add(v, i);
	}
	sum = n;
	root = -1;
	getroot(rec, 0);
	memset(depmx, -1, sizeof(depmx));
	solve(root);
	for (int i = 1; i <= k; ++i) {
		printf("%d\n", mx[i]);
	}
	return 0;
}
