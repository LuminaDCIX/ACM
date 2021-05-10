#include <bits/stdc++.h>

using namespace std;


namespace XDYIMCMI0LY {

  const int N = 25;

  char s[N];

  int cnt[15];
  long long fac[200];

  
  long long res;
  long long t;

  bool ok[N];

  void dfs(int n, long long p, int nw) {
    if (n < 0) {
      return;
    }
    if (n == 0) {
      for (int i = 0; i < 10; ++i) {
        if (cnt[i] && !ok[i]) {
          return;
        }
      }

      
      res += t / p;
      return;
    }
    if (nw > 9) {
      return;
    }
    if (cnt[nw] == 0) {
      dfs(n, p, nw + 1);
    } else {
      for (int i = 1; i <= cnt[nw]; ++i) {
        ok[nw] = 1;
        dfs(n - i, p * fac[i], nw + 1);
        ok[nw] = 0;
      }
    }
  }
  
  long long calc(int n) {
    res = 0;
    t = fac[n];
    dfs(n, 1, 0);
    return res;
  }

    void dfs2(int n, long long p, int nw) {
    if (n < 0) {
      return;
    }
    if (n == 0) {
      for (int i = 1; i < 10; ++i) {
        if (cnt[i] && !ok[i]) {
          return;
        }
      }
      res += t / p;
      return;
    }
    if (nw > 9) {
      return;
    }
    if (cnt[nw] == 0) {
      dfs(n, p, nw + 1);
    } else {
      int start = (nw != 0);
      for (int i = start; i <= cnt[nw]; ++i) {
        ok[nw] = 1;
        dfs(n - i, p * fac[i], nw + 1);
        ok[nw] = 0;
      }
    }
  }
  
  long long calc2(int n) {
    res = 0;
    t = fac[n];
    dfs2(n, 1, 0);
    return res;
  }
 
  
  void main() {
    cin >> s + 1;
    int n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) {
      ++cnt[s[i] - '0'];
    }
    fac[0] = 1;
    for (int i = 1; i <= 20; ++i) {
      fac[i] = fac[i - 1] * i;
    }
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
      ans += calc(i);
      if (cnt[0]) {
        --cnt[0];
        ans -= calc2(i - 1);
        ++cnt[0];
      }
    }
    cout << ans << endl;
    return;
  }
}

int main() {
  cin.tie(0);
  cout.tie(0);
  ios::sync_with_stdio(false);
  XDYIMCMI0LY::main();
  return 0;
}
