#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;

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

const int N = 600000 + 5;
const int MAX = N * 2 + 5;

struct heap {
    int lc[MAX], rc[MAX], dist[MAX];
    ll val[MAX];

    int pop(int x) {
        return merge(lc[x], rc[x]);
    }
    
    int merge(int x, int y) {
        if (!x) return y;
        if (!y) return x;
        if (val[x] < val[y]) swap(x, y);
        rc[x] = merge(rc[x], y);
        if (dist[lc[x]] < dist[rc[x]]) swap(lc[x], rc[x]);
        dist[x] = dist[rc[x]] + 1;
        return x;
    }

    ll top(int x) {
        return val[x];
    }

    int nw(ll x) {
        static int tot = 0;
        ++tot;
        val[tot] = x;
        return tot;
    }
} h;

int n, m;

int rt[N];
int p[N], c[N];
int d[N];
ll stk[N];
int top;

int main() {
    n = read();
    m = read();
    ll b = 0;
    for (int i = 2; i <= n + m; ++i) {
        p[i] = read();
        c[i] = read();
        b += c[i];
    }
    h.val[0] = -1e18;
    for (int i = n + m; i >= n + 1; --i) {
        rt[i] = h.merge(h.nw(c[i]), h.nw(c[i]));
        rt[p[i]] = h.merge(rt[p[i]], rt[i]);
        ++d[p[i]];
    }
    for (int i = n; i >= 2; --i) {
        ++d[p[i]];
        while (--d[i]) rt[i] = h.pop(rt[i]);
        ll R = h.top(rt[i]);
        rt[i] = h.pop(rt[i]);
        ll L = h.top(rt[i]);
        rt[i] = h.pop(rt[i]);
        rt[i] = h.merge(rt[i], h.nw(L + c[i]));
        rt[i] = h.merge(rt[i], h.nw(R + c[i]));
        rt[p[i]] = h.merge(rt[p[i]], rt[i]);
    }
    while (rt[1]) {
        stk[++top] = h.top(rt[1]);
        rt[1] = h.pop(rt[1]);
    }

    reverse(stk + 1, stk + 1 + top);
    ll k = d[1] - top;
    ll y = k * stk[1] + b;
    for (int i = 1; k != 0; ++i) {
        b -= stk[i];
        ++k;
        y = stk[i + 1] * k + b;
    }
    cout << y << endl;
    return 0;
}