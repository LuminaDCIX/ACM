#include <bits/stdc++.h>

using namespace std;

inline int read() {
  int f = 1;
  int x = 0;
  char ch = getchar();
  while (!isdigit(ch)) {
    f = (ch == '-') ? -1 : 1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return f * x;
}



int main() {
  int n = read();
  int a = read();
  int b = read();
  string str;
  cin >> str;
  int nwa = a;
  int nwb = b;
  int lst = nwa > nwb;
  for (int i = 0; i < n; ++i) {
    if (str[i] == '*') {
      lst = nwa > nwb;
      continue;
    }
    if (lst) {
      nwa = max(0, nwa - 1);
      lst ^= 1;
    } else {
      nwb = max(0, nwb - 1);
      lst ^= 1;
    }
  }
  cout << a + b - nwa - nwb << endl;
  return 0;
}

