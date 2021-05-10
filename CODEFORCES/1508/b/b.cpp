#include <bits/stdc++.h>

using namespace std;

vector<int> ans;

bool dfs(int n, long long k) {
  if (n == 1) {
    ans.push_back(1);
    return k == 1 ? true : false;
  }
  if (n - 2 >= 63) {
    ans.push_back(1);
    return dfs(n - 1, k);
  }
  long long t = 1LL << (n - 2);
  int siz = 1;
  long long now = 0;
  while (now + t < k) {
    now += t;
    t >>= 1;
    ++siz;
    if (t == 0) {
      if (now == k - 1) {
	ans.push_back(n);
	return true;
      }
      return false;
    }
  }
  ans.push_back(siz);
  return dfs(n - siz, k - now);
}

int main() {
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--) {
    int n;
    long long k;
    cin >> n >> k;
    ans.clear();
    if (dfs(n, k)) {
      int seq[n];
      memset(seq, 0, sizeof(seq));
      iota(seq, seq + n, 0);
      int now = 0;
      for (int i = 0; i < (int) ans.size(); ++i) {
	int t = ans[i];
	reverse(seq + now, seq + now + t);
	now += t;
      }
      for (int i = 0; i < n; ++i) {
	cout << seq[i] + 1 << " ";
      }
      cout << endl;
    } else {
      cout << -1 << endl;
    }
  }
  return 0;
}
