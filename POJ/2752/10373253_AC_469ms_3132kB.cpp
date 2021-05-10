#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

const int N = 400005;
char s[N];
int nxt[N], n;

void solve() {
	memset(nxt, 0, sizeof(nxt));
	int j = 0;
	nxt[1] = 0;
	n = strlen(s + 1);
	for (int i = 2; i <= n; ++i) {
		while (j > 0 && s[j + 1] != s[i]) {
			j = nxt[j];
		}
		if (s[j + 1] == s[i]) {
			++j;
		}
		nxt[i] = j;
	}
}

int main() {
	while (scanf("%s", s + 1) != EOF) {
		solve();
		int i = nxt[n];
		vector <int> ans;
		ans.push_back(n);
		while (i > 0) {
			ans.push_back(i);
			i = nxt[i];
		}
		reverse(ans.begin(), ans.end());
		for (int i = 0; i < ans.size(); ++i) {
			printf("%d ", ans[i]);
		}
		puts("");
	}
	return 0;
}
