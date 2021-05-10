#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;
int Length[55], DP[55][9010], N, K, T, kase;

bool cmp(int a, int b) {
    return a > b;
}
void input() {
    scanf("%d %d", &N, &T);
    for(int i = 1; i <= N; i ++) scanf("%d", &Length[i]);
    sort(Length + 1, Length + N + 1, cmp);
}

void solve() {
    for(int n = 1; n <= N; n ++) 
      for(int t = Length[n]; t <= min(T, N * 180); t ++) {
          if(DP[n - 1][t] > 0) DP[n][t] =max(DP[n - 1][t], DP[n][t]);
          if(t == Length[n]) DP[n][t] = max(DP[n][t], DP[n - 1][t - Length[n]] + 1);
          if(DP[n - 1][t - Length[n]] > 0) DP[n][t] = max(max(DP[n - 1][t - Length[n]] + 1, DP[n - 1][t]), DP[n][t]);
      }
}
int main() {
    scanf("%d", &K);
    while(K --) {
        memset(DP, 0, sizeof(DP));
        input();
        solve();
        int num = 0, res = 0;
        if(T <= N * 180) {
            for(int i = 0; i < T; i ++) {
                if(DP[N][i] >= num) num = DP[N][i], res = i;
            }
        } else {
            for(int i = 0; i <= N * 180; i ++) {
                if(DP[N][i] >= num) num = DP[N][i], res = i;
            }
        }
        
        //for(int i = 1; i <= N; i ++, putchar('\n'))
        //    for(int j = 1; j <= T; j ++) printf("%d %d ", j, DP[i][j]);
        printf("Case %d: %d %d\n", ++ kase, (num == 0) ? 1 : num + 1,(num == 0)? 678 : res + 678);
    }
    return 0;
}