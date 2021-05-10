// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;

struct kmp {
  int nxt[N];
  
  vector <int>  solve(char *s, char *t) {
    int n = strlen(s + 1);
    int m = strlen(t + 1);
    nxt[1] = 0;
    int j = 0;
    for (int i = 2; i <= m; ++i) {
      while (j != 0 && t[j + 1] != t[i]) {
        j = nxt[j];
      }
      if (t[j + 1] == t[i]) {
        ++j;
      }
      nxt[i] = j;
    }
    j = 0;
    vector <int> pos;
    for (int i = 1; i <= n; ++i) {
      while (j != 0 && t[j + 1] != s[i]) {
        j = nxt[j];
      }
      if (t[j + 1] == s[i]) {
        ++j;
      }
      if (j == m) {
        pos.push_back(i - m + 1);
      }
    }
    return pos;
  }
}k;

char s[N], t[N];

int main() {
  scanf("%s %s", s + 1, t + 1);
  vector <int> ans = k.solve(s, t);
  for (int i = 0; i < (int) ans.size(); ++i) {
    printf("%d\n", ans[i]);
  }
  int m = strlen(t + 1);
  for (int i = 1; i <= m; ++i) {
    printf("%d ", k.nxt[i]);
  }
  puts("");
  return 0;
}
