#include <cstdio>
#include <cstring>
#include <algorithm>
#define lowbit(x) (x&-x)
using namespace std;
int N, M;
int root;
struct edge{
        int to, val, nxt;
}e[80005];
int head[40005], tot;
int amt;
void Add(int from, int to, int val) {
        e[++tot].to = to;
        e[tot].val = val;
        e[tot].nxt = head[from];
        head[from] = tot;
}
namespace BIT {
        int t[500009];
        const int maxn = 500005;
        int sum(int x) {
                int res = 0;
                while(x > 0) {
                        res += t[x];
                        x -= lowbit(x);
                }
                return res;
        }
        void t_add(int x, int val) {
                while(x <= maxn) {
                        t[x] += val;
                        x += lowbit(x);
                }
                return;
        }
}
using namespace BIT;
namespace LCA {
        int dep[40005];
        int id[40005];
        int pre[40005][40];
        void dfs(int u, int fa) {
                id[u] = amt;
                for (int i = head[u]; i; i = e[i].nxt) {
                        int v = e[i].to;
                        if (v == fa) continue;
                        if (!dep[v]) {
                                dep[v] = dep[u] + 1;
                                pre[v][0] = u;
                                t_add(++amt, e[i].val);
                                dfs(v, u);
                                t_add(++amt, -e[i].val);
                        }
                }
                return;
        }
        void init() {
                memset(pre, -1, sizeof(pre));
                for (int i = 1; i <= N; i++) if(!dep[i]) dfs(i, -1);
                for (int j = 1; (1 << j) <= N; j++) {
                        for (int i = 1; i <= N; i++) {
                                if(pre[i][j - 1] != -1) {
                                        pre[i][j] = pre[pre[i][j - 1]][j - 1];
                                }
                        }
                }
                return;
        }
        int lca(int a, int b) {
                if (dep[a] < dep[b]) swap(a, b);
                for (int i = 20; i >= 0; i--) {
                        if (dep[pre[a][i]] >= dep[b]) a = pre[a][i];
                }
                if (a == b) return a;
                for (int j = 20; j >= 0; j--) {
                        if ((pre[a][j] != -1)&&(pre[a][j] != pre[b][j])) {
                                a = pre[a][j];
                                b = pre[b][j];
                        }
                }
                return pre[a][0];
        }
}
using namespace LCA;
void input() {
        for (int i = 1; i <= M; i++) {
                int f, t, v;
                scanf("%d%d%d", &f, &t, &v);
                getchar();
                char p = getchar();
                Add(f, t, v);
                Add(t, f, v);
        }
        return;
}
void solve() {
        init();
        int k;
        scanf("%d", &k);
        while (k--) {
                int a, b;
                scanf("%d%d", &a, &b);
                int f = lca(a, b);
                printf("%d\n", -(sum(id[f]) << 1) + sum(id[a]) + sum(id[b]));
        }
        return;
}
int main() {
        scanf("%d%d", &N, &M);
        input();
        solve();
        return 0;
}
