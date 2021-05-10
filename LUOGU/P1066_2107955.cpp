#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int k, W;
void input() {
	scanf("%d%d", &k, &W);
	return;
}
struct bigint
{
	short len, s[55];
	void init() 
	{
		len = 1;
		for (int i = 0; i <= 54;++i) {
			s[i] = 0;
		} 
		return;
	}
} C[705][705];
int n2[11];
bigint add(bigint a, bigint b)
{
	bigint c;
	c.init();
	c.len = max(a.len, b.len) + 1;
	int x = 0;
	for (int i = 1; i <= c.len; ++i) {
		c.s[i] = a.s[i] + b.s[i] + x;
		x = c.s[i] / 10000;
		c.s[i] %= 10000;
	}
	//if (x != 0) c.s[++c.len] = x;
	while (!c.s[c.len] && c.len > 1) 
		--c.len;
	return c;
} 
void solve() 
{
	n2[0] = 1;
	for (int i = 1; i <= 9; ++i) {
		n2[i] = n2[i - 1] * 2;
	}
	int t = ceil(1.00 * W / k);
	int amx = n2[W % k];
	bigint ans;
	ans.init();
	C[1][0].len = 1; C[1][0].s[1] = 1;
	C[1][1].len = 1; C[1][1].s[1] = 1;
	for (int i = 2; i <= 699; ++i) {
		C[i][0].s[1] = 1;
		C[i][0].len = 1;
		for (int j = 1; j <= i; ++j) {
			C[i][j] = add(C[i - 1][j], C[i - 1][j - 1]);
		}
	}
	for (int i = 2; i <= (int)floor(1.00 * W / k); ++i) {
		ans = add(ans, C[n2[k] - 1][i]);
	}
	//puts("");
	for (int i = 1; i <= amx - 1; ++i) {
		ans = add(ans, C[n2[k] - i - 1][(int)floor(1.00 * W / k)]);
		//print(n2[k] - i, t - 1);
	}	
	printf("%d", ans.s[ans.len]);
	for (int i = ans.len - 1; i > 0; --i) {
		printf("%04d", ans.s[i]);
	}
	return;
}
int main() 
{
	input();
	solve();
	return 0;
} 

