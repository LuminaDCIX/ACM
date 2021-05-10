#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
int n, p;
struct edge
{
  int to, nxt;
} edges[605];
int tot = 0;
int head[305];
int size[305];
int deep[305];
int fa[305];
int sizeofdeep[305];
vector <int> nodeofdeep[305];
int now = 0;
int ans = 0;
void dfs(int x, int f) 
{
  for (int i = head[x]; i; i = edges[i].nxt) {
    int v = edges[i].to;
    if (v == f) {
      continue;
    }
    deep[v] = deep[x] + 1;
    fa[v] = x;
    dfs(v, x);
    size[x] += size[v];
  }
  size[x]++;
  return;
}
/*
void del(int x, int fa) 
{ //delete one of sonnode of x
  bool is_leaf = 1;
  for (int i = head[x]; i; i = edges[i].nxt) {
    int child = 0;
    int v = edges[i].to;
    if (v == fa) {
      continue;  
    }
    now -= size[v];
    is_leaf = 0;
    for (int j = head[x]; j; j = edges[j].nxt) {
      int t = edges[j].to;
      if (t == fa) {
        continue;  
      }
      if (t != v) {
        del(t, x);
        child++;
      }
    }
    if (!child) {
      ans = min(ans, now);
    }
    now += size[v];
  }
  if (is_leaf) {
    ans = min(ans, now);
  }
  return;
}
*/
bool is_del[305];
void color(int x, int c) 
{
  is_del[x] = c;
  for (int i = head[x]; i; i = edges[i].nxt) {
    int v = edges[i].to;
    if (fa[x] == v) {
      continue;
    }
    color(v, c);
  }
  return;
}
void del(int d) 
{
  bool ok = false;
  if (!nodeofdeep[d].size()) {
    ans = min(ans, now);
  }
  for (int i = 0; i < nodeofdeep[d].size(); ++i) {
    int v = nodeofdeep[d][i];
    if (is_del[v]) {
      continue;
    }
    now -= size[v];
    color(v, 1);
    del(d + 1);
    color(v, 0);
    now += size[v];
    ok = 1;
  }
  if (!ok) {
    ans = min(ans, now);
  }
}
inline void add_edge(int from, int to) 
{
  edges[++tot].nxt = head[from];
  edges[tot].to = to;
  head[from] = tot;
  return;
}
int main()
{
  scanf("%d%d", &n, &p);
  int from, to;
  for (int i = 1; i <= p; ++i) {
    scanf("%d%d", &from, &to);
    add_edge(from, to);
    add_edge(to, from);
  }
  deep[1] = 1;
  dfs(1, -1);
  for (int i = 1; i <= n; ++i) {
    nodeofdeep[deep[i]].push_back(i);
  }
  ans = 1305;
  now = n;
  del(2);
  printf("%d\n", ans);
  return 0;
} 