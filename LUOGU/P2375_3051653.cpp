#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;
const long long p = 1000000007;
char s[N];
int nxt[N];
int num[N];
int cnt[N];
int T, n;

inline void init()
{
	int j = -1;
	nxt[0] = -1;
	cnt[0] = 1;
	for (int i = 1; i < n; ++i) {
		while (j != -1 && s[j + 1] != s[i]) {
			j = nxt[j];
		}
		if (s[j + 1] == s[i]) {
			++j;
		}
		nxt[i] = j;
		cnt[i] = (j == -1 ? 0 : cnt[j]) + 1;
	}
}

int main() 
{
	scanf("%d", &T);
	while (T--) {
		scanf("%s", s);
		n = strlen(s);
		init();
		long long ans = 1;
		int j = -1;
		for (int i = 0; i < n; ++i) {
			while ((j != -1 && s[j + 1] != s[i]) || j > (i + 1) / 2 - 1) {
				j = nxt[j];
			}
			if (s[j + 1] == s[i] && j + 1 <= (i + 1) / 2 - 1) {
				++j;
			}
			else if (j != -1 && j + 1 > (i + 1) / 2 - 1) {
				j = nxt[j];
				if (s[j + 1] == s[i]) {
					++j;
				}
			}
			num[i] = j == -1 ? 0 : cnt[j];
			ans = ans * (cnt[j] + 1) % p;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
