// luogu-judger-enable-o2
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

const int N = 1000000 + 5;
const int P = 1e9 + 7;

inline void add(int &a, int b) {
  a += b;
  if (a >= P) {
    a -= P;
  }
}
inline void sub(int &a, int b) {
  a -= b;
  if (a < 0) {
    a += P;
  }
}

int n, m, p;

int no[N][11];
bool ok(int a, int b) {
  if (abs(a - b) > p) {
    return false;
  }
  return !no[a][a - b + 4];
}

namespace solve1 {

  int a[N];
  
  bool check() {
    for (int i = 2; i <= n; ++i) {
      if (!ok(a[i - 1], a[i])) {
        return false;
      }
    }
    if (!ok(a[n], a[1])) {
      return false;
    }
    return true;
  }
  
  void solve() {
    int ans = 0;
    if (n & 1) {
      int top = 0;
      for (int i = 1; i <= n; i += 2) {
        a[++top] = i;
      }
      for (int i = n - 1; i > 0; i -= 2) {
        a[++top] = i;
      }
      if (check()) {
        ++ans;
      }
      top = 0;
      a[++top] = 1;
      for (int i = 2; i <= n; i += 2) {
        a[++top] = i;
      }
      for (int i = n; i > 1; i -= 2) {
        a[++top] = i;
      }
      if (check()) {
        ++ans;
      }
    } else {
      int top = 0;
      for (int i = 1; i <= n; i += 2) {
        a[++top] = i;
      }
      for (int i = n; i >= 2; i -= 2) {
        a[++top] = i;
      }
      if (check()) {
        ++ans;
      }
      top = 0;
      a[++top] = 1;
      for (int i = 2; i <= n; i += 2) {
        a[++top] = i;
      }
      for (int i = n - 1; i >= 3; i -= 2) {
        a[++top] = i;
      }
      if (check()) {
        ++ans;
      }
    }
    cout << ans << endl;
  }
}

namespace solve2 {

  int f[N], g[N];

  int F(int x) ;
  int G(int x) ;

  int F(int x) {
    if (f[x] != -1) {
      return f[x];
    }
    int ans = 0;
    if (ok(x + 0, x + 2)) {
      add(ans, G(x + 1));
    }
    if (ok(x + 0, x + 3) && ok(x + 2, x + 1)) {
      add(ans, G(x + 2));
    }
    if (ok(x + 0, x + 3) && ok(x + 3, x + 2) && ok(x + 2, x + 5) && ok(x + 4, x + 1)) {
      add(ans, G(x + 4));
    }
    if (ok(x + 0, x + 3) && ok(x + 3, x + 6) && ok(x + 5, x + 2) && ok(x + 2, x + 4) && ok(x + 4, x + 1)) {
      add(ans, G(x + 5));
    }
  
    return f[x] = ans;
  }
  
  int G(int x) {
    if (g[x] != -1) {
      return g[x];
    }
    int ans = 0;
    if (ok(x + 2, x + 0)) {
      add(ans, F(x + 1));
    }
    if (ok(x + 1, x + 2) && ok(x + 3, x + 0)) {
      add(ans, F(x + 2));
    }
    if (ok(x + 1, x + 4) && ok(x + 5, x + 2) && ok(x + 2, x + 3) && ok(x + 3, x + 0)) {
      add(ans, F(x + 4));
    }
    if (ok(x + 1, x + 4) && ok(x + 4, x + 2) && ok(x + 2, x + 5) && ok(x + 6, x + 3) && ok(x + 3, x + 0)) {
      add(ans, F(x + 5));
    }

    g[x] = ans;
    return ans;
  }

  
  void solve() {
    memset(f, -1, sizeof(f));
    memset(g, -1, sizeof(g));
    if (n <= 8) {
      static int a[10];
      int top = 0;
      int ans = 0;
      for (int i = n; i >= 1; --i) {
        a[++top] = n - i;
      }
      while (next_permutation(a + 1, a + top + 1)) {
        if (ok(a[top], a[1])) {
          bool flg = 1;
          for (int j = 2; j <= top; ++j) {
            if (!ok(a[j - 1], a[j])) {
              flg = 0;
              break;
            }
          }
          if (flg) {
            ++ans;
          }
        }
      }
      cout << ans / n << endl;
      return;
    }
    
    for (int i = 2; i <= 8; ++i) {
      static int a[10];
      int top = 0;
      for (int j = n - i; j <= n - 1; ++j) {
        a[++top] = j;
      }
      f[n - i] = 0;
      g[n - i] = 0;
      while (next_permutation(a + 1, a + top + 1)) {
        if (ok(n - i + 1, n - i) && a[1] == n - i && a[top] == n - i + 1) {
          bool flg = 1;
          for (int j = 2; j <= top; ++j) {
            if (!ok(a[j - 1], a[j])) {
              flg = 0;
              break;
            }
          }
          if (flg) {
            ++f[n - i];
          }
        }
        if (ok(n - i, n - i + 1) && a[1] == n - i + 1 && a[top] == n - i) {
          bool flg = 1;
          for (int j = 2; j <= top; ++j) {
            if (!ok(a[j - 1], a[j])) {
              flg = 0;
              break;
            }
          }
          if (flg) {
            ++g[n - i];
          }
        }
      }
    }
    int ans = F(0);
    if (!ok(1, 0)) {
      ans = 0;
    }
    if (ok(0, 1) && ok(2, 0)) {
      add(ans, F(1));
    }
    if (ok(0, 3) && ok(4, 1) && ok(1, 2) && ok(2, 0)) {
      add(ans, F(3));
    }
    if (ok(0, 3) && ok(3, 1) && ok(1, 4) && ok(5, 2) && ok(2, 0)) {
      add(ans, F(4));
    }
    if (ok(0, 1) && ok(1, 2) && ok(3, 0)) {
      add(ans, F(2));
    }
    if (ok(0, 1) && ok(1, 4) && ok(5, 2) && ok(2, 3) && ok(3, 0)) {
      add(ans, F(4));
    }
    if (ok(0, 1) && ok(1, 4) && ok(4, 2) && ok(2, 5) && ok(6, 3) && ok(3, 0)) {
      add(ans, F(5));
    }
    if (ok(0, 2) && ok(2, 1) && ok(1, 4) && ok(3, 0)) {
      add(ans, G(3));
    }
    if (ok(0, 2) && ok(2, 5) && ok(4, 1) && ok(1, 3) && ok(3, 0)) {
      add(ans, G(4));
    }
    cout << ans << endl;
  }
}


int main() {
  n = read();
  m = read();
  p = read();
  if (n == 1) {
    puts("1");
    return 0;
  }
  if (n == 2) {
    puts(m ? "0" : "1");
    return 0;
  }

  if (p == 0) {
    puts(n > 1 ? "0" : "1");
  } else if (p == 1) {
    if (n == 1) {
      puts("1");
    } else if (n == 2) {
      puts(m ? "0" : "1");
    } else {
      puts("0");
    }
  } else {
   
    if (p == 2) {
      for (int i = 1; i <= m; ++i) {
        int u = read();
        int v = read();
        if (abs(u - v) <= p) {
          no[u][u - v + 4] = 1;
        }
      }
      solve1::solve();
    } else {
      for (int i = 1; i <= m; ++i) {
        int u = read();
        int v = read();
        u = n - u;
        v = n - v;
        if (abs(u - v) <= p) {
          no[u][u - v + 4] = 1;
        }
      }
      solve2::solve();
    } 
  }
  return 0;
}
