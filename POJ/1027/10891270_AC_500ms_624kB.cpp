#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 17;

int n;
int m;

int T;

int v[N][N];

inline void print()
{
	for (int i = 0; i < n; ++i, puts("")) {
	  for (int j = 0; j < m; ++j) {
	  	printf("%d", v[i][j]);
	  }
	}
	puts("");
	return;
}

bool vis[N][N];

struct block 
{
	int siz;
	int x;
	int y;

	block(int _x, int _y, int _siz) {
	 	siz = _siz;
	 	x = _x;
	 	y = _y;
	}	

	bool operator < (const block &rhs) const {
		if (siz == rhs.siz) {
			return y == rhs.y ? x > rhs.x : y < rhs.y;
		} else {
			return siz > rhs.siz;
		}
	}
};

vector <block> b;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
char C[] = {'R', 'R', 'G', 'B'};
int siz;
int sx;
int sy;

void dfs(int x, int y, int col) {
	if (vis[x][y] || x < 0 || x >= n || y < 0 || y >= m || v[x][y] != col) {
		return;
	}
	vis[x][y] = 1;
	++siz;
	if (y < sy) {
		sx = x;
		sy = y;
	} else if (y == sy) {
		sx = max(sx, x);
	}
	for (int i = 0, xx, yy; i < 4; ++i) {
		xx = x + dx[i];
		yy = y + dy[i];
		dfs(xx, yy, col);
	}
}


void clear(int x, int y, int col) {
	if (x < 0 || x >= n || y < 0 || y >= m || v[x][y] != col) {
		return;
	}
	v[x][y] = 0;
	for (int i = 0, xx, yy; i < 4; ++i) {
		xx = x + dx[i];
		yy = y + dy[i];
		clear(xx, yy, col);
	}
}


inline bool getblock()
{
	memset(vis, 0, sizeof(vis));
	b.clear();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (!vis[i][j] && v[i][j]) {
				siz = 0;
				sx = i;
				sy = j;
				dfs(i, j, v[i][j]);
				if (siz > 1) {
				  b.push_back(block(sx, sy, siz));
				}
			}
		}
	}
	return b.size();
}

inline void down()
{
	for (int i = 0; i < m; ++i) {
		for (int j = n - 2; j >= 0; --j) {
			if (v[j][i] && v[j + 1][i] == 0) {
				int k = j + 1;
				while (k + 1 < n && v[k + 1][i] == 0) {
					++k;
				}
				v[k][i] = v[j][i];
				v[j][i] = 0;
			}
		}
	}
}

inline int findemp()
{
	for (int i = 0; i <= m - 1; ++i) {
		bool flg = 1;
		for (int j = 0; j < n; ++j) {
			if (v[j][i]) {
				flg = 0;
			}
		}
		if (flg) {
			return i;
		}
	}
	return -1;
}

inline void move(int x) 
{
	for (int i = 0; i < n; ++i) {
		for (int j = x; j < m - 1; ++j) {
			v[i][j] = v[i][j + 1];
			v[i][j + 1] = 0;	
		}
	}
}

inline bool check(int x)
{
	for (int i = x; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (v[j][i]) {
				return false;
			}
		}
	}
	return true;
}

inline void left()
{
  int k;
  int lst = -1;
  while (true) {
 		k = findemp();
  	if (k == -1 || check(k)) {
  		return;
  	}
  	move(k);
  	lst = k;
  }
}

int Kase = 0;
inline void solve()
{
	if (Kase) {
		puts("");
	}
	printf("Game %d:\n", ++Kase);
	puts("");
  int ans = 0;
  int cnt = 0;
	while (getblock()) {
		sort(b.begin(), b.end());
		block x = b[0];
		int val = (x.siz - 2) * (x.siz - 2);
		printf("Move %d at (%d,%d): removed %d balls of color %c, got %d points.\n", ++cnt, n - x.x, x.y + 1, x.siz, C[v[x.x][x.y]], val);
		ans += val;
		clear(x.x, x.y, v[x.x][x.y]);
		down();
		//print();
		left();
		//print();	
	}
	int rem = 0;
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < m; ++j) {
			if (v[i][j]) {
				++rem;
			}
		}
	}
	if (!rem) {
		ans += 1000;
	}
	printf("Final score: %d, with %d balls remaining.\n", ans, rem);
}

int main()
{
  scanf("%d", &T);
  while (T--) {
        n=10;
        m=15;
       for (int i = 0; i < n; ++i) {
  		scanf("\n");
  		char k;
  		for (int j = 0; j < m; ++j) {
  			k = getchar();
  			if (k == 'R') {
  				v[i][j] = 1;
  			} else if (k == 'G') {
  				v[i][j] = 2;
  			} else {
  				v[i][j] = 3;
  			}
  		}
  	}
  	solve();
  }
	return 0;
}