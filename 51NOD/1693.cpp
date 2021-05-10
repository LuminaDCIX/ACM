#include <bits/stdc++.h>

using namespace std;

namespace XDYIMCMI0LY {

    inline int read() {
        int f = 1, x = 0, ch = getchar();
        for (; !isdigit(ch); ch = getchar()) f = (ch == '-') ? -1 : 1;
        for (; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
        return f * x;
    }

    const int N = 2e6 + 5;
    const int M = 2e7 + 5;

    int n;

    int head[N], nxt[M], ver[M], val[M];

    inline void _add(int u, int v, int w) {
        static int tot = 0;
        ++tot, nxt[tot] = head[u], ver[tot] = v, val[tot] = w, head[u] = tot;
    }

    int mul[] = {2, 3, 5, 7, 11};

    int dist[N], inq[N];

    void spfa() {
        memset(dist, 0x3f3f, sizeof(dist));
        dist[1] = 0;
        queue <int> que;
        que.push(1);
        inq[1] = 1;
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            inq[u] = 0;
            for (int j = 0; j < 5; ++j) {
                int v = mul[j] * u;
                if (v < n + 6 && dist[v] > dist[u] + mul[j]) {
                    dist[v] = dist[u] + mul[j];
                    if (!inq[v]) inq[v] = 1, que.push(v);
                }
            }

            if (u - 1 > 0 && dist[u - 1] > dist[u] + 1) {
                dist[u - 1] = dist[u] + 1;
                if (!inq[u - 1]) inq[u - 1] = 1, que.push(u - 1);
            }
        }
    }

    int _main() {
        n = read();
        spfa();
        cout << dist[n] << endl;
        return 0;
    }
}

int main() { return XDYIMCMI0LY::_main(); }