#include <set>
#include <map>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

inline int read()
{
  int f = 1;
  int x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    f = (ch == '-') ? -1 : 1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return f * x;
}

using namespace std;

struct node {
  int l;
  int r;

  bool operator < (const node &rhs) const {
    return l == rhs.l ? r < rhs.r : l < rhs.l;
  }

  node (int _l, int _r) {
    l = _l;
    r = _r;
  }
};

const int N = 50000 + 5;

int n;
set <node> s;

struct atom {
  int x;
  int y;
  int c;
  int l;
  int r;
  
  bool operator < (const atom &rhs) const {
    return y < rhs.y;
  }
} a[N];

bool see[N];

map <int, int> mp;
int fa[N << 1];

int find(int x) {
  return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int main()
{
  n = read();
  for (int i = 0; i < n; ++i) {
    a[i].x = read();
    a[i].y = read();
    a[i].c = read();
  }
  sort(a, a + n);
  vector <int> v;
  for (int i = 0; i < n; ++i) {
    a[i].l = (-a[i].x - 1) * a[i].c;
    a[i].r = (-a[i].x) * a[i].c;
    v.push_back(a[i].l);
    v.push_back(a[i].r);
  }
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
  for (int i = 0; i < v.size(); ++i) {
    mp[v[i]] = i + 1;
  }
  for (int i = 1; i < (N * 2); ++i) {
    fa[i] = i;
  }
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    a[i].l = mp[a[i].l];
    a[i].r = mp[a[i].r];
  }
  for (int i = 0; i < n; ++i) {
    int fx = find(a[i].l);
    if (fx >= a[i].r) {
      continue;
    }
    for (int j = fx; j < a[i].r; j = find(j)) {
      fa[find(j)] = find(j + 1);
    }
    ++ans;
  }
  printf("%d\n", ans);
  return 0;
}
