#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
typedef long long ll;
int T, s[20010], N, t[100010], c[20010], d[20010];
ll ans;

inline int lowbit(int x) {
    return x & -x;
}

inline void add(int x, int v, int next) {
   if(next == 1) for(x; x <= 100000; x += lowbit(x)) t[x] += v;
   if(next == -1) for(x; x; x -= lowbit(x)) t[x] += v; 
}

inline int sum(int x, int next) {
    int res = 0;
    if(next == 1) for(x; x; x -= lowbit(x)) res += t[x];
    if(next == -1) for(x; x <= 100000; x += lowbit(x)) res += t[x];
    return res;
}
// c smaller than si d bigger than si
void input() {
    ans = 0;
    memset(t, 0, sizeof(t));
    scanf("%d", &N);
    for(int i = 1; i <= N; i ++) {
        scanf("%d", &s[i]);
    }
}

void solve() {
    for(int i = 1; i <= N; i ++) {
        add(s[i], 1, 1);
        c[i] = sum(s[i], 1) - 1;
    }
    memset(t, 0, sizeof(t));
    for(int i = N; i; i --) {
        add(s[i], 1, -1);
        d[i] = sum(s[i], -1) - 1;
    }
    ll ans = 0;
    c[1] = 0, c[N] = N - 1, d[1] = 0, c[N] = N - 1;
    for(int i = 2; i < N; i ++) {
        ans += (1LL * c[i] * d[i] ) + (1LL * (i - c[i] - 1) * (N - d[i] - i)); 
    }
    printf("%lld\n", ans);
}
int main() {
    scanf("%d", &T);
    while(T --) {
        input();
        solve();
    }
    return 0;
}