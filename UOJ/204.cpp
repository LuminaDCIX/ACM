#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <vector>

using namespace std;
#define pb push_back
#define all(x) x.begin(), x.end()
#define siz(x) ((int) x.size())
typedef vector <int> vi;

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

const int N = 500 + 5;
const int M = 2000 + 5;
const int P = 1e9 + 7;

inline void add(int &u, int v) {
    (u += v) >= P ? u -= P : u;
}
inline void sub(int &u, int v) {
    (u -= v) < 0 ? u += P : u;
}
inline void mul(int &u, int v) {
    u = (long long) u * v % P;
}

map <int, int> mp;

int a[N], b[N];

int dp[N][M];
int sum[N][M];

bool ok[N][M];
int len[M];

int inv[N];

int main() {
    inv[1] = 1;
    for (int i = 2; i < N; ++i) {
        sub(inv[i], P / i);
        mul(inv[i], inv[P % i]);
    }

    int n = read();
    for (int i = 1; i <= n; ++i) {
        a[i] = read();
        b[i] = read();
    }
    int tot = 0;
    {
        vi v;
        for (int i = 1; i <= n; ++i) {
            v.pb(a[i]);
            v.pb(b[i] + 1);
        }
        sort(all(v));
        v.erase(unique(all(v)), v.end());
        for (int i = 1; i < siz(v); ++i) {
            int l = v[i - 1];
            int r = v[i] - 1;
            if (l <= r) {
                ++tot;
                len[tot] = r - l + 1;
                for (int j = 1; j <= n; ++j) if (l >= a[j] && r <= b[j]) ok[j][tot] = 1;
            }
        }
    }
    dp[0][0] = 1;
    for (int i = 0; i <= tot; ++i) sum[0][i] = 1;
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = 0;
        for (int j = 1; j <= tot; ++j) if (ok[i][j]) {
            int ans = 0;
            int num = -1;
            int binom = 1;
            for (int k = i; k >= 1; --k) {
                if (ok[k][j]) {
                    ++num;
                    mul(binom, inv[num + 1]);
                    mul(binom, (len[j] + num) % P);
                }
                int nw = sum[k - 1][j - 1];
                mul(nw, binom);
                add(ans, nw);
            }
            dp[i][j] = ans;
        }
        sum[i][0] = dp[i][0];
        for (int j = 1; j <= tot; ++j) {
            sum[i][j] = sum[i][j - 1];
            add(sum[i][j], dp[i][j]);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= tot; ++j) add(ans, dp[i][j]);
    }
    cout << ans << endl;
    return 0;
}