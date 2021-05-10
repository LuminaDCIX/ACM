#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
 
using namespace std;
 
#define pb push_back
#define siz(x) ((int) x.size()) 
#define fil(a, x) memset(a, x, sizeof(a))
typedef vector <int> vi;
 
const int N = 2e4 + 5;
const int M = 3e5 + 5;
const int MAX = M << 2;
const int SIZ = 26;
 
int read() {
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
 
struct graph {
    int head[M], nxt[M], ver[M];
    int tot;
 
    void init() {
        fil(head, 0);
        tot = 0;
    }
 
    void add(int u, int v) {
        ++tot;
        ver[tot] = v;
        nxt[tot] = head[u];
        head[u] = tot;
    }
    
    int dfn[M], ext[M], dfs_cnt;
 
    void dfs(int u) {
        dfn[u] = ++dfs_cnt;
        for (int o = head[u]; o; o = nxt[o]) {
            int v = ver[o];
            dfs(v);
        }
        ext[u] = dfs_cnt;
    }
 
    void build() {
        dfs_cnt = 0;
        dfs(1);
    }
} g;
 
struct sgt {
    #define lc (o << 1)
    #define rc (o << 1 | 1)
    #define mid ((ll + rr) >> 1)
 
    int mx[MAX];
 
    void build(int o, int ll, int rr) {
        mx[o] = 0;
        if (ll == rr) return;
        build(lc, ll, mid);
        build(rc, mid + 1, rr);
    }
 
    void down(int o) {
        mx[lc] = max(mx[lc], mx[o]);
        mx[rc] = max(mx[rc], mx[o]);
    }
 
    int qry(int o, int ll, int rr, int p) {
        if (ll == rr) return mx[o];
        down(o);
        if (p <= mid) return qry(lc, ll, mid, p);
        else return qry(rc, mid + 1, rr, p);
    }
 
    void mod(int o, int ll, int rr, int l, int r, int v) {
        if (ll >= l && rr <= r) {
            mx[o] = max(mx[o], v);
            return;
        }
        down(o);
        if (l <= mid) mod(lc, ll, mid, l, r, v);
        if (r > mid) mod(rc, mid + 1, rr, l, r, v);
    }
} s;
 
vi pos[N];
 
struct acm {
 
    int tot;
    int nxt[M][SIZ], fail[M];
 
    void init() {
        fil(nxt, 0);
        fil(fail, 0);
        tot = 1;
    }
 
    vi ins(char *s) {
        int len = strlen(s + 1);
        int nw = 1;
        vi ret;
        for (int i = 1; i <= len; ++i) {
            int x = s[i] - 'a';
            if (nxt[nw][x] == 0) nxt[nw][x] = ++tot;
            nw = nxt[nw][x];
            ret.pb(nw);
        }
        return ret;
    }
 
    void build() {
        queue <int> que;
        for (int i = 0; i < SIZ; ++i) {
            if (nxt[1][i]) {
                int p = nxt[1][i];
                fail[p] = 1;
                que.push(p);
            }
        }
        while (!que.empty()) {
            int x = que.front();
            que.pop();
            for (int i = 0; i < SIZ; ++i) {
                if (nxt[x][i]) {
                    int p = nxt[x][i];
                    int q = fail[x];
                    while (q && nxt[q][i] == 0) q = fail[q];
                    if (nxt[q][i]) fail[p] = nxt[q][i];
                    else fail[p] = 1;
                    que.push(p);
                }
            }
        }
        g.init();
        for (int i = 2; i <= tot; ++i) {
            g.add(fail[i], i);
        }
    }
} a;
 
char str[M];
int dp[N], w[N];
int ttt;
 
void solve() {
    int n = read();
    a.init();
    for (int i = 1; i <= n; ++i) {
        scanf("%s", str + 1);
        pos[i] = a.ins(str);
        w[i] = read();
    }
    a.build();
    s.build(1, 1, a.tot);
    g.build();
    for (int i = 1; i <= n; ++i) {
        dp[i] = 0;
        for (int j = 0; j < siz(pos[i]); ++j) {
            int k = pos[i][j];
            dp[i] = max(dp[i], s.qry(1, 1, a.tot, g.dfn[k]) + w[i]);
        }
        int k = pos[i].back();
        s.mod(1, 1, a.tot, g.dfn[k], g.ext[k], dp[i]);
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) ans = max(ans, dp[i]);
    cout << "Case #" << ++ttt << ": ";
    cout << ans << endl;
}
 
int main() {
    int T = read();
    while (T--) solve();
    return 0;
} 