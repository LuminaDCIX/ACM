#include <bits/stdc++.h>

using namespace std;

const int N = 50000 + 5;
char s[N];
char t[N];
int nxt[N];
int extend[N];

inline void init() 
{
	memset(nxt, 0, sizeof(nxt));
	int i = 0;
  int len = strlen(t);
	while (t[i + 1] == t[i] && i + 1 < len) {
		++i;
	}
	nxt[0] = len;
	nxt[1] = i;
	int p = 1;
	for (i = 2; i < len; ++i) {
		if (nxt[i - p] + i < p + nxt[p]) {
			nxt[i] = nxt[i - p];
		}
		else {
			int j = p + nxt[p] - i;
			if (j < 0) {
				j = 0;
			}
			while (i + j < len && s[i + j] == s[j]) {
				++j;
			}
			nxt[i] = j;
			p = i;
		}
	}
}
inline void solve()
{
	memset(extend, 0, sizeof(extend));
	int len = strlen(t);
	int n = strlen(s);
	int i = 0;
	while (s[i] == t[i] && i < min(len, n)) {
		++i;
	}
	extend[0] = i;
	int p = 0;
	for (int i = 1; i < n; ++i) {
		if (i + nxt[i - p] < p + extend[p]) {
			extend[i] = nxt[i - p];
		}
		else {
			int j = p + extend[p] - i;
			if (j < 0) {
				j = 0;
			}
			while (j < len && i + j < n && s[i + j] == t[j]) {
				++j;
			}
			extend[i] = j;
			p = i;
		}
	}
}

int main() {
	while(scanf("%s", t) != EOF) {
		scanf("%s", s);
		init();
		solve();
		int n = strlen(s);
		int p = -1;
		for (int i = 0; i < n; ++i) {
			if (extend[i] == n - i) {
				p = i;
				break;
			}
		}
		if (p == -1) {
			puts("0");
		}
		else {
			for (int i = p; i < n; ++i) {
				putchar(s[i]);
			}
			printf(" %d\n", extend[p]);
		}
	}
	return 0;
}
