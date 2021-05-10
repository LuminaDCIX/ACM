#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;
int T;
int n;
char str[N];
int nxt[N];
bool exi[N];
inline void init()
{
	int j = -1;
	nxt[0] = -1;
	for (int i = 1; i < n; ++i) {
		while (j != -1 && (str[j + 1] != str[i]) || j > (i + 1) / 2 - 1) {
			j = nxt[j];
		}
		if (str[j + 1] == str[i]) {
			++j;
		}
		while (j > (i + 1) / 2 - 1) {
			j = nxt[j];
		}
		if (j != -1) {
			exi[j] = 1;
		}
		nxt[i] = j;
	}
}
int main()
{
	scanf("%d", &T);
	while (T--) {
		scanf("%s", str);
		n = strlen(str);
		memset(exi, 0, sizeof(exi));
		init();
		int j = nxt[n - 1];
		while (j != -1) {
			if (exi[j] && (j + 1) * 3 <= n) {
				break;
			}
			j = nxt[j];
		}
		printf("%d\n", j + 1);
	}
	return 0;
}
