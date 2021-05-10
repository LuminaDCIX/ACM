#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;
const int N = 35;
int mat[N][N];
int T;
int dx[] = {0, 0, 0, -1, 1};
int dy[] = {0, 1, -1, 0, 0};
int ans[7][7];
int kase;
inline bool check(int x, int y) {
	return x >= 0 && x < 5 && y >= 0 && y < 6;
}
inline bool update(int x, int y) {
	mat[x * 6 + y][30] = 1;
}
inline void gauss()
{
	int k = 0;
	int col = 0;
	for (; k < 30 && col < 30; ++k, ++col) {
		int pivot = -1;
		int mx = 0;
		for (int i = k; i < 30; ++i) {
			if (mat[i][col]) {
				pivot = i;
				break;
			}
		}
		if (pivot == -1) {
			--k;
			continue;
		}
		for (int i = col; i <= 30; ++i) {
			swap(mat[pivot][i], mat[k][i]);
		}
		for (int i = 0; i < 30; ++i) {
			if (i == k || mat[i][col] == 0) {
				continue;
			}
			for (int j = col; j <= 30; ++j) {
				mat[i][j] = mat[i][j] - mat[k][j];
				mat[i][j] = (mat[i][j] % 2 + 2) % 2;
			}
		}
	}
  for (int i = 0; i < 30; ++i) {
		if (mat[i][30] == 1) {
			ans[i / 6][i % 6] = 1;
		}
	}
}
int main() {
	scanf("%d", &T);
	while (T--) {
		memset(ans, 0, sizeof(ans));
		memset(mat, 0, sizeof(mat));
		for (int i = 0; i < 5; ++i) {
			for (int j = 0, v; j < 6; ++j) {
				scanf("%d", &v);
				if (v != 0) {
				  update(i, j);
				}
			}
		}
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 6; ++j) {
				for (int k = 0; k < 5; ++k) {
					int x = i + dx[k];
					int y = j + dy[k];
					if (check(x, y)) {
						mat[i * 6 + j][x * 6 + y] = 1;
					}
				}
			}
		}
		gauss();
		printf("PUZZLE #%d\n", ++kase);
		for (int i = 0; i < 5; ++i, puts("")) {
			for (int j = 0; j < 6; ++j) {
				printf("%d ", ans[i][j]);
			}
		}
	}
}
