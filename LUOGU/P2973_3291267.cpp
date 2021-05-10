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

const int N = 300 + 5;
const double eps = 1e-13;

int n, m, P, Q;
int G[N][N];
int dv[N];
double mat[N][N];
double p;

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

inline void build()
{
	mat[0][n] = 1;
	for (int i = 0; i < n; ++i) {
		mat[i][i] = 1;
		for (int j = 0; j < n; ++j) {
			if (i == j) {
				continue;
			}
			if (dv[j] == 0) {
				continue;
			}
			mat[i][j] = -1.0 * G[j][i] / dv[j] * (1 - p);
		}
	}
	return;
}

inline  void gauss()
{
	for (int i = 0; i < n; ++i) {
		int pivot = i;
		for (int j = i; j < n; ++j) {
			if (abs(mat[j][i]) > abs(mat[pivot][i])) {
				pivot = j;
			}
		}
		if (abs(mat[pivot][i]) < eps) {
			continue;
		}
		for (int j = i; j <= n; ++j) {
			swap(mat[i][j], mat[pivot][j]);
		}
		if (abs(mat[i][i]) < eps) {
			continue;
		}
		for (int j = n; j >= i; --j) {
			mat[i][j] /= mat[i][i];
		}
		for (int j = 0; j < n; ++j) {
			if (j == i || abs(mat[j][i]) < eps) {
				continue;
			}
			for (int k = n; k >= i; --k) {
				mat[j][k] -= mat[j][i] * mat[i][k];
			}
		}
	}
}

int main() {
	n = read();
	m = read();
	P = read();
	Q = read();
	p = 1.0 * P / Q;
	for (int i = 0, u, v; i < m; ++i) {
		u = read() - 1;
		v = read() - 1;
		++dv[u];
		++dv[v];
		++G[v][u];
		++G[u][v];
	}
	build();
	gauss();
	double sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += mat[i][n];
	}
	for (int i = 0; i < n; ++i) {
		printf("%.9f\n", mat[i][n] / sum);
	}
	return 0;
}
