// luogu-judger-enable-o2
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;
typedef long long ll;

inline int read() {
    int f = 1;
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch)) {
        f = (ch == '-') ? -1 : 1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return f * x;
}

const int N = 2400 + 5;
const int M = 4260817;

int n, m;

struct dinic {
    int nxt[M], ver[M], cap[M];
    int head[N], cur[N];

    int s, t;

    inline void add_edge(int u, int v, int c) {
        static int tot = 1;
        ++tot;
        nxt[tot] = head[u];
        ver[tot] = v;
        cap[tot] = c;
        head[u] = tot;
    }

    inline void add(int u, int v, int c) {
        add_edge(u, v, c);
        add_edge(v, u, 0);
    }

    void init() {
        s = N - 2;
        t = N - 1;
    }

    bool vis[N];
    int dist[N];

    bool bfs() {
        memset(vis, 0, sizeof(vis));
        vis[s] = 1;
        queue <int> que;
        que.push(s);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int o = head[u]; o; o = nxt[o]) {
                int v = ver[o];
                if (!vis[v] && cap[o]) {
                    vis[v] = 1;
                    dist[v] = dist[u] + 1;
                    que.push(v);
                }
            }
        }
        return vis[t];
    }

    int dfs(int u, int f) {
        if (u == t || f == 0) return f;
        int ans = 0;
        for (int &o = cur[u]; o; o = nxt[o]) {
            int v = ver[o];
            if (dist[v] == dist[u] + 1 && cap[o]) {
                int nw = dfs(v, min(f, cap[o]));
                cap[o] -= nw;
                cap[o ^ 1] += nw;
                f -= nw;
                ans += nw;
                if (!f) break;
            }
        }
        return ans;
    }

    inline ll solve() {
        ll ans = 0;
        while (bfs()) {
            memcpy(cur, head, sizeof(cur));
            ans += dfs(s, 1e9);
        }
        return ans;
    }
} s;

int main() {
    n = read();
    m = read();
    ll ans = 0;
    s.init();
    for (int i = 1; i <= n; ++i) {
        int x = read();
        int t = read();
        s.add(s.s, i, x);
        ans += x;
        for (int j = 1; j <= t; ++j) {
            int v = read();
            int c = read();
            s.add(i, v + n, c);
        }
    }
    for (int i = 1; i <= m; ++i) {
        int x = read();
        s.add(i + n, s.t, x);
    }
    ans -= s.solve();
    printf("%lld\n", ans);
    return 0;
}