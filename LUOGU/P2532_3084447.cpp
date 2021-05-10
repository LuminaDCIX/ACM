#include <bits/stdc++.h>

using namespace std;

const int N = 500 + 5;
const int cut = (int)1e8;
typedef long long ll;
int n;
struct bigint 
{
	ll s[45];
	int n;
	inline void init(int x) {
		n = 1;
		memset(s, 0, sizeof(s));
		s[0] = x;
	}
} f[N];
bigint operator + (bigint a, bigint b) 
{
	bigint c;
	c.init(0);
	c.n = max(a.n, b.n) + 1;
	for (int i = 0; i < c.n; ++i) {
		c.s[i] += a.s[i] + b.s[i];
		c.s[i + 1] += c.s[i] / cut;
		c.s[i] %= cut;
	}
	while (c.s[c.n - 1] == 0) {
		--c.n;
	}
	return c;
}
bigint operator * (bigint a, bigint b) 
{
	bigint c;
	c.init(0);
	for (int i = 0; i < a.n; ++i) {
		for (int j = 0; j < b.n; ++j) {
			c.s[i + j] += a.s[i] * b.s[j];
			c.s[i + j + 1] += c.s[i + j] / cut;
			c.s[i + j] %= cut;
		}
	}
	c.n = a.n + b.n + 2;
	while (c.s[c.n - 1] == 0) {
		--c.n;
	}
	return c;
}
int main()
{
	scanf("%d", &n);
	f[0].init(1);
	f[1].init(1);
	for (int i = 2; i <= n; ++i) {
		for (int j = 0; j < i; ++j) {
			f[i] = f[i] + f[j] * f[i - j - 1]; 
		}
	}
	printf("%lld", f[n].s[f[n].n - 1]);
	for (int i = f[n].n - 2; i >= 0; --i) {
		printf("%08lld", f[n].s[i]);
	}
	puts("");
	return 0;
}
