#include <cstdio>
#include <iostream>
#include <cstring>
#define p 4880
using namespace std;
int w[35], len[35], G, C;
int dp[26][10000];
void print(int x) {
	for (int i = 1; i <= 9999; i ++) {
		if (dp[x][i] != 0)
			printf("%d i = %d ", dp[x][i], i);
	}
	printf("\n");
}
int main() {
	scanf("%d %d",&C, &G);
	for (int i = 1; i <= C; i ++) {
		scanf("%d", &len[i]);
	}
	for (int i = 1; i <= G; i ++) {
		scanf("%d", &w[i]);
	}
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= C; i ++) dp[1][len[i] * w[1] + p] ++;
	//print(1); 
	for (int i = 2; i <= G; i ++) {
		for (int v = -4880; v <= 4880; v ++) {
			for (int k = 1; k <= C; k ++) {
				int& ans = dp[i - 1][v - w[i] * len[k] + p];
				//if(ans != 0)printf("%d\n",v);
				dp[i][v + p] += ans;
			}
			//putchar('\n'); 
		}
		//print(i);
	}
	printf("%d",dp[G][p]);
}