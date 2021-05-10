// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

namespace XDYIMCMI0LY {

    inline int read() {
        int f = 1, x = 0, ch = getchar();
        for (; !isdigit(ch); ch = getchar()) f = (ch == '-') ? -1 : 1;
        for (; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
        return f * x;
    }

    const int P = 1e9 + 7;
    const int N = 1e6 + 5;

    int n, m;
    void add(int &a, int b) { (a += b) >= P ? a -= P : a; }
    void sub(int &a, int b) { (a -= b) < 0 ? a += P : a; }
    void mul(int &a, int b) { a = (long long) a * b % P; }
    int modexp(int a, long long x) {
        int ret = 1;
        while (x) {
            if (x & 1) mul(ret, a);
            mul(a, a);
            x >>= 1;
        }
        return ret;
    }

    int mu[N];
    int p[N], np[N], tot;
    int f[N], invf[N];
    int g[N], invg[N], pg[N], invpg[N];

    void init() {
        mu[1] = 1;
        for (int i = 2; i < N; ++i) {
            if (!np[i]) p[++tot] = i, sub(mu[i], 1);
            for (int j = 1; j <= tot; ++j) {
                int k = p[j] * i;
                if (k >= N) break;
                np[k] = 1;
                if (i % p[j] == 0) {
                    mu[k] = 0;
                    break;
                } else {
                    mu[k] = mu[i];
                    mul(mu[k], mu[p[j]]);
                }
            }
        }

        f[1] = 1;
        for (int i = 2; i < N; ++i) f[i] = f[i - 1], add(f[i], f[i - 2]);

        for (int i = 1; i < N; ++i) invf[i] = modexp(f[i], P - 2);

        for (int i = 1; i < N; ++i) g[i] = 1;

        for (int i = 1; i < N; ++i) {
            for (int j = 1; i * j < N; ++j) {
                int k = i * j;
                int v;
                if (mu[j] == 1) v = f[i];
                else if (mu[j] == mu[2]) v = invf[i];
                else v = 1;
                mul(g[k], v);
            }
        }


        g[0] = invg[0] = 1;
        pg[0] = 1, invpg[0] = 1;
        for (int i = 1; i < N; ++i) pg[i] = g[i], mul(pg[i], pg[i - 1]);
        for (int i = 1; i < N; ++i) invg[i] = modexp(g[i], P - 2);
        for (int i = 1; i < N; ++i) invpg[i] = invpg[i - 1], mul(invpg[i], invg[i]);
    }


    void solve() {
        if (n > m) swap(n, m);
        int ans = 1;
        for (int d = 1; d <= n; ++d) {
            int vn = n / d, vm = m / d;
            int nxtn = n / vn, nxtm = m / vm;
            int nxt = min(nxtn, nxtm);
            int k = pg[nxt];
            mul(k, invpg[d - 1]);
            long long fac = vn * (long long) vm;
            mul(ans, modexp(k, fac));
            d = nxt;
        }
        cout << ans << endl;
    }


    int _main() {
        init();
        int T = read();
        while (T--) n = read(), m = read(), solve();
        return 0;
    }
}

int main() { return XDYIMCMI0LY::_main(); }