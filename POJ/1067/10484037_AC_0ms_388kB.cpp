#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>

using namespace std;

const double phi = (sqrt(5) + 1) * 0.5;
int n, m;

int main()
{
 	while (scanf("%d%d", &n, &m) != EOF) {
	  int a = max(n, m);
		int b = min(n, m);
		puts((int)((a - b) * phi) == b ? "0" : "1");
	}	
	return 0;
}
