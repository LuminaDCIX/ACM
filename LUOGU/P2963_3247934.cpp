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

const int N = 10000 + 5;

int n, m;
int x, y;

struct node {
	int len;
	int tx, ty;
} s[N];

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

inline int len(int x, int y, int tx, int ty) {
  if (x == tx) {
		return abs(ty - y);
	}
	if ((y & 1) == 0) {
		return min(len(x, y + 1, tx, ty), len(x, y - 1, tx, ty)) + 1;
	}
	int down = y + 1;
	int up = (tx - x) * 2 - 1 + y;
	if (ty >= up) {
		return (tx - x) * 2 - 1 + (ty - up);
	}
	if (ty <= down) {
		return (tx - x) * 2 - 1 + (down - ty);
	}
	if (ty & 1) {
		return (tx - x) * 2;
	}
	else {
		return (tx - x) * 2 - 1;
	}
}

int main() {
	n = read();
	m = read();
	x = read();
	y = read();
	for (int i = 0, tx, ty; i < m; ++i) {
		tx = read();
		ty = read();
		s[i].tx = tx;
		s[i].ty = ty;
		if (tx < x) {
			swap(tx, x);
			swap(ty, y);
			s[i].len = len(x, y, tx, ty);
			swap(tx, x);
			swap(ty, y);
			//	printf("%d\n", s[i].len);
			continue;
		}
		s[i].len = len(x, y, tx, ty);
		//printf("%d\n", s[i].len);
	}
	int tx = s[0].tx, ty = s[0].ty;
	int mn = s[0].len;
	for (int i = 1; i < m; ++i) {
		if (s[i].len == mn) {
			if (s[i].tx == tx) {
				ty = min(ty, s[i].ty);
			}
			if (s[i].tx < tx) {
				tx = s[i].tx;
				ty = s[i].ty;
			}
		}
		if (s[i].len < mn) {
			tx = s[i].tx;
			ty = s[i].ty;
			mn = s[i].len;
		}
	}
	printf("%d %d\n%d\n", tx, ty, mn + 1);
	return 0;
}
