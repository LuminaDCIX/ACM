#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iostream>

using namespace std;

const int N = 105;
bool vis[N];
int tot, n;
int len[N];
int tar;

bool dfs(int els, int cnt, int pos) 
{
	if (els == 0) {
		if (cnt == 1) {
			return true;
		}
		return dfs(tar, cnt - 1, 0);
	}
	for (int i = pos; i < n; ++i) {
		if (!vis[i] && len[i] <= els) {
			vis[i] = 1;
			if (dfs(els - len[i], cnt, i)) {
				return true;
			}
				vis[i] = 0;
				if (tar == els) {
					return false;
				}
				while (i + 1 < n && len[i + 1] == len[i]) {
					++i;
				}
		}
	}
	return false;
}
int main()
{
	while (scanf("%d", &n) && n) {
		tot = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &len[i]);
			tot += len[i];
		}
		sort(len, len + n);
		reverse(len, len + n);
		memset(vis, 0, sizeof(vis));
		for (tar = len[0]; ; ++tar) {
			if (tot % tar == 0) {
				if (dfs(tar, tot / tar, 0)) {
					break;
				}
			}
		}
		printf("%d\n", tar);
	}
}
