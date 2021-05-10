#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
int num[N];
int s[N * 2 + 5];
int p[N * 2 + 5];
int lst[N * 2 + 5];
int n, T;
int len;
inline void init()
{
	for (int i = 0; i < n; ++i) {
		s[i * 2] = -1;
		s[i * 2 + 1] = num[i];
	}
	s[2 * n] = -1;
	n = 2 * n + 1;
	int id = 0;
	int mx = 0;
	for (int i = 0; i < n; ++i) {
		p[i] = i < mx ? min(p[id * 2 - i], mx - i) : 1;
		lst[i] = s[i + p[i] - 1];
		if (lst[i] == -1) {
			lst[i] = 1e9;
		}
		while (i - p[i] >= 0 && i + p[i] < n && (s[i + p[i]] <= lst[i]) && s[i + p[i]] == s[i - p[i]]) {
			if (s[i + p[i]] != -1) {
				lst[i] = s[i + p[i]];
			}
			++p[i];
		}
		if (i + p[i] > mx) {
			mx = i + p[i];
			id = i;
		}
	}
}
int main()
{
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &num[i]);
		}
		init();
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			ans = max(ans, p[i]);
		}
		printf("%d\n", (ans & 1) ? (ans / 2) * 2 : (ans - 1) / 2 * 2 + 1);
	}
	return 0;
}
