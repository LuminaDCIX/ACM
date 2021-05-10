#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

const int N = 1000 + 5;
bool vis[N];
int sg[N];
int que[N];
int h, t;
int ind[N];
int n;
struct Graph {
	int head[N];
	int tot;
	struct edge {
		int nxt, to;
	};
	edge edges[N * N];
	inline void add_edge(int from, int to) {
		edges[tot].to = to;
		edges[tot].nxt = head[from];
		head[from] = tot++;
	}
	inline void clear() {
		memset(head, -1, sizeof(head));
		tot = 0 ;
	}
}g, rg;
inline void init()
{
	h = t = 0;
	for (int i = 0; i < n; ++i) {
		if (ind[i] == 0) {
			que[t++] = i;
		}
	}	
	while (h < t) {
		int u = que[h++];
	  for (int i = rg.head[u]; ~i; i = rg.edges[i].nxt) {
			int v = rg.edges[i].to;
			--ind[v];
			if (ind[v] == 0) {
				que[t++] = v;
			}
		}
	}
	for (int i = 0; i < t; ++i) {
		memset(vis, 0, sizeof(vis));
		int u = que[i];
		for (int j = g.head[u]; ~j; j = g.edges[j].nxt) {
			int v = g.edges[j].to;
			vis[sg[v]] = 1;
		}
		for (int j = 0; j <= 1000; ++j) {
			if (!vis[j]) {
				sg[u] = j;
				break;
			}
		}
	}
}
int main() 
{
	while (~scanf("%d", &n)) {
		g.clear();
		rg.clear();
		for (int i = 0, x; i < n; ++i) {
			scanf("%d", &x);
			for (int j = 0, v; j < x; ++j) {
				scanf("%d", &v);
				g.add_edge(i, v);
				rg.add_edge(v, i);
				++ind[x];
			}
		}
		init();
		int x;
		while (scanf("%d", &x) && x) {
			int v = 0;
			for (int i = 0, p; i < x; ++i) {
				scanf("%d", &p);
				v ^= sg[p];
			}
			puts(v == 0 ? "LOSE" : "WIN");
		}
	}
	return 0;
}
