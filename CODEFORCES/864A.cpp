#include <bits/stdc++.h>

using namespace std;

int a[105];

int main()
{
  int n;
  scanf("%d",&n);
  for (int i = 1, v; i <= n; ++i) {
    scanf("%d", &v);
    a[v]++;
  }
  for (int i = 1; i <= 100; ++i) {
    for (int j = 1; j <= 100; ++j) {
      if (i != j && a[i] + a[j] != 0 && a[i] + a[j] == n && a[i] == a[j]) {
	puts("YES");
	printf("%d %d\n", i, j);
	return 0;
      }
    }
  }
  puts("NO");
  return 0;
}
