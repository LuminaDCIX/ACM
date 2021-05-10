#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int N;
int Height, DP[35][4], kase;
int Towers[35][4];

void Get(int &l, int &w, int v, int k) {
    if(k == 0) {l = Towers[v][1], w = Towers[v][2];}
    if(k == 1) {l = Towers[v][0], w = Towers[v][2];}
    if(k == 2) {l = Towers[v][0], w = Towers[v][1];}
}

int dfs(int v, int h) {
    int &res = DP[v][h];
    if(DP[v][h] > 0) return res;
    int l ,w;
    Get(l, w, v, h);
    for(int j = 1; j <= N; j ++)
        for(int k = 0; k < 3; k ++) {
            if((l > Towers[j][0] && w > Towers[j][1]) || (w > Towers[j][0] && l > Towers[j][1])) res = max(dfs(j, 2), res);
            if((l > Towers[j][1] && w > Towers[j][2]) || (w > Towers[j][1] && l > Towers[j][2])) res = max(dfs(j, 0), res);
            if((l > Towers[j][0] && w > Towers[j][2]) || (w > Towers[j][0] && l > Towers[j][2])) res = max(dfs(j, 1), res);
        }
    res += Towers[v][h];
    return DP[v][h] = res;
}

void solve() {
    int l, w, ans = 0;
    for(int i = 1; i <= N; i ++)
        for(int j = 0; j < 3; j ++) ans = max(ans, dfs(i, j));
    printf("Case %d: maximum height = %d\n", ++kase, ans);
}



void input() {
    int a, b, c;
    memset(DP, 0, sizeof(DP));
    for(int i = 1; i <= N; i ++) scanf("%d %d %d", &Towers[i][0], &Towers[i][1], &Towers[i][2]);
    return;
}

int main() {
    while(scanf("%d", &N) && N) {
        input();
        solve();
    }
    return 0;
}