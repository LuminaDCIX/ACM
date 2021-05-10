#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
int n, m;
vector <int> G[1000005];
vector <int> id[1000005];
int deg[1000005];
int nloop, tot;
bool selfloop[1000005];
long long ans = 0;
void input() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
        deg[u] ^= 1;
        deg[v] ^= 1;
        if (u == v) {
            nloop++;
            selfloop[u]++;
        }
    }
    return;
}
int cur[1000005];
void dfs(int u) {
    for (int i = cur[u]; i >= 0; --i) {
        int bar = cur[u];
        cur[u]--;
        dfs(G[u][bar]);
        if(cur[u] == -1) break;
    }
    return;
}
void solve() {
    for (int i = 1; i <= n; ++i)
        cur[i] = (int) G[i].size() - 1;
    for (int i = 1; i <= n; ++i) 
        if (G[i].size()) {
            dfs(i);
            break;
        }

    for (int i = 1; i <= n; ++i)
        if (cur[i] != -1)
            return;
    
    for (int i = 1; i <= n; ++i) {
        int ndeg = G[i].size() - selfloop[i] * 2;
        ans += 1LL * ndeg * (ndeg - 1) / 2;
    }

    ans += 1LL * nloop * (m - nloop);
    ans += 1LL * nloop * (nloop - 1) / 2;
    return;
}
int main() {
    input();
    solve();
    printf("%lld\n", ans);
    return 0;
}