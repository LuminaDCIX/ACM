#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;
const int M = 2000 + 5;

int n;
int m;

vector <int> g[N];

void add(int u, int v) {
  g[u].push_back(v);
}

bool instk[N];

bool vis[N];
bool del[N];

bool dfs(int u) {
  vis[u] = 1;
  if (instk[u] == 1) {
    add(0, u);
    return 1;
  } else {
    instk[u] = 1;
  }

  for (int o = 0; o < (int) g[u].size(); ++o) {
    int v = g[u][o];
    if (!del[v] && dfs(v)) {
      add(0, u);
      return 1;
    }
  }
  instk[u] = 0;
  return 0;
}

bool dfs2(int u) {
  vis[u] = 1;
  if (instk[u] == 1) {
    return 1;
  } else {
    instk[u] = 1;
  }

  for (int o = 0; o < (int) g[u].size(); ++o) {
    int v = g[u][o];
    if (!del[v] && dfs2(v)) {
      return 1;
    }
  }
  instk[u] = 0;
  return 0;
}

/*


*/

bool get() {
  memset(vis, 0, sizeof(vis));
  memset(instk, 0, sizeof(instk));
  for (int i = 1; i <= n; ++i) {
    if (!vis[i] && !del[i]) {
      if (dfs2(i)) {
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    int u, v;
    cin >> u >> v;
    add(u, v);
  }

  for (int i = 1; i <= n; ++i) {
    del[i] = 1;
    if (get()) {
      continue;
    }
    del[i] = 0;

  }

  memset(instk, 0, sizeof(instk));
  memset(vis, 0, sizeof(vis));
  for (int i = 1; i <= n; ++i) {
    if (!vis[i] && !del[i]) {
      if (dfs(i)) {
        int ans = (int) g[0].size() - 1;
        cout << ans << endl;
        reverse(g[0].begin(), g[0].end());
        for (int i = 1; i <= ans; ++i) {
          cout << g[0][i] << endl;

        }
        return 0;
      }
    }
  }
  puts("-1");
  return 0;
}