#include <bits/stdc++.h>

using namespace std;

inline int read() {
  int f = 1;
  int x = 0;
  char ch = getchar();
  while (!isdigit(ch)) {
    f = (ch == '-') ? -1 : 1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return f * x;
}

const int N = 100000 + 5;
const int M = 200000 + 5;


int n;

int head[N];
int nxt[M], ver[M];
int tot = 1;

inline void add(int u, int v) {
  ++tot;
  nxt[tot] = head[u];
  ver[tot] = v;
  head[u] = tot;
}

bool vis[N];

int stk[N], top;
int dfn[N], low[N], dfs_cnt;
vector <int> bcc[N];
int bcc_cnt;
set <int> bel[N];

 
void dfs(int u, int fa) {
  low[u] = dfn[u] = dfs_cnt++;
  stk[top++] = u;
  for (int o = head[u]; o; o = nxt[o]) {
    int v = ver[o];
    if (dfn[v] == 0) {
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      
      if (low[v] >= dfn[u]) {
        
        ++bcc_cnt;
        int y = -1;
        do {
          y = stk[--top];
          bel[y].insert(bcc_cnt);
          bcc[bcc_cnt].push_back(y);
        } while (y != v);
         bel[u].insert(bcc_cnt);
        bcc[bcc_cnt].push_back(u);
      }
    } else {
      low[u] = min(low[u], dfn[v]);
    }
  }
}

bool in[N];
bool ok[M];

int fr[M], to[M];
int cnt[N];
void calc(int x, int y, int d) {
  if (bel[x].size() > bel[y].size()) {
    swap(x, y);
  }
  for (set <int>::iterator it = bel[x].begin(); it != bel[x].end(); ++it) {
    if (bel[y].find(*it) != bel[y].end()) {
      ++cnt[*it];
      return;
    }
  }
}

int main() {
  n = read();
  int m = read();
  for (int i = 1; i <= m; ++i) {
    int u = read();
    int v = read();
    add(u, v);
    add(v, u);
    fr[i] = u;
    to[i] = v;

  }
  for (int i = 1; i <= n; ++i) {
    if (!dfn[i]) { 
      dfs(i, 0);
    }
  }
  for (int i = 1; i <= m; ++i) {
    int u = fr[i];
    int v = to[i];
    calc(u, v, i);
  }
  for (int i = 1; i <= m; ++i) {
    int x = fr[i];
    int y = to[i];
    if (bel[x].size() > bel[y].size()) {
      swap(x, y);
    }
    for (set <int>::iterator it = bel[x].begin(); it != bel[x].end(); ++it) {
      if (bel[y].find(*it) != bel[y].end()) {
        if (cnt[*it] == bcc[*it].size()) {
          ok[i] = 1;
          break;
        }
      }
    }
  }
  // for (int i = 1; i <= bcc_cnt; ++i) {
  //   if (bcc[i].size() <= 2) {
  //     continue;
  //   }
  //   for (int j = 0; j < bcc[i].size(); ++j) {
  //     int u = bcc[i][j];
  //     in[u] = 1;

  //   }
  //   int cnt = 0;
  //   for (int j = 0; j < bcc[i].size(); ++j) {
  //     int u = bcc[i][j];
  //     for (int k = 0; k < bcc[i].size(); ++k) {
  //       int v = bcc[i][k];
  //       if (s.find(make_pair(u, v)) != s.end()) {
  //         ++cnt;
  //         if (cnt / 2 > bcc[i].size()) {
  //           break;
  //         }
  //       }
        
  //     }
  //     if (cnt / 2 > bcc[i].size()) {
  //       break;
  //     }
  //   }

  //   if (cnt / 2 == bcc[i].size()) {
  //     for (int j = 0; j < bcc[i].size(); ++j) {
  //       int u = bcc[i][j];
  //       for (int k = 0; k < bcc[i].size(); ++k) {
  //         int v = bcc[i][k];
  //         if (s.find(make_pair(u, v)) != s.end()) {
  //           ok[mp[make_pair(u, v)]] = 1;
  //         }
  //       }
  //     }
  //   }
  //   for (int j = 0; j < bcc[i].size(); ++j) {
  //     int u = bcc[i][j];
  //     in[u] = 0;
  //   }
    
  // }
  int ans = 0;
  for (int i = 1; i <= m; ++i) {
    if (ok[i]) {
      ++ans;
    }
  }
  cout << ans << endl;
  for (int i = 1; i <= m; ++i) {
    if (ok[i]) {
      printf("%d ", i);
    }
  }
  cout << endl;
  return 0;
}
