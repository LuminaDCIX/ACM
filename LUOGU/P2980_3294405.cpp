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

const int N = 100000 + 5;

int n, c;
int nxt[N][19];

struct segment {
	int l, r;
	bool operator < (const segment &rhs) const {
		return l == rhs.l ? r < rhs.r : l < rhs.l;
	}
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

inline bool touch(int a, int b)
{
	if (s[a].r < c) {
		if (b <= a) {
			return false;
		}
		return s[b].l <= s[a].r;
	} else {
		if (b > a) {
			return true;
		}
		return (s[a].r) % c >= s[b].l;
	}
}

inline bool between(int a, int b, int c)
{
	if (a <= c) {
		return a <= b && b <= c;
	} else {
		return a <= b || b <= c;
	}
}

int main() {
	c = read();
  n = read();
	for (int i = 0; i < n; ++i) {
		s[i].l = read();
		s[i].r = read() + s[i].l;
	}
	sort(s, s + n);
	int t = n;
	n = 0;
	for (int i = 0; i < t; ++i) {
		if (i == 0 || s[i].r > s[i - 1].r) {
			s[n++] = s[i];
		}
	}
	t = 0;
	while (s[t].r <= s[n - 1].r % c) {
		++t;
	}
	n -= t;
	for (int i = 0; i < n; ++i) {
		s[i] = s[i + t];
	}
	t = 0;
	for (int i = 0; i < n; ++i) {
		while (touch(i, (t + 1) % n)) {
			t = (t + 1) % n;
		}
		nxt[i][0] = t;
	}
	for (int k = 0; k < 17; ++k) {
		for (int i = 0; i < n; ++i) {
			int a = nxt[i][k];
			if (a == -1) {
				nxt[i][k + 1] = -1;
				continue;
			} else {
				int b = nxt[a][k];
				if (b == -1 || between(i, b, a)) {
					nxt[i][k + 1] = -1;
				} else {
					nxt[i][k + 1] = b;
				}
			}
		}
	}
	int ans = n;
	for (int i = 0; i < n; ++i) {
		int now = nxt[i][0];
		int x = 2;
		for (int k = 16; k >= 0; --k) {
			if (nxt[now][k] == -1 || between(now, i, nxt[now][k])) {
				continue;
			}
			x += 1 << k;
			now = nxt[now][k];
		}
		ans = min(ans, x);
	}
	printf("%d\n", ans);
	return 0;
}
