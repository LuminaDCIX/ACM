#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 1e5 + 5, maxm = 1e4 + 5, oo = 0x3f3f3f3f;
int n, m;
int cnt;
struct QUERY{
    int x, y, k;
    int id, type;
};
QUERY q[maxn + maxm], q1[maxn + maxm], q2[maxn + maxm];
int bit[maxn];
int ans[maxn];
void add(int i, int x)
{
    while(i <= n){
        bit[i] += x;
        i += i &-i;
    }
}
int sum(int i)
{
    int res = 0;
    while(i){
        res += bit[i];
        i -= i & -i;
    }
    return res;
}
void init()
{
    memset(bit, 0, sizeof(bit));
    cnt = 1;
}
void solve(int ql, int qr, int l, int r)
{
    if(ql > qr) return;
    if(l == r){
        for(int i = ql; i <= qr; i++){
            if(q[i].type == 2) ans[q[i].id] = l;
        }
        return ;
    }
    int m = l + r >> 1;
    int p1 = 0, p2 = 0;
    for(int i = ql; i <= qr; i++){
        if(q[i].type == 1){
            if(q[i].x <= m){
                add(q[i].id, q[i].y);
                 q1[p1++] = q[i];
            }else q2[p2++] = q[i];
        }else{
            int res = sum(q[i].y) - sum(q[i].x - 1);
            if(res >= q[i].k) q1[p1++] = q[i];
            else{
                q[i].k -= res;
                q2[p2++] = q[i];
            }
        }
    }
    //清空标记
    for(int i = 0; i < p1; i++){
        if(q1[i].type == 1) add(q1[i].id, -q1[i].y);
    }
    for(int i = 0; i < p1; i++){
        q[ql + i] = q1[i];
    }
    for(int i = 0; i < p2; i++){
        q[ql + p1 + i] = q2[i];
    }
    solve(ql, ql + p1 - 1, l , m);
    solve(ql + p1, qr, m + 1, r);
}
int main (void)
{
        scanf("%d%d", &n, &m);
        init();
        int x, y, k;
        for(int i = 0; i < n; i++){
            scanf("%d", &x);
            q[cnt++] = (QUERY){x, 1, oo, i + 1, 1};
        }
        for(int i = 0; i < m; i++){
            scanf("%d%d%d", &x, &y, &k);
            q[cnt++] = (QUERY){x, y, k, i + 1, 2};
        }
        solve(1, cnt - 1, -oo, oo);
        for(int i = 1; i <= m; i++){
            printf("%d\n", ans[i]);
        }
        return 0;
}