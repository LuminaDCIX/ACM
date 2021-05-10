// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

inline int getlen(int x) {
  int len = 0;
  while (x) {
    ++len;
    x /= 10;
  }
  return len;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int l, r;
    scanf("%d %d", &l, &r);
    vector <pair <int, long long> > v;
    for (long long i = 1, j = 0; i <= r; i *= 10, ++j) {
      long long k = ceil((double)l / i) * i;
      if (k >= l && k <= r) {
        v.push_back(make_pair((getlen(k) - j) * 2, k));
      }
      k = ceil((double) l / (5 * i)) * (5 * i);
      if (k >=l && k <= r) {
        v.push_back(make_pair((getlen(k) - j) * 2 - 1, k));
      }
    }
    sort(v.begin(), v.end());
    cout << v[0].second << endl;
  }
  return 0;
}
