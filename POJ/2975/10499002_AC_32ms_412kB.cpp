#include <cstdio>

using namespace std;

const int N = 1000 + 5;
int n;
int x[N];

int main()
{
	while (scanf("%d", &n) && n) {
		int v = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &x[i]);
				v ^= x[i];
		}
		if (v == 0) {
			puts("0");
			continue;
		}
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			if (x[i] > (v ^ x[i])) {
				++cnt;
			}
		}
		printf("%d\n", cnt);
	}
}
