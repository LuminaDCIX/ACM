#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 200 + 5;
const int M = 5000 + 5;
const int MAXM = 5000 * 4 + 5;
const int MAXN = 200 * 2 + 5;
const int inf = 1e9;

int read() {
  int x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x;
} 

int n;
int m;
int S;
int T;

struct edge {
  edge *nxt;
  edge *r;
  int to;
  int cap;
};

edge e[MAXM];
edge *head[MAXN];
edge *cur[MAXN];
edge *ptr = e;

edge* make(int u, int v, int cap) {
  ptr->to = v;
  ptr->nxt = head[u];
  ptr->cap = cap;
  head[u] = ptr;
  return ptr++;
} 

edge* add(int u, int v, int cap) {
  edge *st = make(u, v, cap);
  edge *ts = make(v, u, 0);
  st->r = ts;
  ts->r = st;
  return st;
}

edge* pos[N];

vector <int> people;

int dist[MAXN];
bool vis[MAXN];

bool bfs() {
  memset(vis, 0, sizeof(vis));
  vis[S] = 1;
  queue <int> que;
  que.push(S);
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    for (edge *o = head[u]; o; o = o->nxt) {
      int v = o->to;
      if (!vis[v] && o->cap) {
        vis[v] = 1;
        dist[v] = dist[u] + 1;
        que.push(v);
      }
    }
  }
  return vis[T];         
} 

int dfs(int u, int f) {
  if (u == T || f == 0) {
    return f;
  }
  int sum = 0;
  for (edge *&o = cur[u]; o; o = o->nxt) {
    int v = o->to;
    int s = 0;
    if (dist[v] == dist[u] + 1 && o->cap && (s = dfs(v, min(f, o->cap))) > 0) {
      o->cap -= s;
      o->r->cap += s;
      sum += s;
      f -= s;
      if (!f) {
        break;
      }
    }
  }
  return sum; 
}

int dinic() {
  int ans = 0;
  while (bfs()) {
    for (int i = 0; i < MAXN; ++i) {
      cur[i] = head[i];
    }
    ans += dfs(S, inf);
  }
  return ans; 
}

bool solve() {
  int ans = dinic();
  if (ans >= inf) {
    return false;
  }
  for (int i = 0; i < n; ++i) {
    if (i == S || i == T) {
      continue;
    }
    for (edge *o = e; o < ptr; ++o, ++o) {
      o->cap = (o->cap + o->r->cap);
      o->r->cap = 0;
    }
    pos[i]->cap = 0;
    pos[i]->r->cap = 0;
    int now_ans = dinic();
    if (now_ans < ans) {
      ans = now_ans;
      people.push_back(i);
    } else {
      pos[i]->cap = 1;
      pos[i]->r->cap = 1;
    }
  }
  return true;
}

int main() {
  n = read();
  S = read() - 1;
  T = read() - 1; 
  for (int i = 0; i < n; ++i) {
    if (i != S && i != T) {
      pos[i] = add(i, i + 200, 1);
    }
    int u = (i == S || i == T) ? i : i + 200;
    for (int j = 0; j < n; ++j) {
      int o = read();
      if (i == j) {
        continue;
      }
      if (o == 1) {
        add(u, j, inf);
      }
    }
  }
  if (solve()) {
    int siz = (int) people.size();
    printf("%d\n", siz);
    for (int i = 0; i < siz; ++i) {
      printf("%d ", people[i] + 1);
    }
  } else {
    puts("NO ANSWER!");
  }
  return 0;
}