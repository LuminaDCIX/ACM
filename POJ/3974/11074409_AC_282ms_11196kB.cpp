#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

const int N = 1000000 + 5;
int p[N * 2 + 5];
char s[N * 2 + 5];
char str[N];
int n;
int len;

inline void init()
{
	for (int i = 0; i < len; ++i) {
		s[i * 2] = '#';
		s[i * 2 + 1] = str[i];
	} 
	s[2 * len] = '#';
	n = len * 2 + 1;
	int id = 0;
	int mx = 0;
	for (int i = 0; i < n; ++i) {
		p[i] = i < mx ? min(p[2 * id - i], mx - i) : 1;
		while (i - p[i] >= 0 && i + p[i] < n && s[i - p[i]] == s[i + p[i]]) {
			++p[i];
		}
		if (i + p[i] > mx) {
			mx = i + p[i];
			id = i;
		}
	}
	return;
}
int main() 
{
	int c = 0;
	while (true) {
		scanf("%s", str);
		if (str[0] == 'E') {
			return 0;
		}
		len = strlen(str);
		init();
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			ans = max(ans, p[i] - 1);
		}
		printf("Case %d: %d\n", ++c, ans);
	}
	return 0;
}
