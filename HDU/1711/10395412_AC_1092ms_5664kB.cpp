#include <bits/stdc++.h>

using namespace std;

const int M = 10000 + 5;
const int N = 1000000 + 5;
int t[M];
int s[N];
int n, m;
int T;
int nxt[M];

inline void init() {
	memset(nxt, 0, sizeof(nxt));
	int j = 0;
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

inline int solve() {
	int j = 0;
	for (int i = 1; i <= n; ++i) {
		while (j > 0 && t[j + 1] != s[i]) {
			j = nxt[j];
		}
		if (t[j + 1] == s[i]) {
			++j;
		}
		if (j == m) {
			return i - j + 1;
		}
	}
	return -1;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &s[i]);
		}
		for (int i = 1; i <= m; ++i) {
			scanf("%d", &t[i]);
		}
		init();
		printf("%d\n", solve());
	}
	return 0;
}
