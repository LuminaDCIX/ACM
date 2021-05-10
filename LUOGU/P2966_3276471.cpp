#include <bits/stdc++.h>

using namespace std;

const int N = 250 + 5;
const int M = 10000 + 5;

int n, m, q;
int val[N];
int id[N];
int G[N][N];
int path[N][N];

inline int read() {
	int f = 1, x = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		f = (ch == '-') ? -1 : 1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}

bool cmp(int a, int b) {
	return val[a] < val[b];
}

inline void init()
{
	for (int i = 0; i < n; ++i) {
		id[i] = i;
	}
	sort(id, id + n, cmp);
}

inline void solve()
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			path[i][j] = min(G[i][j] + max(val[i], val[j]), 0x3f3f3f3f);
		}
	}
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				int bar = G[i][id[k]] + G[id[k]][j];
				if (G[i][j] > bar) {
					G[i][j] = bar;
				}
				path[i][j] = min(path[i][j], bar + max(val[i], max(val[j], val[id[k]])));
			}
		}
	}
}

int main()
{
	n = read();
	m = read();
	q = read();
	for (int i = 0; i < n; ++i) {
		val[i] = read();
	}
	init();
	memset(G, 0x3f3f, sizeof(G));
	for (int i = 0; i < n; ++i) {
		G[i][i] = 0;
	}
	for (int i = 0, u, v, w; i < m; ++i) {
		u = read() - 1;
		v = read() - 1;
		w = read();
		G[u][v] = G[v][u] = min(G[u][v], w);
	}
	solve();
	for (int i = 0, u, v; i < q; ++i) {
		u = read() - 1;
		v = read() - 1;
		printf("%d\n", path[u][v]);
	}
	return 0;
}
