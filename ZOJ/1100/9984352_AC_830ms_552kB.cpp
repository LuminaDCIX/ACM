#include <bits/stdc++.h>

using namespace std;

const int maxn=11;
int v[(1 << maxn) + 5];
long long f[maxn + 5][(1 << maxn) + 5];
int n, m;
inline void init() {
	memset(v, 0, sizeof(v));
	for (int i = 0; i < (1 << m); ++i) {
		int cnt = 0;
		for (int j = 0; j < m; ++j) {
			if (((1 << j) & i)) {
				if (cnt & 1) {
					break;
				}
				else {
					cnt = 0;
				}
			}
			else {
				cnt++;
			}
		}
		if (cnt & 1) {
			continue;
		}
		v[i] = 1;
	}
}

int main() {
	while (scanf("%d%d", &n, &m) && n + m) {
		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		init();
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < (1 << m); ++j) {
				for (int k = 0; k < (1 << m); ++k) {
					if (v[j | k] && (j & k) == 0) {
						f[i][j] += f[i - 1][k];
					}
				}
			}
		}
		printf("%lld\n", f[n][0]);
	}
	return 0;
}
