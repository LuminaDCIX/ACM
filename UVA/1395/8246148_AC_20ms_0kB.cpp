#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, kase, set[105], ans, ok;
const int INF = 0x3f3f3f3f;
struct edge {
    int value, u, v;
    edge() {
		value = INF, u = 0, v = 0; 
	} 
	edge(int from, int to, int val) {
        value = val; u = from; v = to;
    }
} edges[50005];
bool cmp_(edge a, edge b) {
    return a.value < b.value;
}
int find(int x) {
    return set[x] == x ? x : set[x] = find(set[x]);
}
void input() {
    int u, v, value;
    for(int i = 1; i <= m; i ++) {
        scanf("%d %d %d", &u, &v, &value);
        edges[i] = edge(u, v, value);
    }
}
void kruskal(int l, int r) {
	int i = l;
    for(i = l; i <= r; i ++) {
        edge &e = edges[i];
        int fv = find(e.v), fu = find(e.u);
        if(fv == fu) continue;
        set[fu] = fv;
        ok ++;
		if (ok == n - 1) break;
    }
	if (ok == n - 1) ans = min(ans, edges[i].value - edges[l].value);
}
void solve() {
    sort(edges + 1, edges + m + 1, cmp_);
    ans = INF;
    int L = 1, R = n - 1;
    while(L <= m) {
        for(int i = 1; i <= n; i ++) set[i] = i;
        ok = 0;
        kruskal(L++, m);
    }
}
void output() {
    if(ans == INF) printf("-1"); else printf("%d", ans);
}
int main() {
    while(scanf("%d %d",&n , &m) && (n + m)) {
        input();
        solve();
        output();
		putchar('\n');
    }
    return 0;
}