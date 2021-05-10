#include <cstring>
#include <algorithm>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;
const int N = 500 + 5;
char box[N][N];
int n, m;
int tx, ty;
bool vis[N][N][3];
struct node {
	int x, y;
	int s, len;
	node(int _x = -1, int _y = -1, int _s = -1, int _len = 0) {
		x = _x;
		y = _y;
		s = _s;
		len = _len;
	}
};
int dx[3][4];
int dy[3][4];
int t[3][4];
//0  x

//1  xx

//2  x
//   x

//0 l 1 r 2 u 3 d
node que[N * N * 3];
int head, tail;
inline void init() 
{
	dx[0][0] = 0;
	dy[0][0] = -2;
	t[0][0] = 1;
	dx[0][1] = 0;
	dy[0][1] = 1;
	t[0][1] = 1;
	dx[0][2] = -2;
	dy[0][2] = 0;
	t[0][2] = 2;
	dx[0][3] = 1;
	dy[0][3] = 0;
	t[0][3] = 2;

	dx[1][0] = 0;
	dy[1][0] = -1;
	t[1][0] = 0;
	dx[1][1] = 0;
	dy[1][1] = 2;
	t[1][1] = 0;
	dx[1][2] = -1;
	dy[1][2] = 0;
	t[1][2] = 1;
	dx[1][3] = 1;
	dy[1][3] = 0;
	t[1][3] = 1;

	dx[2][0] = 0;
	dy[2][0] = -1;
	t[2][0] = 2;
	dx[2][1] = 0;
	dy[2][1] = 1;
	t[2][1] = 2;
	dx[2][2] = -1;
	dy[2][2] = 0;
	t[2][2] = 0;
	dx[2][3] = 2;
	t[2][3] = 0;
	dy[2][3] = 0;
}
bool check(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m && box[x][y] != '#';
}
inline int solve() 
{
	while (head != tail) {
		node x = que[head++];
		for (int i = 0; i < 4; ++i) {
			int tx = dx[x.s][i] + x.x;
			int ty = dy[x.s][i] + x.y;
			int tt = t[x.s][i];
			bool ok = true;
			if (tt == 0) {
				if (!check(tx, ty) || box[tx][ty] == 'E') {
					ok = false;
				}
			}
			if (tt == 1) {
				if (!check(tx, ty) || !check(tx, ty + 1)) {
					ok = false;
				}
			}
			if (tt == 2) {
				if (!check(tx, ty) || !check(tx + 1, ty)) {
					ok = false;
				}
			}
			if (!ok) {
				continue;
			}
			if (box[tx][ty] == 'O' && tt == 0) {
				return x.len + 1;
			}
			if (vis[tx][ty][tt]) {
				continue;
			}
			vis[tx][ty][tt] = 1;
			if (ok) {
				que[tail++] = node(tx, ty, tt, x.len + 1);
			}
		}
	}
	return -1;
}
int main()
{
	init();
	while (scanf("%d%d", &n, &m) && n + m) {
		memset(vis, 0, sizeof(vis));
		head = tail = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%s", box[i]);
		}
		int x, y;
		int fx, fy;
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (box[i][j] == 'X') {
					++cnt;
					if (cnt == 1) {
						x = i;
						y = j;
					}
					if (cnt == 2) {
						fx = i;
						fy = j;
					}
				}
			}
		}
		if (cnt == 1) {
			que[tail++] = node(x, y, 0);
			vis[x][y][0] = 1;
		}
		else {
			if (fx == x && fy == y + 1) {
				que[tail++] = node(x, y, 1);
				vis[x][y][1] = 1;
			}
			if (fx == x + 1 && fy == y) {
				que[tail++] = node(x, y, 2);
				vis[x][y][2] = 1;
			}
		}
		int k = solve();
		if (k == -1) {
			puts("Impossible");
		}
		else {
			printf("%d\n", k);
		}
	}
}
