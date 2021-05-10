#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int N, T, M1, M2, DP[55][205], Time[55][55], Has_train[55][205][2], kase;
int main() {
    while(scanf("%d", &N) && N) {
    scanf("%d", &T);
    int tem = 0;
    memset(DP, 0, sizeof(DP));
    memset(Has_train, 0, sizeof(Has_train));
    for(int i = 1; i <= N - 1; i ++) {
        scanf("%d", &tem);
        Time[i][i + 1] = tem;
        Time[i + 1][i] = tem;
    }
    scanf("%d", &M1);
    for(int i = 1; i <= M1; i ++) {
        scanf("%d", &tem);
        int tot = tem;
        for(int i = 1; i <= N; i ++) {
            Has_train[i][tot][1] = 1;
            tot += Time[i][i + 1];
            if(tot > T) break;
        }
    }
    scanf("%d", &M2);
    for(int i = 1; i <= M2; i ++) {
        scanf("%d", &tem);
        int tot = tem;
        for(int i = N; i >= 0; i --) {
            Has_train[i][tot][0] = 1;
            tot += Time[i][i - 1];
            if(tot > T) break;
        }
    }
    for(int i = 0; i <= T; i ++) DP[N][i] = 0x3f3f3f3f;
    for(int i = 1; i <= N; i ++) DP[i][T] = 0x3f3f3f3f;
    DP[N][T] = 0;
    for(int t = T - 1; t >= 0; t --){
        for(int i = 1; i <= N; i ++) {
            DP[i][t] = DP[i][t + 1] + 1;
            if(i < N && t + Time[i][i + 1] <= T && Has_train[i][t][1]) DP[i][t] = min(DP[i][t], DP[i + 1][t + Time[i][i + 1]]);
            if(i > 1 && t + Time[i][i - 1] <= T && Has_train[i][t][0]) DP[i][t] = min(DP[i][t], DP[i - 1][t + Time[i][i - 1]]);
        }
    }
    printf("Case Number %d: ", ++kase);
    if(DP[1][0] < 0x3f3f3f3f) printf("%d\n", DP[1][0]);
    else printf("impossible\n");
    }
    return 0;
}