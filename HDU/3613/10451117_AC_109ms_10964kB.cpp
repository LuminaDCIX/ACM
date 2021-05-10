#include <bits/stdc++.h>

using namespace std;

const int N = 500000 + 5;
char t[N];
char s[N << 1];
int T, n;
int val[275];
int p[N << 1];
int x[N << 1];
void init()
{
	s[0] = '#';
	for (int i = 0; i < n; ++i) {
		s[i * 2] = '#';
		s[i * 2 + 1] = t[i];
	}
	s[n * 2] = '#';
	int len = strlen(s);
	int mx = 0;
	int id = 0;
	for (int i = 0; i < len; ++i) {
		p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
		while (i - p[i] >= 0 && i + p[i] < len && s[i - p[i]] == s[i + p[i]]) {
			++p[i];
		}
		if (i + p[i] > mx) {
			id = i;
			mx = i + p[i];
		}
	}
}
int main() 
{
	scanf("%d", &T);
	while (T--) {
		for (int i = 'a'; i <= 'z'; ++i) {
			scanf("%d", &val[i]);
		}
		scanf("%s", t);
		n = strlen(t);
		init();
		int ans = 0;
		for (int i = 1; i <= 2 * n; ++i) {
			x[i] = x[i - 1] + val[s[i]];
		}
		for (int i = 2; i < 2 * n; i += 2) {
			int lmid = i / 2;
			int rmid = (n * 2 + i + 1) / 2;
			int t = 0;
			if (lmid + p[lmid] - 1 >= i) {
				t += x[lmid + p[lmid] - 1];
			}
			if (rmid + p[rmid] - 1 >= n * 2) {
				t += x[n * 2] - x[i];
			}
			ans = max(t, ans);
		}
		printf("%d\n", ans);
	}
	return 0;
}
