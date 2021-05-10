#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
typedef long long ll;
ll s[N];
ll det[N];
ll detmx[N];
int n, m;
inline void add(ll t[], int x, ll v) {
	for (; x < N; x += x & -x) {
		t[x] += v;
	}
}
inline ll sum(ll t[], int x) {
	ll ret = 0;
	for (; x; x -= x & -x) {
		ret += t[x];
	}
	return ret;
}
inline ll calc(int x) {
	return s[x] + (x + 1) * sum(det, x) - sum(detmx, x);
}
int main() {
	scanf("%d%d", &n, &m);
	ll v;
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &v);
		s[i] = s[i - 1] + v;
	}
	for (int i = 1, o, l, r; i <= m; ++i) {
		scanf("%d", &o);
		if (o == 2) {
			scanf("%d%d", &l, &r);
			printf("%lld\n", calc(r) - calc(l - 1));
		}
		else {
			scanf("%d%d%lld", &l, &r, &v);
			add(det, l, v);
			add(det, r + 1, -v);
			add(detmx, l, v * l);
			add(detmx, r + 1, -v * (r + 1));
		}
	}
	return 0;
}
