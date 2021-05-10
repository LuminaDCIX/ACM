#include <bits/stdc++.h>

using namespace std;

const int maxn = 1000;
double a[4][maxn + 5];
double b[maxn + 5];
double f[maxn + 5], ans[maxn + 5];
int x, y, n, m;
int main() {
	scanf("%d%d%d%d", &n, &m, &x, &y);
	if (m == 1) {
		for (int i = n - 1; i >= x; --i) {
			ans[1] += 2;
		}
	}
	else for (int j = n - 1; j >= x; --j) {
		memset(a, 0 ,sizeof(a));
		a[1][1] = a[1][m] = 2.0 / 3.0;
		a[2][1] = a[3][m] = -1.0 / 3.0;
		b[1] = 1 + ans[1] / 3.0;
		b[m] = 1 + ans[m] / 3.0;
		for (int i = 2; i <= m - 1; ++i) {
			b[i] = 1 + ans[i] * 0.25;
			a[1][i] = 0.75;
			a[2][i] = a[3][i] = -0.25;
		}
		for (int i = 2; i <= m - 1; ++i) {
			b[i] = a[1][i - 1] * b[i] - a[3][i] * b[i - 1];
			a[1][i] = -a[3][i] * a[2][i - 1] + a[1][i - 1] * a[1][i];
			a[2][i] = a[1][i - 1] * a[2][i];
		}
		double bar1 = b[m] * a[1][m - 1] / a[3][m] - b[m - 1];
		double bar2 = a[1][m] * a[1][m - 1] / a[3][m] - a[2][m - 1];
		f[m] = bar1 / bar2;
		for (int i = m - 1; i >= 1; --i) {
			f[i] = (b[i] - a[2][i] * f[i + 1]) / a[1][i];
		}
		for (int i = 1; i <= m; ++i) {
			ans[i] = f[i];
		}
	}
	printf ("%.4lf\n", ans[y]);
	return 0;
}
