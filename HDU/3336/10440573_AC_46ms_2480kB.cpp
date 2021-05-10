#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 200000 + 5;
const int mod = 10007;
int nxt[N];
char s[N];
int T, n;

inline void init() 
{
	memset(nxt, 0, sizeof(nxt));
	nxt[0] = n;
	int i = 0;
	while (nxt[i] == nxt[i + 1]) {
		++i;
	}
	nxt[1] = i;
	int p = 1;
	for (i = 2; i < n; ++i) {
		if (i + nxt[i - p] < p + nxt[p]) {
			nxt[i] = nxt[i - p];
		}
		else {
			int j = p + nxt[p] - i;
			if (j < 0) {
				j = 0;
			}
			while (i + j < n && s[i + j] == s[j]) {
				++j;
			}
			nxt[i] = j;
			p = i;
		}
	}
}
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		scanf("%s", s);
		init();
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			ans = (ans + nxt[i]) % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
