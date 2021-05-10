#include <bits/stdc++.h>

using namespace std;

namespace XDYIMCMI0LY {

    inline int read() {
        int f = 1, x = 0, ch = getchar();
        for (; !isdigit(ch); ch = getchar()) f = (ch == '-') ? -1 : 1;
        for (; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
        return f * x;
    }

    const int N = 2000 + 5;
    const int M = 40 + 5;
    const int E = N * 2 + 5;

    int n, m;

    vector <int> pnt[M][N];

    int head[N], ver[E], nxt[E];

    inline void _add(int u, int v) {
        static int tot = 0;
        ++tot, nxt[tot] = head[u], ver[tot] = v, head[u] = tot;
    }

    const int V = N * N + 5;
    const int EE = 9260817;

    int hole[M];

    struct dinic {
        int head[V], nxt[EE], ver[EE], cap[EE], cur[V];
        int tote, tot, S, T;

        int id(int i, int t) {
            return (t - 1) * m + n + i;
        }

        void add_edge(int u, int v, int c) {
            ++tote, nxt[tote] = head[u], ver[tote] = v, head[u] = tote, cap[tote] = c;
        }

        void add(int u, int v, int c) {
            add_edge(u, v, c);
            add_edge(v, u, 0);
        }
        int vis[V], dist[V];

        inline bool bfs() {
            queue <int> que;
            que.push(S);
            ++tot;
            vis[S] = tot;
            dist[S] = 0;
            while (!que.empty()) {
                int u = que.front();
                que.pop();
                for (int o = head[u]; o; o = nxt[o]) {
                    int v = ver[o];
                    if (vis[v] != tot && cap[o]) {
                        vis[v] = tot;
                        dist[v] = dist[u] + 1;
                        que.push(v);
                    }
                }
            }
            return vis[T] == tot;
        }

        int dfs(int u, int f) {
            if (u == T || f == 0) return f;
            int sum = 0;
            for (int &o = cur[u]; o; o = nxt[o]) {
                int v = ver[o];
                if (dist[v] == dist[u] + 1 && cap[o]) {
                    int nw = dfs(v, min(f, cap[o]));
                    cap[o] -= nw;
                    cap[o ^ 1] += nw;
                    f -= nw;
                    sum += nw;
                    if (!f) break;
                }
            }
            return sum;
        }

        void solve() {
            S = V - 2;
            T = V - 1;
            int t = 1, ans = 0;
            for (int i = 1; i <= n; ++i) add(S, i, 1);
            for (t = 1; ans != n; ++t) {
                for (int i = 1; i <= m; ++i) {
                    if (t != 1) add(id(i, t - 1), id(i, t), n);
                    add(id(i, t), T, 1);
                    for (int j = 0; j < (int) pnt[i][t - 1].size(); ++j) {
                        int v = pnt[i][t - 1][j];
                        add(v, id(i, t), 1);
                    }
                }
                while (bfs()) {
                    int tot = id(n, t);
                    for (int i = 1; i <= tot; ++i) cur[i] = head[i];
                    cur[S] = head[S];
                    cur[T] = head[T];
                    ans += dfs(S, 10000000);
                };
                // cerr << ans << endl;
            }

            cout << t - 2 << endl;
        };
    } d;

    void dfs(int u, int fa, int anc, int dep) {
        pnt[anc][dep].push_back(u);
        for (int o = head[u]; o; o = nxt[o]) {
            int v = ver[o];
            if (v == fa) continue;
            dfs(v, u, anc, dep + 1);
        }
    }

    int _main() {
        n = read(), m = read();
        for (int i = 1; i < n; ++i) {
            int u = read(), v = read();
            _add(u, v), _add(v, u);
        }
        for (int i = 1; i <= m; ++i) hole[i] = read();
        for (int i = 1; i <= m; ++i) dfs(hole[i], 0, i, 0);

        d.solve();
        return 0;
    }
}

int main() { return XDYIMCMI0LY::_main(); }