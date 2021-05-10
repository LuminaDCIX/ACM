#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

vector <int> g[N];
int f[N][2];

int n;
int k;

bool ok[N];
bool del[N];

void dfs(int u) {
  ok[u] = 1;
  int ori[2] = {del[f[u][0]], del[f[u][1]]};
  del[f[u][0]] = del[f[u][1]] = 1;
  for (int i = 0; i < 2; ++i) {
    int v = f[u][i];
    if (ori[i]) {
      continue;
    }
    del[v] = 1;
    for (int o = 0; o < (int) g[v].size(); ++o) {
      int x  = g[v][o];
      if (!ok[x] && (!del[f[x][0]] || !del[f[x][1]])) {
        dfs(x);
      }
    }
  }

}

int main() {
  ios::sync_with_stdio(false);
  cin >> k >> n;
  
  for (int i = 1; i <= n; ++i) {
    int u, v;
    cin >> u >> v;
    f[i][0] = u;
    f[i][1] = v;
    g[u].push_back(i);
    g[v].push_back(i);
  }

  for (int i = 1; i <= n; ++i) {
    if (!ok[i] && (!del[f[i][0]] || !del[f[i][1]])) {
      dfs(i);
    }
  }

  int ans = n;
  for (int i = 1; i <= n; ++i) {
    if (ok[i]) {
      --ans;
    }
  }

  cout << ans << endl;

  return 0;
}