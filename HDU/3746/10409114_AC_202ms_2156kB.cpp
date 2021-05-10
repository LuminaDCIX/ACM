#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
int T, n;
char s[N];
int nxt[N];

inline void init() {
	memset(nxt, -1, sizeof(nxt));
	nxt[0] = -1;
	int j = -1;
	for (int i = 1; i < n; ++i) {
		while (j != -1 && s[j + 1] != s[i]) {
			j = nxt[j];		
		}
		if (s[j + 1] == s[i]) {
			++j;
		}
		nxt[i] = j;
	}
	return;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%s", s);
		n = strlen(s);
		init();
		int cir = n - nxt[n - 1] - 1;
		if (cir == n) {
		    printf("%d\n", n);
		    continue;
		}
		if (n % cir == 0) {
		    printf("%d\n", 0);
		    continue;
		}
		printf("%d\n", ((n - 1) / cir + 1) * cir - n);
	}
	return 0;	
}