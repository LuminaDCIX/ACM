#include <bits/stdc++.h>
using namespace std;
namespace DEFINE {
#define FI first
#define SE second
#define PB push_back
#define MP make_pair
#define SIZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define SET(x,v) memset(x,v,sizeof(x))
#define FORG(o,u) for (int o=head[u];o;o=nxt[o])
#define PER(i,a,n) for (int i=(n),_ed##i=(a);i>=_ed##i;--i)
#define REP(i,a,n) for (int i=(a),_ed##i=(n);i<=_ed##i;++i)
#define FOREACH(it,s) for (typeof__ it=(s).begin();it!=(s).end();++it)
typedef double DB;
typedef long long LL;
typedef vector<int> VI;
typedef pair<int, int> PII;
const int P = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
inline int ADD(int u, int v) {
    return (u += v) >= P ? u - P : u;
}
inline int SUB(int u, int v) {
    return (u -= v) < 0 ? u + P : u;
}
inline int MUL(int u, int v) {
    return (LL)u * v % P;
}
inline int EXP(int a, LL x) {
    int ret = 1;

    while (x) {
        if (x & 1)
            ret = MUL(ret, a);

        a = MUL(a, a);
        x >>= 1;
    }

    return ret;
}
inline LL read() {
    LL x = 0;
    int f = 1, ch = getchar();

    for (; ch < '0' || ch > '9'; ch = getchar())
        f = (ch == '-') ? -1 : 1;

    for (; ch >= '0' && ch <= '9'; ch = getchar())
        x = x * 10 + ch - '0';

    return f * x;
}
inline void FILEIO(string s) {
    freopen((s + "in").c_str(), "r", stdin);
    freopen((s + "out").c_str(), "w", stdout);
}
}
using namespace DEFINE;

const int N = 100000 + 5;

LL A, B, C;
int n, m;
int a[N], t[N];
int suma[N], sumt[N];

int main() {
    A = read();
    B = read();
    C = read();
    n = read();
    m = read();
    REP(i, 1, n) t[i] = read();
    REP(i, 1, m) a[i] = read();
    int M = 100000;
    LL cnt1 = 0, cnt2 = 0;
    LL S = 0;
    int lim = 100000;
    REP(i, 1, m) cnt2 += M - a[i];
    REP(i, 1, n) S += M - t[i];
    REP(i, 1, n) ++sumt[t[i]];
    REP(i, 1, lim) sumt[i] += sumt[i - 1];
    REP(i, 1, m) ++suma[a[i]];
    REP(i, 1, lim) suma[i] += suma[i - 1];
    LL ans = 2e18;
    REP(i, 0, lim) {
        if (C <= 1e15 || (C > 1e15 && S == 0)) {
            if (cnt1 <= cnt2) {
                ans = min(ans, S * C + cnt1 * min(A, B));
            } else {
                if (B <= A)
                    ans = min(ans, S * C + cnt1 * B);
                else
                    ans = min(ans, S * C + cnt2 * A + (cnt1 - cnt2) * B);
            }
        }

        --M;
        cnt2 -= suma[M];
        cnt1 += suma[lim] - suma[M];
        S -= sumt[M];
    }
    printf("%lld\n", ans);
    return 0;
}
