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

    const int N = 100000 + 5;

    int n, m;

    struct P *E;
    struct P {
        P *lc, *rc;
        long long sum;
        int cnt;
        inline void* operator new(size_t) {
            static P *S, *T;
            return (S == T && (T = (S = new P[1 << 10]()) + (1 << 10)), S == T) ? 0 : S++;
        }

        P* ins(int ll, int rr, int l, int r, int p) {
            P *t = new P();
            t->lc = lc, t->rc = rc;
            t->cnt = cnt, t->sum = sum;
            if (ll >= l && rr <= r) {
                t->cnt++;
                t->sum += p;
                return t;
            }
            int mid = (ll + rr) / 2;
            if (l <= mid) t->lc = lc->ins(ll, mid, l, r, p);
            if (r > mid) t->rc = rc->ins(mid + 1, rr, l, r, p);
            return t;
        }

        int getcnt(int ll, int rr, int x) {
            if (ll == rr) return cnt;
            int mid = (ll + rr) / 2;
            if (x <= mid) return lc->getcnt(ll, mid, x) + cnt;
            else return rc->getcnt(mid + 1, rr, x) + cnt;
        }

        long long getsum(int ll, int rr, int x) {
            if (ll == rr) return sum;
            int mid = (ll + rr) / 2;
            if (x <= mid) return lc->getsum(ll, mid, x) + sum;
            else return rc->getsum(mid + 1, rr, x) + sum;
        }
    };
    void init() {
        E = new P();
        E->lc = E->rc = E;
        E->cnt = E->sum = 0;
    }

    P *root[N];

    struct atom {
        int l, r, p;
        bool operator < (const  atom &rhs) const {
            return p < rhs.p;
        }
    } a[N];

    inline int getnxt(long long pre) {
        int a = read(), b = read(), c = read();
        return ((long long) a * pre + b) % c + 1;
    }

    inline long long doit(int t, int k) {
        int l = 0, r = n, ans = n;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (root[mid]->getcnt(1, m, t) >= k) r = mid - 1, ans = mid;
            else l = mid + 1;
        }
        return root[ans]->getsum(1, m, t);
    }

    int solve() {
        init();
        n = read(), m = read();
        for (int i = 1; i <= n; ++i) {
            a[i].l = read();
            a[i].r = read();
            a[i].p = read();
        }
        sort(a + 1, a + 1 + n);
        root[0] = E;
        for (int i = 1; i <= n; ++i) {
            root[i] = root[i - 1]->ins(1, m, a[i].l, a[i].r, a[i].p);
        }
        long long pre = 1;
        for (int i = 1; i <= m; ++i) {
            int t =  read();
            int k = getnxt(pre);
            pre = doit(t, k);
            printf("%lld\n", pre);
        }
        return 0;
    }
}

int main() { return XDYIMCMI0LY::solve(); }