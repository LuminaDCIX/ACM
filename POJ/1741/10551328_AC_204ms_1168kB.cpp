#include <cstdio>
#include <algorithm>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>

using namespace std;

const int N = 10000 + 5;
typedef long long ll;
vector<int> s;
int n, k, p;
int siz[N];
struct edge {
	int val, nxt, to;
};
edge edges[N << 1];
int head[N], tot;
int sum, root;
ll ans;
int f[N];
int d[N], deep[N];
int cnt;
bool vis[N];
inline void add_edge(int from, int to, int val) {
	edges[tot].to = to;
	edges[tot].nxt = head[from];
	edges[tot].val = val;
	head[from] = tot++;
}
void getroot(int u, int fa)
{
	siz[u] = 1;
	f[u] = 0;
	for (int i = head[u]; ~i; i = edges[i].nxt) {
		int v = edges[i].to;
		if (v == fa || vis[v]) {
			continue;
		}
		getroot(v, u);
		f[u] = max(f[u], siz[v]);
		siz[u] += siz[v];
	}
  f[u] = max(f[u], sum - siz[u]);
	if (f[u] < f[root]) {
	  root = u;
	}
}
void getdeep(int u, int fa)
{
	deep[cnt++] = d[u];
	for (int i = head[u]; ~i; i = edges[i].nxt) {
		int v = edges[i].to;
		if (v == fa || vis[v]) {
			continue;
		}
		d[v] = d[u] + edges[i].val;
		getdeep(v, u); 
	}
}
ll calc(int x, int now) 
{
	d[x] = now;
	cnt = 0;
	getdeep(x, 0);
	sort(deep, deep + cnt);
	ll t = 0;
	for (int l = 0, r = cnt - 1; l < r;) {
		if (deep[l] + deep[r] <= k) {
			t += r - l;
			++l;
		}
		else {
			--r;
		}
	}
	return t;
}
void solve(int u)
{
	ans += calc(u, 0);
	vis[u] = 1;
	for (int i = head[u]; ~i; i = edges[i].nxt) {
		int v = edges[i].to;
		if (vis[v]) {
			continue;
		}
		ans -= calc(v, edges[i].val);
		sum = siz[v];
		root = 0;
		getroot(v, u);
		solve(root);
	}
}
int main()
{
	memset(head, -1, sizeof(head));
	while (1) {
		memset(head, -1, sizeof(head));
		memset(vis, 0, sizeof(vis));
		tot = 0;
		scanf("%d%d", &n, &k);
		if (n == 0 && k == 0) {
			return 0;
		}
		for (int i = 1, u, v, x; i < n; ++i) {
			scanf("%d%d%d", &u, &v, &x);
			add_edge(u, v, x);
			add_edge(v, u, x);
		}
		sum = n;
		f[0] = 1e9;
		root = 0;
		ans = 0;
		getroot(1, 0);
		solve(root);
		printf("%lld\n", ans);
	}
	return 0;
}
