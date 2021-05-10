#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

const int N = 2000 + 5;

int main()
{
	int x;
	scanf("%d", &x);
  if (x == 0 || x == 6 || x == 12 || x == 22 || x == 30 || x == 32 || x == 44 || x == 54 || x == 64 || x == 76 || x == 86 || x == 98 || x == 110 || x == 118 || x == 130 || x == 132 || x == 162 || x == 170 || x == 184 || x == 194 || x == 202 || x == 282 || x == 290 || x == 302 || x == 356 || x == 1046) {
		puts("2");
		return 0;
	}
	puts("1");
	return 0;
}
