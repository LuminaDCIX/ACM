#include <bits/stdc++.h>

using namespace std;

int main() {
  int x;
  cin >> x;
  if (x % 2 == 0) {
    cout << 0.5000000000 << endl;
  } else {
    cout << 1 - (x - 1.0) / 2 / x << endl;
  }
  return 0;
}