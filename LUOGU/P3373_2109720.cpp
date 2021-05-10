#include <cstdio>
#include <algorithm>
using namespace std;
#define lson (o << 1)
#define rson (o << 1 | 1)
#define M (t[o].l + ((t[o].r - t[o].l) >> 1))
typedef long long ll;
ll n, m, p, x, sum;
struct node {
    ll v, mul, add, l, r;
}t[(100000 * 4) + 10];

void read(ll &x)
{
    char c = getchar(); x = 0;
    while (c < '0' || c > '9') c = getchar();
    while (c <= '9' && c >= '0') x = x * 10 + c - 48, c = getchar();
}

void build(ll o, ll l, ll r) {
    t[o].l = l, t[o].r = r;
    t[o].mul = 1, t[o].add = 0;
    if (l == r) {
        scanf("%lld", &t[o].v);
        t[o].v = t[o].v % p;
        return;
    } else {
        build(lson, l, M);
        build(rson, M + 1, r);
    }
    t[o].v = (t[lson].v + t[rson].v) % p;
}
void pushdown(ll o, ll l, ll r) {
    if (t[o].l == t[o].r) {t[o].add = 0; t[o].mul = 1; return;}
    t[lson].v = (((t[lson].v* t[o].mul) + (((t[lson].r - t[lson].l + 1)) * t[o].add))) % p;
    t[rson].v = (((t[rson].v* t[o].mul) + (((t[rson].r - t[rson].l + 1)) * t[o].add))) % p;
    t[lson].add = (((t[lson].add * t[o].mul) ) + t[o].add) % p;
    t[rson].add = (((t[rson].add * t[o].mul) ) + t[o].add) % p;
    t[lson].mul = (t[lson].mul * t[o].mul) % p;
    t[rson].mul = (t[rson].mul * t[o].mul) % p;
    t[o].add = 0, t[o].mul = 1;
}
void maintain(ll o) {
    if(t[o].l != t[o].r) t[o].v = (t[lson].v + t[rson].v) % p;
}
void query(ll o, ll l,ll r) {
    pushdown(o, l, r);
    if (l == t[o].l && r == t[o].r) {
        sum = (t[o].v + sum) % p;
    } else {
        if (l <= M)query(lson, l, min(M, r));
        if (r > M)query(rson, max(l,M + 1), r);
        maintain(o);
    }
}
void add_x(ll o, ll l, ll r) {
    //printf("%lld %lld %lld\n", o, l, r);
    pushdown(o, l, r);
    if (l == t[o].l && r == t[o].r) {
        t[o].add = x % p;
        t[o].v = ((x * (r - l + 1) + t[o].v) % p);
    } else {
        if(l <= M)add_x(lson, l, min(M, r));
        if(r > M )add_x(rson, max(l, M + 1), r);
        maintain(o);
    }
}
void mul_x(ll o, ll l, ll r) {
    pushdown(o, l, r);
    if (l == t[o].l && r == t[o].r) {
        t[o].v = ((t[o].v + t[o].add * (r - l + 1) ) % p) * (x) % p;t[o].mul = x % p;
    } else {
        if (l <= M)mul_x(lson, l, min(M, r));
        if (r > M)mul_x(rson, max(l, M + 1), r);
        maintain(o);
    }
}
int main() {
    read(n), read(m), read(p);
    build(1, 1, n);
    ll l, r;
    for (int i = 1; i <= m; i++) {
        int q; scanf("%d", &q);
        if (q == 2) {
            read(l), read(r), read(x);
            add_x(1, l, r);
        }
        else if (q == 1) {
            read(l), read(r), read(x);
            mul_x(1, l, r);
        }
        else {
            sum = 0;
            read(l), read(r);
            query(1, l, r);
            printf("%lld\n", sum);
        }
    }
    //system("pause");
}