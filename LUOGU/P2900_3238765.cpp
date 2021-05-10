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

const int N = 50000 + 5;
typedef long long ll;

int n;
bool del[N];
ll f[N];
int que[N];
int head, tail;
int w[N], h[N];

struct rectangle {
	int h, w;
	bool operator < (const rectangle &rhs) const {
		return w == rhs.w ? h < rhs.h : w < rhs.w;
	}
} rec[N];

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

inline void init() {
  int hmx = 0;
	for (int i = n - 1; i >= 0; --i) {
		if (rec[i].h <= hmx) {
			del[i] = 1;
		}
		hmx = max(hmx, rec[i].h);
	}
	int len = 0;
	for (int i = 0; i < n; ++i) {
		if (!del[i]) {
			rec[len++] = rec[i];
		}
	}
	n = len;
	for (int i = 1; i <= n; ++i) {
		h[i] = rec[i - 1].h;
		w[i] = rec[i - 1].w;
	}
}

inline double grad(int j, int k) {
	return ((double)(f[k] - f[j]) / (h[j + 1] - h[k + 1]));
}

int main()
{
	n = read();
	for (int i = 0; i < n; ++i) {
		rec[i].h = read();
		rec[i].w = read();
	}
	sort(rec, rec + n);
	init();
	que[tail++] = 0;
  for (int i = 1; i <= n; ++i) {
		while (tail > head + 1 && grad(que[head], que[head + 1]) < w[i]) {
			head++;
		}
		f[i] = f[que[head]] + 1ll * h[que[head] + 1] * w[i];
		while (head + 1 < tail && grad(que[tail - 2], que[tail - 1]) > grad(que[tail - 1], i)) {
			tail--;
		}
		que[tail++] = i;
	}
	printf("%lld\n", f[n]);
	return 0;
}
