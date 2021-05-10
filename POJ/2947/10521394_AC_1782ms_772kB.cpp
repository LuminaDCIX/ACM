#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;
typedef long long ll;
const int N = 300 + 5;
int mat[N][N];
char dat[7][4] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
int n, m;
ll gcd(ll a, ll b) {
	return !b ? a : gcd(b, a % b);
}
ll lcm(ll a, ll b) {
	return a / gcd(a, b) * b;
}
inline int getdate(char s[]) 
{
	for (int i = 0; i < 7; ++i) {
		if (strcmp(s, dat[i]) == 0) {
			return i;
		}
	}
}
 
inline int gauss()
{//mat (m - 1) * n
	int col = 0;
	int k = 0;
	for (k = 0; k < m && col < n; ++k, ++col) {
		int mx = 0;
		int row = -1;
		for (int r = k; r < m; ++r) {
			if (mx < abs(mat[r][col])) {
				mx = abs(mat[r][col]);
				row = r;
			}
		}
		if (row == -1) {
			--k;
			continue;
		}
		for (int c = col; c <= n; ++c) {
			swap(mat[k][c], mat[row][c]);
		}
		for (int r = k + 1; r < m; ++r) {
			if (mat[r][col]) {
				int Lcm = lcm(abs(mat[k][col]), abs(mat[r][col]));
				int bar1 = Lcm / mat[r][col];
				int bar2 = Lcm / mat[k][col];
				if (mat[r][col] * mat[k][col] < 0) {
					bar2 *= -1;
				}
				for (int c = col; c <= n; ++c) {
					mat[r][c] = mat[r][c] * bar1 - mat[k][c] * bar2;
					mat[r][c] = (mat[r][c] % 7 + 7) % 7;
				}
			}
		}
	}
	for (int i = k; i < m; ++i) {
		if (mat[i][n] != 0) {
			return -1;
		}
	}
	if (k < n) {
		return 1;
	} 
	return 0;
}
void extgcd(ll a, ll b, ll &x, ll &y) {
	if (!b) {
		x = 1;
		y = 0;
		return;
	}
	extgcd(b, a % b, y, x);
	y -= (a / b) * x;
}
inline ll inv(ll a) {
	ll x, y;
	extgcd(a, 7, x, y);
	return (x % 7 + 7) % 7;
}
int main()
{
	while (scanf("%d%d", &n, &m) && n + m) {
		memset(mat, 0, sizeof(mat));
		for (int p = 0; p < m; ++p) {
			int k;
			char bar1[4], bar2[4];
			scanf("%d", &k);
			scanf("%s%s", bar1, bar2);
			int len = ((getdate(bar2) - getdate(bar1) + 1) % 7 + 7) % 7;
			for (int i = 0, v; i < k; ++i) {
				scanf("%d", &v);
				++mat[p][--v];
			}
			mat[p][n] = len;
		}
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j <= n; ++j) {
				mat[i][j] %= 7;
			}
		}
		int flg = gauss();
		if (flg == -1) {
			puts("Inconsistent data.");
			continue;
		}
		if (flg == 1) {
			puts("Multiple solutions.");
			continue;
		}
		for (int i = n - 1; i >= 0; --i) {
			int bar = mat[i][n];
			for (int j = n - 1; j > i; --j) {
				bar -= mat[j][n] * mat[i][j] % 7;
			}
			bar = (bar % 7 + 7) % 7;
			mat[i][n] = (inv(mat[i][i]) * bar % 7 + 7) % 7;
			if (mat[i][n] < 3) {
				mat[i][n] += 7;
			}
		}
		for (int i = 0; i < n - 1; ++i) {
			printf("%d ", mat[i][n]);
		}
		printf("%d\n", mat[n - 1][n]);
	}
	return 0;
}
