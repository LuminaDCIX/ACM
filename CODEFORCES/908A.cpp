#include <bits/stdc++.h>

using namespace std;;

char s[55];


int main() {
  int cnt = 0;
  scanf("%s", s);
  int len = strlen(s);
  for (int i = 0; i < len; ++i) {
    if (s[i] >= '0' && s[i] <= '9') {
      if ((s[i] - '0') & 1) {
        ++cnt;
      }
    } else {
      if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') {
        ++cnt;
      }
    }
  }
  printf("%d\n", cnt);
  return 0;
}

