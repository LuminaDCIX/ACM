#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
//Product by MiracleEEEE

const int INF = 0x3f3f3f;
int N, S, E, M, K, head[515], tot, distE[1005], distS[1005], vis[1005], wayS[1005], wayE[1005], first;

struct edge {
	int to, value, next;

	friend bool operator < (const edge a, const edge b) {
		return b.value < a.value;
	}

	edge(int t, int x) {
		to = t;
		value = x;
	}

	edge() {
		to = 0;
		value = 0;
		next = 0;
	}
} edges[5005];
priority_queue<edge> q;

struct business {
	int from, to, value;
} busi[5005];

void add(int from, int to, int value) {
	edges[++tot].next = head[from];
	edges[tot].to = to;
	edges[tot].value = value;
	head[from] = tot;
}

bool input() {
	tot = 0;
	memset(head, 0, sizeof(head));
	scanf("%d", &M);
	int u, v, value;
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d",&u, &v, &value);
		add(u, v, value);
		add(v, u, value);
	}

	scanf("%d", &K);
	for (int i = 1; i <= K; i++) {
		scanf("%d %d %d", &busi[i].from, &busi[i].to, &busi[i].value);
	}
	return true;
}

void Dijkstra(int v, int *dist, int *way) {

	for (int i = 1; i <= N; i++) dist[i] = INF, vis[i] = 0;
	dist[v] = 0;
	q.push(edge(v, 0));

	while (!q.empty()) {

		edge e = q.top(); q.pop();
		if (vis[e.to]) continue;

		int v = head[e.to];
		vis[e.to] = 1;
		for (v; v; v = edges[v].next) {
			if (edges[v].value + dist[e.to] < dist[edges[v].to]) {
				dist[edges[v].to] = dist[e.to] + edges[v].value;
				way[edges[v].to] = e.to;
				q.push(edge(edges[v].to, dist[edges[v].to]));
			}
		}

	}
}

void print(int v, int end, bool order, int *way) {
	int i = head[v];
	if (v == end) {
		printf("%d", end);
		return;
	}
	if (!order) {
		print(way[v], end, order, way);
		printf(" %d", v);
	}
	if (order) {
		printf("%d ", v);
		print(way[v], end, order, way);
	}
}

bool solve() {
	Dijkstra(S, distS, wayS);
	Dijkstra(E, distE, wayE);
	int ans = distS[E], ok = 0, u = 0, d = 0;;
	for (int i = 1; i <= K; i++) {
		business &b = busi[i];
		if (distS[b.from] + distE[b.to] + b.value < ans) {
			ans = distS[b.from] + distE[b.to] + b.value;
			ok = 1; u = b.from, d = b.to;
		}
		if (distS[b.to] + distE[b.from] + b.value < ans) {
			ans = distS[b.to] + distE[b.from] + b.value;
			ok = 1; u = b.to, d = b.from;
		}
	}
	if (!ok) {
		print(E, S, 0, wayS);
		putchar('\n');
		printf("Ticket Not Used\n");
	}
	else {
		print(u, S, 0, wayS);
		putchar(' ');
		print(d, E, 1, wayE);
		putchar('\n');
		printf("%d\n", u);
	}
	printf("%d\n", ans);
	return true;
}
int main()
{
	while (scanf("%d", &N) != EOF) {
		scanf("%d %d", &S, &E);
		if (first++) putchar('\n');
		input();
		solve();
	}
	return 0;
}