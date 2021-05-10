#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>

using namespace std;
const int maxn = 1e5;
int n;
long long m;
int v[maxn + 5];
int que[maxn + 5], h, t;
long long s[maxn + 5];
long long f[maxn + 5];
int mx[maxn + 5][21];
void init() {
	for (int i = 1; i <= n; ++i) {
		mx[i][0] = v[i];
	}
	int k = log(n) / log(2);
	for (int i = 1; i <= k; ++i) {
		for (int j = 1; j <= n; ++j) {
			mx[j][i] = mx[j][i - 1];
			if (j + (1 << (i - 1)) <= n) {
				mx[j][i] = max(mx[j][i], mx[j + (1 << (i - 1))][i - 1]);
			}
		}
	}
}
int query(int l, int r) {
	int k = log(r - l + 1) / log(2);
	return max(mx[l][k], mx[r - (1 << k) + 1][k]);
}
int main() {
	scanf("%d%lld", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &v[i]);
		if (v[i] > m) {
			puts("-1");
			return 0;
		}
	}
	init();
	for (int i = 1; i <= n; ++i) {
		s[i] = s[i - 1] + v[i];
	}
	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	int k = 0;
	long long sum = 0;
	for (int i = 1; i <= n; ++i) {
		sum += v[i];
		while (sum > m) sum -= v[++k];
		while (h < t && s[i] - s[que[h]] > m) {
			h++;
		}
		f[i] = min(f[i], f[k] + query(k + 1, i));
		for (int j = h; j < t; ++j) {
			f[i] = min(f[i], f[que[j]] + query(que[j] + 1, i));
		}
		while (h < t && v[que[t - 1]] <= v[i]) {
			t--;
		}
		que[t++] = i;
	}
	printf("%lld\n", f[n]);
	return 0;
}
