#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef pair<int, short> pii;
typedef __gnu_pbds::priority_queue<pii, greater<pii>, pairing_heap_tag> heap;
typedef long long ll;
const int N = 2500 + 5;
const int M = 6200 * 2 + 5;
const int inf = 1e9;
heap::point_iterator id[N];
int n, m, tot;
short head[N];
int dist[N];
int x, y, s, e;
struct edge {
    short nxt, to, val;
} edges[M];
inline void add_edge(int from, int to, int val) 
{
    edges[tot].nxt = head[from];
    edges[tot].to = to;
    edges[tot].val = val;
    head[from] = tot++;
}
inline void dijkstra() 
{
    heap que;
    for (int i = 1; i <= n; ++i) {
        dist[i] = inf;
    }
    dist[s] = 0;
    id[s] = que.push(make_pair(0, s));
    while (!que.empty()) {
        int u = que.top().second;
        que.pop();
        for (int i = head[u]; ~i; i = edges[i].nxt) {
            edge e = edges[i];
            if (e.val + dist[u] < dist[e.to]) {
                dist[e.to] = e.val + dist[u];
                if (id[e.to] != 0) {
                    que.modify(id[e.to], make_pair(dist[e.to], e.to));
                }
                else {
                    id[e.to] = que.push(make_pair(dist[e.to], e.to));
                }
            }
        }
    }
}
int main() 
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &m, &s, &e);
    for (int i = 1, x, y, z; i <= m; ++i) {
        scanf("%d%d%d", &x, &y, &z);
        add_edge(x, y, z);
        add_edge(y, x, z);
    }
    dijkstra();
    printf("%d\n", dist[e]);
    return 0;
}
