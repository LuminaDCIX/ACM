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

const int N = 100000 + 5;

int n, m1, m2;
int head[N], tot;
int in[N];
queue <int> que;

struct edge {
	int nxt, to, from;
	int tag;
} e[N << 2];

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

inline void add(int u, int v, int t) {
	e[tot].to = v;
	e[tot].from = u;
	e[tot].nxt = head[u];
	e[tot].tag = t;
	head[u] = tot++;
}

int main() {
	memset(head, -1, sizeof(head));
	n = read();
	m1 = read();
	m2 = read();
	for (int i = 0, u, v; i < m1; ++i) {
		u = read() - 1;
		v = read() - 1;
		add(u, v, 0);
		++in[v];	
	}
	if (tot & 1) {
		++tot;
	}
	for (int i = 0, u, v; i < m2; ++i) {
		u = read() - 1;
		v = read() - 1;
		add(u, v, 1);
		add(v, u, 1);
	}
	for (int i = 0; i < n; ++i) {
		if (!in[i]) {
			que.push(i);
		}
	}
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		for (int i = head[u], v; ~i; i = e[i].nxt) {
			if (!e[i].tag) {
				v = e[i].to;
				--in[v];
				if (!in[v]) {
					que.push(v);
				}
			}
			if (e[i].tag == 1) {
				e[i ^ 1].tag = 2;
			}
		}
	}
	for (int i = 0; i < tot; ++i) {
		if (e[i].tag == 1) {
			printf("%d %d\n", e[i].from + 1, e[i].to + 1);
		}
	}
	return 0;
}
