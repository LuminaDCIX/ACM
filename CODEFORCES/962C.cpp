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

set <long long> s;

int tot, num[15];
bool del[15];

int tonum() {
  int x = 0;
  bool flg = 0;
  for (int i = tot; i >= 1; --i) {
    if (!del[i]) {
      if (num[i] == 0) {
        flg = 1;
        break;
      } else {
        break;
      }
    }
  }
  if (flg) {
    return 0;
  }
  for (int i = tot; i >= 1; --i) {
    if (del[i]) {
      continue;
    }
    x = x * 10 + num[i];
  }
  return x;
}

bool dfs(int nw, int dcnt, int tar) {
  if (nw == tot + 1) {
    
    return s.find(tonum()) != s.end();
  }
  if (dcnt < tar) {
    del[nw] = 1;
    if (dfs(nw + 1, dcnt + 1, tar)) {
      return true;
    }
    del[nw] = 0;
  }
  return dfs(nw + 1, dcnt, tar);
}

int main() {
  int k = sqrt(2e9) + 5;
  for (int i = 1; i <= k; ++i) {
    s.insert((long long) i * i);
  }

  int n = read();
  int x = n;
  while (x) {
    num[++tot] = x % 10;
    x /= 10;
  }

  for (int cnt = 0; cnt < tot; ++cnt) {
    memset(del, 0, sizeof(del));
    if (dfs(1, 0, cnt)) {
      printf("%d\n", cnt);
      return 0;
    }
  }
  puts("-1");
  
  return 0;
}

