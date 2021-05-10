#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
ll a[100005];
ll f[100005];
ll sum[100005];
ll mn;
inline Abs(ll x) {
        return x < 0 ? -x : x;
}
int main() {
        int N;
        const ll inf = 10000000000ll;
        scanf("%d", &N);
        for (int i = 1; i <= N; i++) {
                scanf("%lld", &a[i]);
        }
        for (int i = 1; i <= N - 1; ++i) {
                f[i] = Abs(a[i] - a[i + 1]);
        }
        mn = inf;
        ll ans = -inf;
        for (int i = 1; i <= N - 1; ++i) {
                int bar = -1;
                if (i % 2 == 0) bar = 1;
                sum[i] = sum[i - 1] + bar * f[i];
                mn = min(mn, sum[i]);
                ans = max(ans, sum[i] - mn);
                ans = max(ans, sum[i]);
        }
        //for (int i = 1; i <= N - 1; i++) printf("%lld ",sum[i]);
        mn = inf;
        for (int i = 1; i <= N - 1; ++i) {
                int bar = -1;
                if((i % 2)) bar = 1;
                sum[i] = sum[i - 1] + bar * f[i];
                mn = min(mn, sum[i]);
                ans = max(ans, sum[i] - mn);
                ans = max(ans, sum[i]);
        }
        printf("%lld", ans);
        return 0;
}