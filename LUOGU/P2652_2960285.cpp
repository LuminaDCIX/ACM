#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
vector<int> v[N];
map<int, int> id;
int cnt;
int n;

int main() {
	scanf("%d", &n);
	for (int i = 0, x, y; i < n; ++i) {
		scanf("%d%d", &x, &y);
		if (id[x] == 0) {
			id[x] = ++cnt;	
		}
		x = id[x];
		v[x].push_back(y);
	}
	int ans = n - 1;
	for (int i = 1; i <= cnt; ++i) {
		sort(v[i].begin(), v[i].end());
		int len = unique(v[i].begin(), v[i].end()) - v[i].begin();
		int l = 0;
		int r = 0;
		int use = 1;
		int tot = 0;
		while (l <= r && r < len - 1) {
			ans = min(ans, n - (r - l + 1));
			while (l < r && v[i][r + 1] - v[i][r] > n - use) {
				use -= v[i][l + 1] - v[i][l];
				++l;
			}
			if (v[i][r + 1] - v[i][r] <= n - use) {
				use += v[i][r + 1] - v[i][r];
				++r;
			}
			else {
				l = r = r + 1;
				if (r >= len) {
					break;	
				}
				use = v[i][r] - v[i][l] + 1;
			}
			ans = min(ans, n - (r - l + 1));
		}
	}
	printf("%d\n", ans);	
	return 0;
}