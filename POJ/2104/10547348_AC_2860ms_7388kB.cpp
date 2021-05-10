#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>

using namespace std;

const int N = 100000 + 5;
const int M = 5000 + 5;
int n, m;
int tot;
int ans[M];
struct query {
	int t, x, y, k, cur;
	query(int a = 0, int b = 0, int c = 0, int d = 0) {
		t = a;
		x = b;
		y = c;
		k = d;
		cur = 0;
	}
};
query q[M + N + 5];
struct bit {
	int t[N];
	inline void add(int x, int v) {
		for (; x < N; x += x & -x) {
			t[x] += v;
		}
	}
	inline int sum(int x) {
		int ret = 0;
		for (; x; x -= x & -x) {
			ret += t[x];
		}
		return ret;
	}

} s;
int bar[N + M + 5];
query q1[N + M + 5];
query q2[M + N + 5];
void divide(int h, int t, int l, int r)
{
	if (h > t) {
		return;
	}
	if (l == r) {
		for (int i = h; i <= t; ++i) {
			if (q[i].t != 0) {
				ans[q[i].t] = l;
			}
		}
		return;
	}
	int mid = (l + r) >> 1;
	for (int i = h; i <= t; ++i) {
		if (q[i].t == 0 && q[i].y <= mid) {
			s.add(q[i].x, 1);
		}
		if (q[i].t != 0) {
			bar[i] = s.sum(q[i].y) - s.sum(q[i].x - 1);
		}
	}
	for (int i = h; i <= t; ++i) {
		if (q[i].t == 0 && q[i].y <= mid) {
			s.add(q[i].x, -1);
		}
	}
	int l1 = 0;
	int l2 = 0;
	for (int i = h; i <= t; ++i) {
		if (q[i].t != 0) {
			if (q[i].cur + bar[i] >= q[i].k) {
				q1[l1++] = q[i];
			} 
			else {
				q[i].cur += bar[i];
				q2[l2++] = q[i];
			}
		}
		else {
			if (q[i].y <= mid) {
				q1[l1++] = q[i];
			}
			else {
				q2[l2++] = q[i];
			}
		}
	}
	for (int i = 0; i < l1; ++i) {
		q[h + i] = q1[i];
	}
	for (int i = 0; i < l2; ++i) {
		q[h + l1 + i] = q2[i];
	}
	divide(h, h + l1 - 1, l, mid);
	divide(h + l1, t, mid + 1, r);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0, v; i < n; ++i) {
		scanf("%d", &v);
		q[tot++] = query(0, i + 1, v, 0);
	}
	for (int i = 0, x, y, k; i < m; ++i) {
		scanf("%d%d%d", &x, &y, &k);
		q[tot++] = query(i + 1, x, y, k);
	}
	divide(0, tot - 1, -1e9, 1e9);
	for (int i = 1; i <= m; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}
