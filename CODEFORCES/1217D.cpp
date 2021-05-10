#include <bits/stdc++.h>

using namespace std;

const int N = 5000 + 5;

const int M = 5000 + 5;

vector <int> g[N];
vector <int> id[N];

int tot;

void add(int u, int v) {
  g[u].push_back(v);
  ++tot;
  id[u].push_back(tot);
}

int n;
int m;
int dfn[N];
int col[M];

void dfs(int u) {
  dfn[u] = 1;
  for (int i = 0; i < (int) g[u].size(); ++i) {
    int v = g[u][i];
    if (dfn[v] == -1) {
      dfs(v);
    } else if (dfn[v] == 1) {
      ++col[id[u][i]];
    } else {

    }
  }
  dfn[u] = 0;
}


int main() {
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    int u, v;
    cin >> u >> v;
    add(u, v);
  }

  memset(dfn, -1, sizeof(dfn));
  for (int i = 1; i <= n; ++i) {
    if (dfn[i] == -1) {
      dfs(i);
    }
  }
  int ans = 0;
  for (int i = 1; i <= m; ++i) {
    ans = max(ans, col[i]);
  }
  cout << ans + 1 << endl;
  for (int i = 1; i <= m; ++i) {
    if (i != 1) {
      cout.put(' ');
    }
    cout << col[i] + 1;
  }
  cout << endl;
  return 0;
}