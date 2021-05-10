#include <bits/stdc++.h>

using namespace std;

const int maxn = 1000;
int n, m;

inline long long C(int x, int y) {
	if (y > x) {
		return 0;
	}
	long long ret = 1;
	for (int i = 1; i <= y; ++i) {
		ret = ret * (x - i + 1) / i;
	}
	return ret;
}
int gcd(int a, int b) {
	return !b ? a : gcd(b, a % b);
}
int main() {
	scanf("%d%d", &n, &m);
	n++, m++;
	long long ans = C(n * m, 3);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			int d = gcd(i, j);
			if (d >= 2) {
				ans -= (d - 1) * (n - i) * (m - j) * 2;
			}
		}
	}
	ans -= C(n, 3) * m;
	ans -= C(m, 3) * n;
	printf("%lld\n", ans);
}
