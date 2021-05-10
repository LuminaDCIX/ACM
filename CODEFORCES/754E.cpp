#include <bits/stdc++.h>

using namespace std;



namespace XDYIMCMI0LY {

  const int N = 400 + 5;

  int n;
  int m;
  int r;
  int c;

  char s[N][N];
  char t[N][N];

  
    bitset<N> b[26][N];
    bitset<N> ans[N];


  bitset<N> shift(bitset<N> x, int k) {
    return (x >> k) | (x << (m - k));
  }
  
  void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
      cin >> s[i];
    }

    
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        int c = (int) s[i][j] - 'a';
        b[c][i][j] = 1;
      }
    }
    cin >> r >> c;
    for (int i = 0; i < r; ++i) {
      cin >> t[i];
    }
    
    
    for (int i = 0; i < n; ++i) {
      ans[i] = ~ans[i];
    }

    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        if (t[i][j] == '?') {
          continue;
        }
        int p = t[i][j] - 'a';
        
        for (int k = 0; k < n; ++k) {
          
          int x = (k + i) % n;
          if (ans[k].count() == 0) {
            continue;
          }
          if (b[p][x].count() == 0) {
            ans[k].reset();
          } else {
            ans[k] &= shift(b[p][x], j % m);
          }
        }
      }
    }

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cout << ans[i][j];
      }
      cout << endl;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  XDYIMCMI0LY::solve();
  flush(cout);
  return 0;
}
