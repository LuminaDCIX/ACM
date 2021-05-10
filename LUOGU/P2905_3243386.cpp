#include <set>
#include <map>
#include <stack>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
 
using namespace std;

const int N = 1000 + 5;
const int K = 30 + 5;

int n, m, k;
int f[K][K << 1][K << 1];
int pre[K][K << 1][K << 1];
int x[N], y[N];
int cx[N], cy[N];
int cnt[K << 1][K << 1];
int dx[] = {0, 0, 1, -1};
int dy[] = {-1, 1, 0, 0};

inline int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		f = (ch == '-') ? -1 : 1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 3) + (x << 1) + ch - '0';
		ch = getchar();
  }
	return x * f;
}


int main()
{
	n = read();
	m = read();
	k = read();
	for (int i = 0; i < n; ++i) {
		x[i] = read();
		y[i] = read();
	}
	for (int i = 0; i < m; ++i) {
		cx[i] = read();
		cy[i] = read();
	}
	int base = k + 1;
  for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (abs(x[i] - cx[j]) <= k && abs(y[i] - cy[j]) <= k) {
				++cnt[base + cx[j] - x[i]][base + cy[j] - y[i]];
			}
		}
	}
	memset(f, 0xcfcf, sizeof(f));
	f[0][base][base] = cnt[base][base];
	for (int i = 1; i <= k; ++i) {
		for (int j = base - k; j <= base + k; ++j) {
			for (int l = base - k; l <= base + k; ++l) {
				int tmp = 0xcfcfcfcf;
				for (int d = 0; d < 4; ++d) {
					tmp = max(tmp, f[i - 1][j - dx[d]][l - dy[d]]);
				}
				f[i][j][l] = tmp + cnt[j][l];
			}
		}
	}
	int mx = 0;
	for (int i = base - k; i <= k + base; ++i) {
		for (int j = base - k; j <= k + base; ++j) {
			mx = max(mx, f[k][i][j]);
		}
	}
	printf("%d\n", mx);
	for (int i = 0; i <= k; ++i) {
		for (int j = base - k; j <= base + k; ++j) {
			for (int l = base - k; l <= base + k; ++l) {
				pre[i][j][l] = 'Z';
			}
		}
	}
	for (int i = base - k; i <= k + base; ++i) {
		for (int j = base - k; j <= k + base; ++j) {
			if (f[k][i][j] == mx) {
				pre[k][i][j] = 'Y';
			}
		}
	}
	for (int i = k - 1; i >= 0; --i) {
		for (int j = base - k; j <= base + k; ++j) {
			for (int l = base - k; l <= base + k; ++l) {
				if (f[i][j][l] + cnt[j - 1][l] == f[i + 1][j - 1][l] && pre[i + 1][j - 1][l] < 'Z') {
					pre[i][j][l] = 'W';
					//printf("%d %d\n", j, l);
				}
				if (f[i][j][l] + cnt[j][l - 1] == f[i + 1][j][l - 1] && pre[i + 1][j][l - 1] < 'Z') {
					pre[i][j][l] = 'S';
				}
				if (f[i][j][l] + cnt[j][l + 1] == f[i + 1][j][l + 1] && pre[i + 1][j][l + 1] < 'Z') {
					pre[i][j][l] = 'N';
				}
				if (f[i][j][l] + cnt[j + 1][l] == f[i + 1][j + 1][l] && pre[i + 1][j + 1][l] < 'Z') {
					pre[i][j][l] = 'E';
				}
			}
		}
	}
	int x = base;
	int y = base;
	for (int i = 0; i < k; ++i) {
		printf("%c", pre[i][x][y]);
		switch (pre[i][x][y]) {
		case 'E':
			++x;
			break;
		case 'N':
			++y;
			break;
		case 'S':
			--y;
			break;
		case 'W':
			--x;
			break;
		}
	}
	return 0;
}
