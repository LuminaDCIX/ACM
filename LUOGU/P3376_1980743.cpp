//当前弧优化 Dinic
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000;
const int inf = 0x3f3f3f3f;
struct edge {
        int to, nxt;
        int cap, flow;
} e[2 * maxn + 5];
int head[10005];
void Add(int from, int to, int cap) {
        static int tot = 1;
        e[++tot] = (edge){to, head[from], cap, 0};
        head[from] = tot;
        e[++tot] = (edge){from, head[to], 0, 0};
        head[to] = tot;
}
bool vis[10005];
int dis[10005];
int cur[10005]; //当前弧
int N, M, S, T;
bool bfs() {
        memset(vis, 0, sizeof(vis));
        queue<int> q;
        q.push(S);
        dis[S] = 0;
        vis[S] = true;
        while(!q.empty()) {
                int x = q.front(); q.pop();
                for (int i = head[x]; i; i = e[i].nxt) {        
                        if (!vis[e[i].to] && e[i].cap > e[i].flow) {
                                vis[e[i].to] = true;
                                dis[e[i].to] = dis[x] + 1;
                                q.push(e[i].to);
                        }
                }
        }
        return vis[T];
} 
int dfs(int x, int f) {
        if (x == T || f == 0) return f;
        int flow = 0, now;
        for (int &i = cur[x]; i; i = e[i].nxt) {
                if (dis[x] + 1 == dis[e[i].to] 
                && (now = dfs(e[i].to, min(f, e[i].cap - e[i].flow))) > 0) {
                        e[i].flow += now;
                        e[i ^ 1].flow -= now;
                        flow += now;
                        f -= now;
                        if (!f) break;  
                }
        }
        return flow;
}
int dinic() {
        int flow = 0;
        while (bfs()) {
                for (int i = 1; i <= N; i++) cur[i] = head[i]; 
                flow += dfs(S, inf);
        }
        return flow;
}
int main() {
        scanf("%d%d%d%d", &N, &M, &S, &T);
        while (M--) {
                int f, t, c;
                scanf("%d%d%d", &f, &t, &c);
                Add(f, t, c);
        }
        printf("%d", dinic());
        return 0;
}