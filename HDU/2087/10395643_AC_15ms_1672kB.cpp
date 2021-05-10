#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;
char t[N];
char s[N];
int n, m;
int nxt[N];

void init() {
	int j = 0;
	memset(nxt, 0, sizeof(nxt));
	nxt[1] = 0;
	for (int i = 2; i <= m; ++i) {
		while (j > 0 && t[j + 1] != t[i]) {
			j = nxt[j];
		}
		if (t[j + 1] == t[i]) {
			++j;
		}
		nxt[i] = j;
	}
}
inline int solve(int x) {
	int cnt = 0;
	int j = 0;
	for (int i = x; i <= n; ++i) {
		while (j > 0 && s[i] != t[j + 1]) {
			j = nxt[j];
		}
		if (s[i] == t[j + 1]) {
			++j;
		}
		if (j == m) {
			++cnt;
			j = 0;
		}
	}
	return cnt;
}
int main() {
	while (true) {
		scanf("%s", s + 1);
		if (s[1] == '#') {
			return 0;
		}
		scanf("%s", t + 1);
		n = strlen(s + 1);
		m = strlen(t + 1);
		init();
		int ans = 0;
		for (int i = 1; i <= n; ++i) {
			ans = max(ans, solve(i));
		}
		printf("%d\n", ans);
	}
	return 0;
}
