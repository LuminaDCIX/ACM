#include <bits/stdc++.h>
#define x(k) (k)
#define y(k) (f[i - 1][k] - d[k])
using namespace std;

const int maxp = 100;
const int maxn = 100000;
long long f[maxp + 5][maxn + 5];
int que[maxn + 5], l, r;
long long S0[maxn + 5];
long long h[maxn + 5];
long long d[maxn + 5];
int n, m, w;
struct cat {
	int S, t;
};
cat	c[maxn + 5];
bool cmp(cat a, cat b) {
	return a.t - a.S < b.t - b.S;
}
int main() {
	scanf("%d%d%d", &n, &m, &w);
	for (int i = 2, q; i <= n; ++i) {
		scanf("%d", &q);
		S0[i] = S0[i - 1] + q;
	}
	for (int i = 1, p, q; i <= m; ++i) {
		scanf("%d%d", &p, &c[i].t);
		c[i].S = S0[p];
	}
	sort(c + 1, c + 1 + m, cmp);
	for (int i = 1; i <= m; ++i) {
		h[i] = c[i].S - c[i].t;
		d[i] = d[i - 1] + h[i];
		h[i] = -h[i];
		f[0][i] = 1e12;
	}
	for (int i = 1; i <= w; ++i) {
		r = l = 0;
		que[r++] = 0;
		for (int j = 1; j <= m; ++j) {
			while (r - l > 1 && y(que[l + 1]) - y(que[l]) <=  h[j] * (x(que[l + 1]) - x(que[l]))) {
				l++;
			}
			f[i][j] = f[i - 1][que[l]] + (j - que[l]) * (h[j]) + d[j] - d[que[l]];
			while (r - l > 1 && (y(que[r - 1]) - y(que[r - 2])) * (x(j) - x(que[r - 1])) >= (y(j) - y(que[r - 1])) * (x(que[r - 1]) - x(que[r - 2]))) {
				r--;
			}
			que[r++] = j;
		}
	}
	printf("%lld\n", f[w][m]);
	return 0;
}