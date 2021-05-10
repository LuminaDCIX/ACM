#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>

using namespace std;

const int maxn = 25000;
int n, T;
struct work {
	int l, r;
};
work w[maxn + 5];
bool cmp(work a, work b) {
	return a.l == b.l ? a.r < b.r : a.l < b.l;
}

int main() {
	scanf("%d%d", &n, &T);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &w[i].l, &w[i].r);
		if (w[i].l > w[i].r) {
			swap(w[i].l, w[i].r);
		}
	}
	sort(w + 1, w + 1 + n, cmp);
	int r = 0;
	int ans = 1;
	int t = 0;
  for (int i = 1; i <= n; ++i) {
		if (w[i].l > T || t >= T || r >= T) {
			break;
		}
		if (w[i].l - 1 <= r) {
			t = max(t, w[i].r);
		}
		else {
			if (w[i].l - 1 > t) {
				puts("-1");
				return 0;
			}
			r = t;
			t = w[i].r;
			ans++;
		}
	}
	if (r < T && t < T) {
		puts("-1");
		return 0;
	}
	printf("%d\n", ans);
	return 0;
}
