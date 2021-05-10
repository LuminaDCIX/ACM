#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
char str[N];
char trs[N];
char s[27];
char fs[27];
int n, T;
int nxt[N];
int extend[N];

inline void init() 
{
	memset(nxt, 0, sizeof(nxt));
	nxt[0] = n;
	int i = 0;
	while (i + 1 < n && str[i] == str[i + 1]) {
		++i;
	}
	nxt[1] = i;
	int p = 1;
	for (int i = 2; i < n; ++i) {
		if (i + nxt[i - p] < p + nxt[p]) {
			nxt[i] = nxt[i - p];
		}
		else {
			int j = p + nxt[p] - i;
			if (j < 0) {
				j = 0;
			}
			while (i + j < n && str[j] == str[i + j]) {
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
	int i = 0;
	while (i < n && str[i] == trs[i]) {
		++i;
	}
	extend[0] = i;
	int p = 0;
	for (i = 1; i < n; ++i) {
		if (i + nxt[i - p] < p + extend[p]) {
			extend[i] = nxt[i - p];
		}
		else {
			int j = p + extend[p] - i;
			if (j < 0) {
				j = 0;
			}
			while (i + j < n && str[j] == trs[i + j]) {
				++j;
			}
			extend[i] = j;
			p = i;
		}
	}
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("\n");
		for (int i = 0; i < 26; ++i) {
			s[i] = getchar();
			fs[s[i] - 'a'] = i;
		}
		scanf("%s", str);
		n = strlen(str);
		for (int i = 0; i < n; ++i) {
			trs[i] = s[str[i] - 'a'];
		}
		init();
		solve();
		int c = -1;
		if (n == 1) {
			putchar(str[0]);
			putchar(fs[str[0] - 'a'] + 'a');
			puts("");
			continue;
		}
		for (int i = n / 2; i < n; ++i) {
			if (n - i == extend[i] && (i) * 2 >= n) {
				c = i;
				break;
			}
		}
		if (c == -1) {
			for (int i = 0; i < n; ++i) {
				putchar(str[i]);
			}
			for (int i = 0; i < n; ++i) {
				putchar(fs[str[i] - 'a'] + 'a');
			}
			puts("");
			continue;
		}
		for (int i = 0; i < c; ++i) {
			putchar(str[i]);
		}
		for (int i = 0; i < c; ++i) {
			putchar(fs[str[i] - 'a'] + 'a');
		}
		puts("");
	}
	return 0;
}
