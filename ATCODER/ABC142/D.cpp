#include <bits/stdc++.h>

using namespace std;

void get(long long x, map <long long, int> &m) {
  for (long long i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      m[i] = 1;
      while (x % i == 0) {
        x /= i;
      }
    }
  }
  if (x > 1) {
    m[x] = 1;
  }
  return;
}

map <long long, int> m[2];

int main() {
  long long A, B;
  cin >> A >> B;
  get(A, m[0]);
  get(B, m[1]);
  int ans = 0;
  for (map<long long, int>::iterator it = m[0].begin(); it != m[0].end(); ++it) {
    if (m[1][(*it).first]) {
      ++ans;
    }
  }
  cout << ans + 1 << endl;
  return 0;
}