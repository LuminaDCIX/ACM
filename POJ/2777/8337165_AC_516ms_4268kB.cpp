    #include <cstdio>
    #include <algorithm>
    #include <cstring>
    using namespace std;

    #define lson (o << 1)
    #define rson (o << 1 | 1)
    #define M (t[o].l + (t[o].r - t[o].l) / 2)

    int N, T, Q, check_color[35], res;

    struct SegNode {
        int num, l, r, vis;
    } t[(100000 * 4) + 10];

    void build(int o, int l, int r) {
        t[o].l = l, t[o].r = r;
        t[o].num = 1; t[o].vis = 1;
        if(l == r) return;
        build(lson, l, M);
        build(rson, M + 1, r);
    }

    void maintain(int o) {
        if(t[o].l == t[o].r) return;
        if(t[o].vis >= 1) return;
        if(t[lson].vis == -1|| t[rson].vis == -1 || t[lson].num != t[rson].num) t[o].vis = -1;
        if(t[o].vis == -1) t[o >> 1].vis = -1;
        return;
    }
    void pushdown(int o) {
        if(t[o].l != t[o].r && t[o].vis >= 1) {
            t[lson].num = t[rson].num = t[o].vis;
            t[lson].vis = t[rson].vis = t[o].vis;
        }
    }
    void update(int o, int L, int R, int Color) {
        pushdown(o);
        if(L == t[o].l && R == t[o].r) {
            t[o].num = Color;
            t[o].vis = Color;
            t[o >> 1].vis = -1;
            return;
        }
        if(L <= M) update(lson, L, min(R, M), Color);
        if(R >  M) update(rson, max(L, M + 1), R, Color);
        maintain(o);
    }

    void Sum(int o, int L, int R) {
        if(t[o].vis >= 1 ) {
            check_color[t[o].num] = 1;
            return;
        }
        if(t[o].l == t[o].r) return;
        if(L <= M) Sum(lson, L, min(R, M));
        if(R >  M) Sum(rson, max(L, M + 1), R);
    }

    int main() {
        scanf("%d %d %d", &N, &T, &Q);
        build(1, 1, N);
        while(Q --) {
            getchar();
            char q;
            scanf("%c", &q);
            if(q == 'C') {
                int l, r, c;
                scanf("%d %d %d", &l, &r, &c);
                update(1, min(l, r), max(l, r), c);
            } else {
                int l, r;
                scanf("%d %d", &l, &r);
                memset(check_color, 0, sizeof(check_color));
                Sum(1, min(l, r), max(l, r));
                int ans = 0;
                for(int i = 1; i <= T; i ++) if(check_color[i]) ans ++;
                //for(int i = 0; i <= T; i ++) printf("%d ", check_color[i]);
                printf("%d\n", ans);
            }
        }
    }