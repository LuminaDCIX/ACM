#include <bits/stdc++.h>
#define val(r, a, b) (sum[r][b] - sum[r][a - 1])
using namespace std;

int f[17][17][17][2][2][235];
int pre[17][17][17][2][2][235];
int sum[17][17];
int n, m, k;
int ans;
int a, al, ar;
int aol, aor;


inline void update(int row, int l, int r, int opl, int opr, int s) {
	if (row == n) {
		return;
	}
	for (int nl = (opl == 0 ? 1 : l); nl <= r; ++nl) {
		for (int nr = max(nl, l); nr <= (opr == 0 ? r : m); ++nr) {
			int t1, t2;
			if (nl == l) {
				t1 = opl;
			}
			else {
				t1 = (nl < l ? 0 : 1);
			}
			if (nr == r) {
				t2 = opr;
			}
			else {
				t2 = (nr < r ? 0 : 1);
			}
			if (f[row + 1][nl][nr][t1][t2][s + (nr - nl + 1)] < f[row][l][r][opl][opr][s] + val(row + 1, nl, nr)) {
				f[row + 1][nl][nr][t1][t2][s + (nr - nl + 1)] = f[row][l][r][opl][opr][s] + val(row + 1, nl, nr);
				pre[row + 1][nl][nr][t1][t2][s + (nr - nl + 1)] = (l << 12) | (r << 8) | (opl << 4) | opr;
			}
		}
	}
}
inline void solve() {
	for (int row = 1; row <= n; ++row) {
		for (int l = 1; l <= m; ++l) {
			for (int r = l; r <= m; ++r) {
				for (int opl = 0; opl < 2; ++opl) {
					for (int opr = 0; opr < 2; ++opr) {
						f[row][l][r][opl][opr][r - l + 1] = val(row, l, r);
						for (int s = r - l + 1; s <= k; ++s) {
							if (f[row][l][r][opl][opr][s] < 0) {
								continue;
							}
							update(row, l, r, opl, opr, s);
							if (s == k) {
								if (ans < f[row][l][r][opl][opr][s]) {
									ans = f[row][l][r][opl][opr][s];
									a = row;
									al = l;
									ar = r;
									aol = opl;
									aor = opr;
								}
							}
						}
					}
				}
			}
		}
	}
}
void print(int row, int l, int r, int opl, int opr, int k) {
	if (row == 0 || k <= 0) {
		return;
	}
	int p = pre[row][l][r][opl][opr][k];
	print(row - 1, (p >> 12) % 16, (p >> 8) % 16, (p >> 4) % 16, p % 16, k - (r - l + 1));
	for (int i = l; i <= r; ++i) {
		printf("%d %d\n", row, i);
	}
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			scanf("%d", &sum[i][j]);
			sum[i][j] += sum[i][j - 1];
		}
	}
	memset(f, -1, sizeof(f));
	solve();
	printf("Oil : %d\n", ans);
	print(a, al, ar, aol, aor, k);
	return 0;
}
