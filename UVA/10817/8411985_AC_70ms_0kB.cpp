#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#define pb push_back
#define INF 6000010
using namespace std;

int N,M,S;
int cost[125],DP[125][1<<8][1<<8];
int lesn[125];

int dp(int i,int s1,int s2) {
    int &res=DP[i][s1][s2];
    if(i==M+N+1) return (1<<S)-1==s2?0:INF;
    if(res>=0) return res;
    int s0=((1<<S)-1)^s1^s2,s1t=s1^(s1&lesn[i])|(s0&lesn[i]),s2t=s2|(lesn[i]&s1);
    if(i<=M) {
        res=dp(i+1,s1t,s2t)+cost[i];
    } else {
        res=dp(i+1,s1,s2);
        res=min(res,cost[i]+dp(i+1,s1t,s2t));
    }
    //printf("i=%d s0=%d s1=%d s2=%d lesn=%d res=%d\n",i,s0,s1,s2,lesn[i],res);
    return res;
}


/*
    s0=(1<<S)^s1^s2;
    s1t一个人教的科目
    s0没人交的科目
*/
void solve() {
    int tem=0;
    for(int i=1;i<=M+N;i++) {
        scanf("%d",&cost[i]);
        lesn[i]=0;
        while(getchar()!='\n') {
            scanf("%d",&tem);
            lesn[i]^=(1<<(tem-1));
        }
    }
    memset(DP,-1,sizeof(DP));
    dp(0,0,0);
    printf("%d\n",DP[0][0][0]);
    return;
}

int main() {
    while(scanf("%d",&S)&&S) {
        scanf("%d%d",&M,&N);
        solve();
    }
}