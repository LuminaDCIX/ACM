#include <bits/stdc++.h>

using namespace std;
const int maxn = 10000;
int n, m;
int cut = 10000000;
int cnt[maxn * 2 + 5];
struct Bigint {
	long long s[maxn + 5];
	int n;
	inline void init(int x) {
		memset(s, 0, sizeof(s));
		s[0] = x;
		n = 1;
	}
	inline void print() {
		printf("%lld", s[n - 1]);
		for (int i = n - 2; i >= 0; --i) {
			printf("%07lld", s[i]);
		}
		puts("");
	}
};
Bigint ret;
Bigint operator * (Bigint &a, int b) {
	Bigint ret;
	ret.init(0);
	for (int i = 0; i < a.n; ++i) {
	 	ret.s[i] += a.s[i] * b;
		ret.s[i + 1] += ret.s[i] / cut;
		ret.s[i] %= cut;
	}
	ret.n = a.n + 2;
	while (ret.s[ret.n - 1] == 0) {
		--ret.n;
	}
	return ret;
}
Bigint operator + (Bigint &a, Bigint &b) {
	Bigint ret;
	ret.init(0);
	long long lst = 0;
	int lim = max(a.n, b.n);
	for (int i = 0; i < lim; ++i) {
		ret.s[i] += a.s[i] + b.s[i];
		ret.s[i + 1] += ret.s[i] / cut;
		ret.s[i] %= cut;
	}
	ret.n = lim + 2;
	while (ret.s[ret.n - 1] == 0) {
		--ret.n;
	}
	return ret;
}
int main() {
	scanf("%d%d", &n, &m);

	Bigint bar1, bar2;
	bar1.init(0);
	bar2.init(0);
	if (n + 3 - m >= 0 && n + 1 - 2 >= 0) {
		bar1.s[0] = 1;
		for (int i = 1; i <= n; ++i) {
			bar1 = bar1 * i;
		}
		bar1 = bar1 * (n + 1);
		bar1 = bar1 * (n);
		for (int i = 0; i < m; ++i) {
			bar1 = bar1 * (n + 3 - i);
		}
	}
	if (n + 2 - (m - 1) >= 0) {
		bar2.n = bar2.s[0] = 1;
		for (int i = 1; i <= n; ++i) {
			bar2 = bar2 * i;
		}
		bar2 = bar2 * (2 * m);
		bar2 = bar2 * (n + 1);
		for (int i = 0; i < m - 1; ++i) {
			bar2 = bar2 * (n + 2 - i);
		}
	}
	bar1 = bar1 + bar2;
	bar1.print();
	return 0;
}
