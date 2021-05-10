#include <bits/stdc++.h>

using namespace std;

#define y1 temp_y1
#define all(x) x.begin(), x.end()

const int N = 3e5 + 5;

int n;

int lst[N];
int fa[N];

vector<int> g[N];

int min_leaf = -1;
int ext_cnt = 0;
bool ok = true;

void dfs1(int u, int k) {
  for (auto v : g[u]) {
    dfs1(v, k);
  }
  if (ext_cnt < k && lst[u] != ext_cnt) {
    ok = false;
  }
  if (ext_cnt == k) {
    min_leaf = u;
  }
  ++ext_cnt;
}

long long ans = 0;
int seq[N];
int dfs_cnt = 0;
int siz[N];

void dfs2(int u, int k, int dep) {
  seq[u] = dfs_cnt++;
  if (lst[u] < k) {
    ans += dep;
    siz[u]++;
  }
  for (auto v : g[u]) {
    dfs2(v, k, dep + 1);
    siz[u] += siz[v];
  }
  if (lst[u] < k && lst[u] != ext_cnt) {
    ok = false;
  }
  if (lst[u] >= k && siz[u] + seq[u] != lst[u]) {
    ok = false;
  }
  ++ext_cnt;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> lst[i];
    --lst[i];
  }
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    --u;
    --v;
    fa[v] = u;
    g[u].push_back(v);
  }
  for (int i = 0; i < n; ++i) {
    sort(all(g[i]), [&](int x, int y) -> bool {
      return lst[x] < lst[y];
    });
  }

  if (lst[0] == 0) {
    dfs2(0, 0, 0);
    if (ok) {
      cout << "YES" << endl;
      cout << 0 << endl;
      for (int i = 0; i < n; ++i) {
        cout << lst[i] + 1 << " ";
      }
      cout << endl;
      return 0;
    } else {
      cout << "NO" << endl;
      return 0;
    }
  }
  int v = lst[0] - 1;
  dfs1(0, v);
  int u = min_leaf;
  bool is_find = false;
  fa[0] = -1;
  //cerr << v + 1 << " " << u + 1 << " " << lst[u] + 1 <<endl;
  do {
    if (lst[u] == v) {
      is_find = true;
    }
    if (lst[u] == v && fa[u] != -1) {
      swap(lst[u], lst[fa[u]]);
      ++ans;
    }
    u = fa[u];
  } while (u != -1);
  if (!is_find) {
    cout << "NO" << endl;
    return 0;
  }
  ext_cnt = 0;
  dfs2(0, v, 0);

  if (ok) {
    cout << "YES" << endl;
    cout << ans << endl;
    for (int i = 0; i < n; ++i) {
      cout << seq[i] + 1 << " " ;
    }
    cout << endl;
  } else {
    cout << "NO" << endl;
  }
  return 0;
}
