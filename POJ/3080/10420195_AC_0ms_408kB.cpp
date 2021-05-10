#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cstdio>

using namespace std;

const int N = 60 + 5;
char str[15][N];
char t[N];
int nxt[N];
int n, T, k;
char s[N];
char p[N];

inline void init(int l, int r)
{
  int j = -1;
  memset(nxt, -1, sizeof(nxt));
  n = r - l + 1;
  for (int i = 1; i < n; ++i) {
    while (j != -1 && s[j + 1] != s[i]) {
      j = nxt[j];    
    }
    if (s[j + 1] == s[i]) {
      ++j;    
    }
    nxt[i] = j;
  }
}

inline bool _find(int k)
{ 
  int j = -1;
  for (int i = 0; i < 60; ++i) {
    while (j != -1 && str[k][i] != s[j + 1]) {
      j = nxt[j];    
    }
    if (str[k][i] == s[j + 1]) {
      ++j;    
    }
    if (j == n - 1) {
      return true;    
    }
  }
  return false;
}

inline bool check(int l, int r) 
{
  for (int i = 0; i < r - l + 1; ++i) {
    s[i] = str[1][l + i];      
  }
  init(l, r);
  for (int i = 2; i <= k; ++i) {
    if (!_find(i)) {
      return false;        
    }
  }
  return true;
}

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &k);
    for (int i = 1; i <= k; ++i) {
      scanf("%s", str[i]);
    }
    int l = -1;
    int r = -1;
    int ans = 0;
    for (int i = 0; i < 60; ++i) {
      for (int j = i; j < 60; ++j) {
        if (check(i, j)) {
          if (j - i + 1 > ans) {
            ans = j - i + 1;
            l = i;
            r = j;
            for (int l = 0; l < j - i + 1; ++l) {
              p[l] = s[l];    
            }
          }
          else if (j - i + 1 == ans && strcmp(s, p) < 0) {
            for (int l = 0; l < j - i + 1; ++l) {
              p[l] = s[l];    
            }
          }
        }
      }
    }
    if (ans < 3) {
      puts("no significant commonalities");   
      continue;
    }
    for (int i = 0; i < ans; ++i) {
      printf("%c", p[i]);    
    }
    puts("");
  }
  return 0;
}