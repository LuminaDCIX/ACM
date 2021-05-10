#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;

vector<pair<int, int> > e;
vector<vector<int> > ans;
vector<vector<int> > now;
int ans_cnt;

int n;

void dfs(int u, int cnt) {
  if (u == (int) e.size()) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
          if (now[i][j] == 1 && now[j][k] == 1 && now[k][i] == 1) {
            return;
          }
        }
      }
    }
    if (ans_cnt < cnt) {
      ans_cnt = cnt;
      ans = now;
    }
    return;
  }
  int i = e[u].first;
  int j = e[u].second;
  dfs(u + 1, cnt);
  now[i][j] = now[j][i] = 1;
  dfs(u + 1, cnt + 1);
  now[i][j] = now[j][i] = 0;
}

int main() {
  cin >> n;
  now.resize(n);
  // ans.resize(n);
  for (int i = 0; i < n; ++i) {
    now[i].resize(n);
    // ans[i].resize(n);
    // for (int j = i + 1; j < n; ++j) {
    //   e.push_back(make_pair(i, j));
    // }
  }
  // dfs(0, 0);
  // cout << ans_cnt << endl;
  // for (int i = 0; i < n; ++i) {
  //   for (int j = 0; j < n; ++j) {
  //     cout << ans[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  // cout << endl;
  int k = (n + 1) / 2;
  cout << (n - k) * k << endl;
  for (int i = 0; i < k; ++i) {
    for (int j = k; j < n; ++j) {
      now[i][j] = now[j][i] = 1;
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      if (now[i][j]) {
        cout << i + 1 << " " << j + 1 << endl;
      }
    }
  }
  cout << endl;
  return 0;
}
