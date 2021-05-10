#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
int e[105][105], n, s, q, kase;
int main() {
	while(scanf("%d %d %d", &n, &s, &q) && (n && s && q)) {
		int u, v, value;
		if(kase) putchar('\n');
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) e[i][j] = 0x3f3f3f3f;
		for (int i = 1; i <= s; i++) {
			scanf("%d %d %d", &u, &v, &value);
			e[u][v] = e[v][u] = value;
		}
		for(int k = 1; k <= n; k ++)
			for (int i = 1; i <= n; i ++)
				for (int j = 1; j <= n; j++) {
					if (max(e[i][k], e[k][j]) < e[i][j]) e[i][j] = max(e[i][k], e[k][j]);
				}
		printf("Case #%d\n", ++kase);
		for (int i = 1; i <= q; i++) {
			scanf("%d %d", &u, &v);
			if (e[u][v] == 0x3f3f3f3f) printf("no path\n");
			else printf("%d\n", e[u][v]);
		}
	}
	return 0;
}
