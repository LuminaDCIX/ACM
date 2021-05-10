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

const int N = 35 + 5;

int n, m;
int mat[N][N];
vector <int> freex;
int ans = 0;
int t[N][N];
int v[N];

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

inline void print() {
	for (int i = 0; i < n; ++i, puts("")) {
		for (int j = 0; j <= n; ++j) {
			printf("%d ", t[i][j]);
		}
	}
	puts("");
}
inline void gauss() 
{
	int k = 0;
	//print();
	for (int i = 0; i < n; ++i) {
		int rec = -1;
		for (int j = k; j < n; ++j) {
			if (mat[j][i]) {
				rec = j;
				break;
			}
		}
		if (rec == -1) {
			freex.push_back(i);
			continue;
		}
		for (int j = i; j <= n; ++j) {
			swap(mat[k][j], mat[rec][j]);
		}
		for (int j = 0; j < n; ++j) {
			if (j == k || mat[j][i] == 0) {
				continue;
			}
			for (int p = i; p <= n; ++p) {
				mat[j][p] ^= mat[k][p];
			}
		}
		++k;
	}
	//print();
}

void dfs(int now, int tot) {
	if (tot >= ans) {
		return;
	}
	if (now == freex.size()) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j <= n; ++j) {
				t[i][j] = mat[i][j];
			}
		}
		for (int i = 0; i < freex.size(); ++i) {
			int x = freex[i];
			if (!v[i]) {
				continue;
			}
			for (int j = 0; j < n; ++j) {
				if (t[j][x]) {
					t[j][n] ^= 1;
				}
			}
		}
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			if (t[i][n]) {
				++cnt;
			}
		}
		ans = min(ans, cnt + tot);
		return;
	}
	v[now] = 0;
	dfs(now + 1, tot);
	v[now] = 1;
	dfs(now + 1, tot + 1);
}

int main() {
	n = read();
	for (int i = 0; i < n; ++i) {
		mat[i][i] = 1;
	}
	for (int i = 0; i < n; ++i) {
		mat[i][n] = 1;
	}
	m = read();
	for (int i = 0, u, v; i < m; ++i) {
		u = read() - 1;
		v = read() - 1;
		mat[u][v] = mat[v][u] = 1;
	}
	gauss();
  for (int i = 0; i < n; ++i) {
		if (mat[i][n]) {
			++ans;
		}
	}
	dfs(0, 0);
	printf("%d\n", ans);
	return 0;
}
