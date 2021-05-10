#include <bits/stdc++.h>

using namespace std;

const int maxn = 1000;
const int mod = 1e9 + 7;
struct bit {
	int t[maxn + 5];
	inline int sum(int x) {
		int ret = 0;
		while (x) {
			ret = (ret + t[x]) % mod;
			x -= x & -x;
		}
		return ret;
	}
	inline void add(int x, int v) {
		while (x <= maxn) {
			t[x] = (t[x] + v) % mod;
			x += x & -x;
		}
	}
	inline void clear() {
		memset(t, 0, sizeof (t));
	}
}t;
map<int,int> id;
int v[maxn + 5];
int v2[maxn + 5];
int n, m;
int f[maxn + 5][maxn + 5];
int main() {
	int T,kase = 0;
	scanf("%d\n", &T);
	while (T--) {
		memset(f, 0, sizeof(f));
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &v[i]);
			v2[i] = v[i];
		}
		sort(v2, v2 + n);
		int len = unique(v2, v2 + n) - v2;
		id.clear();
		for (int i = 0; i < len; ++i) {
			id[v2[i]] = i + 1;;
		}
		for (int i = 0; i < n; ++i) {
			v[i] = id[v[i]];
		}
		for (int i = 0; i < n; ++i) {
			f[1][i] = 1;
		}
		for (int i = 2; i <= m; ++i) {
			t.clear();
			for (int j = 0; j < n; ++j) {
				f[i][j] = (t.sum(v[j] - 1) + f[i][j]) % mod;
				t.add(v[j], f[i - 1][j]);
			}
		}
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			ans = (ans + f[m][i]) % mod;
		}
		printf("Case #%d: %d\n", ++kase, ans);
	}
	return 0;
}
