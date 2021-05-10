// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include <ctime>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define siz(x) ((int) x.size())
#define clr(x) memset(x, 0, sizeof(x))
typedef long long ll;
typedef vector <int> vi;
typedef pair <int, int> pii;

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

const int N = 50000 + 5;
const int M = 100000 + 5;
const int SIZ = 27;


int n, m, B;
ll ans = 0;

struct sam {
    char str[M];
    int nxt[M][SIZ], fa[M], len[M], rt[M], siz[M];
    int lst, tot;

    inline int nw(int x) {
        ++tot;
        len[tot] = x;
        return tot;
    }

    void extend(int x, int r) {
        int p = lst;
        int np = nw(len[p] + 1);
        while (p && nxt[p][x] == 0) {
            nxt[p][x] = np;
            p = fa[p];
        }
        if (!p) fa[np] = 1;
        else {
            int q = nxt[p][x];
            if (len[q] == len[p] + 1) fa[np] = q;
            else {
                int nq = nw(len[p] + 1);
                fa[nq] = fa[q];
                fa[q] = fa[np] = nq;
                memcpy(nxt[nq], nxt[q], sizeof(nxt[q]));
                while (p && nxt[p][x] == q) {
                    nxt[p][x] = nq;
                    p = fa[p];
                }
            }
        }
        lst = np;
        siz[np] = 1;
        rt[np] = r;
    }

    void init(char *s) {
        memcpy(str, s, sizeof(str));
        lst = 1;
        tot = 1;
        int l = m;
        str[++l] = 'a' + 26;
        reverse(str + 1, str + l + 1);
        for (int i = 1; i <= l; ++i) extend(str[i] - 'a', i);
    }

    int q[M], c[N];

    void build() {
        for (int i = 2; i <= tot; ++i) ++c[len[i]];
        for (int i = 1; i <= m + 1; ++i) c[i] += c[i - 1];
        for (int i = 2; i <= tot; ++i) q[c[len[i]]--] = i;
        for (int i = tot - 1; i >= 1; --i) {
            int x = q[i];
            siz[fa[x]] += siz[x];
            rt[fa[x]] = max(rt[fa[x]], rt[x]);
        }
    }

    int go(int &nw, int x) {
        if (!nxt[nw][x]) return -1;
        nw = nxt[nw][x];
        return siz[nw];
    }
} s1, s2;

struct stree {

    int head[M], ver[M], nxt[M];
    int be[M], ed[M];

    char str[M];

    int pos[M], tot;

    void add(int u, int v, int l, int r) {
        ++tot;
        ver[tot] = v;
        nxt[tot] = head[u];
        be[tot] = l;
        ed[tot] = r;
        head[u] = tot;
    }

    int jmp[M][SIZ];

    void getnxt(int u) {
        for (int o = head[u]; o; o = nxt[o]) {
            int v = ver[o];
            jmp[u][str[be[o]] - 'a'] = o;
            getnxt(v);
        }
    }

    void build(sam &s, char *ss) {
        memcpy(str, ss, sizeof(str));
        str[m + 1] = 'a' + 26;
        for (int i = 2; i <= s.tot; ++i) {
            int l = s.rt[i] - s.len[i] + 1;
            int r = s.rt[i] - s.len[s.fa[i]];
            --l, --r;
            int nl = m - r + 1;
            int nr = m - l + 1;
            add(s.fa[i], i, nl, nr);
            pos[i] = m - s.rt[i] + 2;
        }
        getnxt(1);
    }

    int cnt[M], tag[M];

    void init() {
        ver[0] = 1;
        clr(cnt);
        clr(tag);
    }

    void go(pii &nw, int x) {
        if (nw.fi == -1) return;
        if (nw.fi == ed[nw.se]) {
            int v = ver[nw.se];
            v = jmp[v][x];
            if (v == 0) nw = mp(-1, 0);
            else nw = mp(be[v], v);
        } else {
            if (str[nw.fi + 1] - 'a' == x) ++nw.fi;
            else nw = mp(-1, 0);
        }
    }

    void push(int u, int sum) {
        sum += tag[u];
        if (head[u] == 0) cnt[pos[u]] = sum;
        for (int o = head[u]; o; o = nxt[o]) push(ver[o], sum);
    }

} t1, t2;

int head[N], nxt[M], ver[M];

void add(int u, int v) {
    static int tot = 0;
    ++tot;
    nxt[tot] = head[u];
    ver[tot] = v;
    head[u] = tot;
}

char s[N];
int jry[N];

bool vis[N];

namespace solve1 {
    vi r;

    void init(int u, int fa) {
        r.pb(u);
        for (int o = head[u]; o; o = nxt[o]) {
            int v = ver[o];
            if (vis[v] || v == fa) continue;
            init(v, u);
        }
    }

    void dfs(int u, int fa, int rt) {
        int k = s1.go(rt, jry[u]);
        if (k == -1) return;
        ans += k;
        for (int o = head[u]; o; o = nxt[o]) {
            int v = ver[o];
            if (vis[v] || v == fa) continue;
            dfs(v, u, rt);
        }
    }

    void solve(int x) {
        r.clear();
        init(x, 0);
        for (int i = 0; i < siz(r); ++i) dfs(r[i], 0, 1);
    }
}

namespace solve2 {

    void dfs(int u, int fa, pii pos1, pii pos2) {
        t1.go(pos1, jry[u]);
        t2.go(pos2, jry[u]);
        if (pos1.fi != -1) ++t1.tag[t1.ver[pos1.se]];
        if (pos2.fi != -1) ++t2.tag[t2.ver[pos2.se]];
        if (pos1.fi == -1 && pos2.fi == -1) return;
        for (int o = head[u]; o; o = nxt[o]) {
            int v = ver[o];
            if (v == fa || vis[v]) continue;
            dfs(v, u, pos1, pos2);
        }
    }

    void solve(int x) {
        t1.init();
        t2.init();
        dfs(x, 0, mp(0, 0), mp(0, 0));
        t1.push(1, 0);
        t2.push(1, 0);
    }
}

namespace solve3 {

    vi r;

    void init(int u, int fa) {
        r.pb(u);
        for (int o = head[u]; o; o = nxt[o]) {
            int v = ver[o];
            if (vis[v] || v == fa) continue;
            init(v, u);
        }
    }

    int anc, fanc;

    void dfs(int u, int fa, int rt) {
        int k = s1.go(rt, jry[u]);
        if (k == -1) return;
        ans -= k;
        for (int o = head[u]; o; o = nxt[o]) {
            int v = ver[o];
            if (vis[v] || v == fa) continue;
            dfs(v, u, rt);
        }
    }

    int getpos(int u, int fa, int rt) {
        int k = s1.go(rt, jry[u]);
        if (k == -1) return -1;
        if (u == anc) {
            k = s1.go(rt, jry[fanc]);
            if (k == -1) return -1;
            return rt;
        }
        for (int o = head[u]; o; o = nxt[o]) {
            int v = ver[o];
            if (vis[v] || v == fa) continue;
            int k = getpos(v, u, rt);
            if (k != -1) return k;
        }
        return -1;
    }


    void solve(int x, int fax) {
        fanc = fax;
        anc = x;
        r.clear();
        init(x, 0);
        for (int i = 0; i < siz(r); ++i) {
            int rt = getpos(r[i], 0, 1);
            if (rt == -1) continue;
            dfs(x, 0, rt);
        }
    }
}

namespace divide {
    int root, siz[N], all, dp[N];

    void fdrt(int u, int fa) {
        siz[u] = 1;
        dp[u] = 0;
        for (int o = head[u]; o; o = nxt[o]) {
            int v = ver[o];
            if (v == fa || vis[v]) continue;
            fdrt(v, u);
            siz[u] += siz[v];
            dp[u] = max(dp[u], siz[v]);
        }
        dp[u] = max(dp[u], all - siz[u]);
        if (root == 0 || dp[u] < dp[root]) root = u;
    }

    void dfs(int u, int fa) {
        siz[u] = 1;
        for (int o = head[u]; o; o = nxt[o]) {
            int v = ver[o];
            if (v == fa || vis[v]) continue;
            dfs(v, u);
            siz[u] += siz[v];
        }
    }

    void solve(int x, int tot) {
        if (tot <= B) {
            solve1::solve(x);
            return;
        }

        all = tot;
        root = 0;
        fdrt(x, 0);
        vis[root] = 1;
        dfs(root, 0);
        solve2::solve(root);
        for (int i = 1; i <= m; ++i) ans += (ll) t1.cnt[i] * t2.cnt[m - i + 1];
        for (int o = head[root]; o; o = nxt[o]) {
            int v = ver[o];
            if (vis[v]) continue;
            if (siz[v] > B) {
                solve2::solve(v);
                for (int i = 1; i <= m; ++i) {
                    if (s[i] - 'a' != jry[root] || i + 1 > m || m - i + 2 < 1) continue;
                    ans -= (long long) t1.cnt[i + 1] * t2.cnt[m - i + 2];
                }
            } else {
                solve3::solve(v, root);
            }
        }
        for (int o = head[root]; o; o = nxt[o]) {
            int v = ver[o];
            if (vis[v]) continue;
            solve(v, siz[v]);
        }
    }
}

int main() {
    n = read();
    m = read();
    B = 300;
    for (int i = 0; i < n - 1; ++i) {
        int u = read();
        int v = read();
        add(u, v);
        add(v, u);
    }
    scanf("%s", s + 1);
    for (int i = 1; i <= n; ++i) jry[i] = s[i] - 'a';
    scanf("%s", s + 1);
    s2.init(s);
    reverse(s + 1, s + m + 1);
    s1.init(s);
    reverse(s + 1, s + m + 1);
    s1.build();
    s2.build();
    t1.build(s2, s);
    reverse(s + 1, s + m + 1);
    t2.build(s1, s);
    reverse(s + 1, s + m + 1);
    divide::solve(1, n);
    cout << ans << endl;
    return 0;
}