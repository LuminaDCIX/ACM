#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
int t, n, cnt[105], sum;
struct data{int price, fac;}datas[105][105];
vector<int> buffac;
//每个集合只能选1一
//要使B/P最大 -》 对于每一个确定的B 要使 P 尽可能小 -》 dp[i][j]表示在 前j行，且B不超过i的情况下的最小P											 
int main() {
	cin >> t;
	while (t --) {
		cin >> n;
		buffac.clear();
		for (int i = 1; i <= n; i ++) {
			cin >> cnt[i];
			for (int j = 1; j <= cnt[i]; j ++) {
				cin >> datas[i][j].fac >> datas[i][j].price;
				buffac.push_back(datas[i][j].fac);
			}
		}
		sort(buffac.begin(),buffac.end());
		sum = unique(buffac.begin(),buffac.end()) - buffac.begin();
		//for (int i = 0; i < sum; i ++) cout << buffac[i]<<" ";
		int dp[sum + 5][n + 1]; memset(dp,0,sizeof(dp));
		for (int i = 0; i < sum; i ++) 
			for (int j = 1; j <= n; j ++) dp[i][j] = 0x3f3f3f3f;
		
		//for (int i = 0; i < sum; i ++,puts("")) 
		//	for (int j = 1; j <= n; j ++) cout << dp[i][j] <<" ";
		
		for (int i = 0; i < sum; i ++) {
			for (int j = 1; j <= n; j ++) {
				for (int k = 1; k <= cnt[j]; k ++) {
					if (datas[j][k].fac >= buffac[i])dp[i][j] = min(dp[i][j], dp[i][j-1] + datas[j][k].price);
				}
			}
		}
		
		//for (int i = 0; i < sum; i ++,puts("")) 
		//	for (int j = 1; j <= n; j ++) cout << dp[i][j] <<" ";
			
		double ans = 0.0;
		for (int i = 0; i < sum; i ++)ans = max (ans, 1.0 * buffac[i] / dp[i][n]);
		printf("%.3f\n",ans);
	}
}