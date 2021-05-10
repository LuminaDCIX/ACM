#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

int n;

int cntl[N];
int cntr[N];

map<int, int> cnt;

int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    string s;
    cin >> s;
    int l = 0;
    int r = 0;
    for (int i = 0; i < (int)s.length(); ++i) {
      if (s[i] == '(') {
        ++l;
      } else {
        if (l) {
          --l;
        } else {
          ++r;
        }
      }
    }
    cntl[i] = l;
    cntr[i] = r;
  }
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (cntl[i] == 0) {
      ++cnt[cntr[i]];
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (cntr[i] == 0) {
      ans += cnt[cntl[i]];
    }
  }
  cnt.clear();
  for (int i = 1; i <= n; ++i) {
    if (cntr[i] == 0) {
      ++cnt[cntl[i]];
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (cntl[i] == 0) {
      ans += cnt[cntr[i]];
    }
  }
  cout << ans / 2 << endl;
  return 0;
}
