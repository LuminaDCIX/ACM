#include <bits/stdc++.h>

using namespace std;

int a;
int f;
int b;
int k;

int main()
{
  scanf("%d %d %d %d", &a, &b, &f, &k);
  int now = b;
  int cnt = 0;
  for (int i = 1; i <= k + 1; ++i) {
    if (i == 1) {
      if (now < f) {
	puts("-1");
	return 0;
      }
      now -= f;
    } else if (i == k + 1) {
      int len = (k & 1) ? a - f : f;
      if (now < len) {
	++cnt;
	now = b;
      }
      if (now < len) {
	puts("-1");
	return 0;
      }
    } else if (! (i & 1)) {
      int len = (a - f) * 2;
      if (now < len) {
	now = b;
	++cnt;
      }
      if (now < len) {
	puts("-1");
	return 0;
      }
      now -= len;
    } else {
      int len = f * 2;
      if (now < len) {
	now = b;
	++cnt;
      }
      if (now < len) {
	puts("-1");
	return 0;
      }
      now -= len;
    } 
  }
  printf("%d\n", cnt);
  return 0;
}
