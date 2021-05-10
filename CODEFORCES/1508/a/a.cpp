#include <bits/stdc++.h>

using namespace std;


int main() {
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--) {
    string s[3];
    int n;
    cin >> n;
    cin >> s[0] >> s[1] >> s[2];
    pair<int, int> cnt[3];
    cnt[0].first = cnt[1].first = cnt[2].first = 0;
    cnt[0].second = 0;
    cnt[1].second = 1;
    cnt[2].second = 2;
    for (int i = 0; i < 2 * n; ++i) {
      for (int j = 0; j < 3; ++j) {
	cnt[j].first += (s[j][i] == '0');
      }
    }
    sort(cnt, cnt + 3);
    char c;
    int x, y;
    if (cnt[1].first <= n) {
      c = '1';
      x = cnt[0].second;
      y = cnt[1].second;
    } else {
      c = '0';
      x = cnt[2].second;
      y = cnt[1].second;
    }
    int i = 0;
    int j = 0;
    while (i < 2 * n && j < 2 * n) {
      int ci = i;
      int cj = j;
      while (ci < 2 * n && s[x][ci] != c) {
	++ci;
      }
      while (cj < 2 * n && s[y][cj] != c) {
	++cj;
      }
      while (i < ci) {
	cout << s[x][i];
	i++;
      }
      while (j < cj) {
	cout << s[y][j];
	j++;
      }
      if (i < 2 * n && j < 2 * n) {
	cout << c;
	i++;
	j++;
      }
    }
    while (i < 2 * n) {
      cout << s[x][i];
      ++i;
    }
    while (j < 2 * n) {
      cout << s[y][j];
      ++j;
    }
    cout << endl;
  }
  return 0;
}



