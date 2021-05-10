#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = (a); i <= (b); ++i)

int read() {
  int f = 1;
  int x = 0;
  char ch = getchar();
  while (!(ch >= '0' && ch <= '9')) {
		
    if (ch == '-') {
      f = -1;
    }
    ch = getchar();
		
  }
	
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return f * x;
}

bool del[105];

int main() {
  vector <int> v;
  int n = read();
  rep (i, 1, n) {
    int x = read();
    v.push_back(x);
  }
  sort(v.begin(), v.end());
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (!del[i]) {
      del[i] = 1;
      ++ans;
      for (int j = i + 1; j < n; ++j) {
	if (v[j] % v[i] == 0) {
	  del[j] = 1;
	}
      }
    }
  }
  cout << ans << endl;
  return 0;
}
