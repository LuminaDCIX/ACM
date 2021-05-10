#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

const int N = 1000005; 
char s[N];
int nxt[N];
int n;

inline void init() {
	memset(nxt, 0, sizeof(nxt));
	nxt[1] = 0;
	int j = 0;
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
	while (true) {
		scanf("%s", s + 1);
		if (s[1] == '.') {
			return 0;
		}
		n = strlen(s + 1);
		init();
		int k = n - nxt[n];
		printf("%d\n", n % k == 0 ? n / k : 1);
	}
	return 0;
}
