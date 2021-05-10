#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#define fir "John"
#define nxt "Brother"
using namespace std;

int main()
{
	int T, n;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		int cnt = 0;
		int v = 0;
		for (int i = 0, x; i < n; ++i) {
			scanf("%d", &x);
			if (x == 1) {
				++cnt;
			}
			v ^= x;
		}
		if (cnt == n) {
			puts(v == 0 ? fir : nxt);
			continue;
		}
		else {
			puts(v != 0 ? fir : nxt);
		}
	}
	return 0;
}
