#include <bits/stdc++.h>

using namespace std;

namespace XDYIMCMI0LY {

  const int N = 25;

  int main() {
    int a;
    int b;
    int c;
    int n;

    cin >> a >> b >> c>> n;
    
    if (c > a || c> b) {
      puts("-1");
      return 0;
    }
    if (a > n || b > n || c > n) {
        puts("-1");
        return 0;
      }
    
    c = a + b - c;
    if (c < 0) {
      puts("-1");
    } else {
      if (n - c <= 0) {
        puts("-1");
      } else {
        cout << n - c << endl;
      }
    }
      
  }
}

int main() {
  cin.tie(0);
  cout.tie(0);
  ios::sync_with_stdio(false);
  XDYIMCMI0LY::main();
  return 0;
}
