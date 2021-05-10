#include <bits/stdc++.h>

using namespace std;


int main() {
  long long n, m, c, d;
  cin >> n >> m >> c >> d;
  long long cnt1 = (n - floor((double)n / m) * m) * d;
  long long cnt2 = (ceil((double) n / m) * m - n) * c;
  cout << min(cnt1, cnt2) << endl;
  return 0;
}
