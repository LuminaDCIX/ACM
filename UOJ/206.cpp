#include "gap.h"
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 100000 + 5;

typedef long long ll;

ll a[N];

namespace solve1 {
    ll solve(int n) {
        ll l = 0;
        ll r = 1e18;
        for (int i = 1; i <= (n + 1) / 2; ++i) {
            ll mn, mx;
            MinMax(l, r, &mn, &mx);
            a[i] = mn;
            a[n - i + 1] = mx;
            l = mn + 1;
            r = mx - 1;
        }
        ll ans = 0;
        for (int i = 2; i <= n; ++i) ans = max(ans, a[i] - a[i - 1]);
        return ans;
    }
}

namespace solve2 {

    ll a[N + N + 5];

    ll solve(int n) {
        ll l = 0;
        ll r = 1e18;
        ll mn, mx;
        MinMax(l, r, &mn, &mx);
        l = mn + 1;
        r = mx - 1;
        ll pmn = mn;
        ll pmx = mx;
        if (n - 2 == 0) return pmx - pmn;
        ll len = ceil((r - l + 1) / (1.0 * (n - 2)));
        int tot = 0;
        for (ll i = l; i <= r; i += len) {
            ll low = i;
            ll high = min(i + len - 1, r);
            MinMax(low, high, &mn, &mx);
            if (mn == -1) continue;
            a[++tot] = mn;
            a[++tot] = mx;
        }
        ll ans = 0;
        for (int i = 2; i <= tot; ++i) ans = max(ans, a[i] - a[i - 1]);
        ans = max(ans, a[1] - pmn);
        ans = max(ans, pmx - a[tot]);
        return ans;

    }
}

long long findGap(int T, int n) {
    if (T == 1) return solve1::solve(n);
    else return solve2::solve(n);
    return 0;
}
