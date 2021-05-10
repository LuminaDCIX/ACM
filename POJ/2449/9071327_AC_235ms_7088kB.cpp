#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
const int inf = 1000000000;
struct edge
{
  int to, nxt, val;
};
edge edges1[100005];
edge edges2[100005];
int tot1;
int tot2;
int head1[1005];
int head2[1005];
int n, m;
int s, t, k;
int h[1005];
struct node
{
  int x;
  int g;
  node(int _x, int _g)
  {
    x = _x;
    g = _g;
    return;
  }
  bool operator < (const node rhs) const
  {
    return g + h[x]> rhs.g + h[rhs.x];
  } 
};
void add_edge(edge* edges, int *head, int from, int to, int val, int &tot)
{
  edges[++tot].to = to;
  edges[tot].val = val;
  edges[tot].nxt = head[from];
  head[from] = tot;
  return;
}
void input()
{
  scanf("%d%d", &n, &m);
  int from, to, val;
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d%d", &from, &to, &val);
    add_edge(edges1, head1, to, from, val, tot1);
    add_edge(edges2, head2, from, to, val, tot2);
  }
  scanf("%d%d%d", &s, &t, &k);
  return;
}
bool inq[1005];
int que[5015], f, e;
void spfa()
{
  for (int i = 1; i <= n; ++i) {
    h[i] = inf;  
  }
  h[t] = 0;
  que[e++] = t;
  inq[t] = 1;
  while (f != e) {
    int u = que[f++];
    inq[u] = 0;
    for (int i = head1[u]; i; i = edges1[i].nxt) {
      int v = edges1[i].to;
      if (h[v] > h[u] + edges1[i].val) {
        h[v] = h[u] + edges1[i].val;
        if (inq[v]) {
          continue;
        }
        else {
          inq[v] = 1;
          que[e++] = v;
        }
      }
    }
  }
  return;
}
priority_queue <node> q;
int cnt[1005];
int Astar() 
{
  if (s == t) {
    k++;
  }
  q.push(node(s, 0));
  while (!q.empty()) {
    int len = q.top().g;
    int u = q.top().x;
    q.pop();
    cnt[u]++;
    if (cnt[t] == k) {
      return len;
    }
    if (cnt[u] > k) {
      continue;
    }
    for (int i = head2[u]; i; i = edges2[i].nxt) {
      int v = edges2[i].to;
      q.push(node(v, len + edges2[i].val));
    }
  }
  return -1;
}
void solve()
{
  spfa();
  if (h[s] == inf) {
    puts("-1");
    return;
  }
  int ans = Astar();
  printf("%d\n", ans);
  return;
}
int main()
{
  input();
  solve();
  return 0;
}