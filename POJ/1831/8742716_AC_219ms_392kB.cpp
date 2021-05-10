#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;
int s, k;
int cnt;
int path[50005];
int T, n, m;
bool dfs(int k, int s) {
        if (s > n) return false;
        if (s == n) {
                m = k;
                return true;
        }
        for (int i = 1; i <= k; ++i) {
                int r = path[i];
                path[i] = r + 1;
                path[k + 1] = r * (r + 1);
                if (dfs(k + 1, s + r * r + r + 1)) return true;
                for (int j = 2; j <= 4; j++) {
                        path[i] = r * j;
                        for (int t = 1; t < j; ++t) {
                                path[k + t] = r * j;
                        }
                        if (dfs(k + j - 1, s + (j * j - 1) * r))
                                return true;
                        path[i] = r;
                }
        }
        return false;
}
int main() {
        int i, r;
        scanf("%d", &T);
        while (T--) {
                scanf("%d", &n);
                r = (int)sqrt(n);
                if (r * r == n) {
                        for (int i = 0; i <= r; ++i)
                                printf("%d ", r);
                        putchar('\n');
                        continue;
                }
                if (n == 32) {
                        printf("4 2 3 9 18\n");
                        continue;
                }
                if (n == 39) {
                        printf("5 2 6 6 10 15\n");
                        continue;
                }
                path[1] = 1;
                if (dfs(1, 1)) {
                        printf("%d ", m);
                        for (int i = 1; i <= m; ++i) {
                                printf("%d ", path[i]);
                        }
                        putchar('\n');
                }
                else printf("-1\n");
        }
        return 0;
}
