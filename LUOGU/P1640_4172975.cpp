#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1000000 + 5;

inline int read() {
  int x;
  scanf("%d", &x);
  return x;
}

int n;

int fa[N];
bool vis[N];

int get(int x) {
  return fa[x] == x ? x : fa[x] = get(fa[x]);
}

int main() {
  n = read();
  for (int i = 0; i < N; ++i) {
    fa[i] = i;
  }
  for (int i = 0; i < n; ++i) {
    int a = read();
    int b = read();
    int fx = get(a);
    int fy = get(b);    
    if (fx == fy) {
      vis[fx] = 1;
    } else {
      if (fx > fy) {
        swap(fx, fy);
      }
      if (vis[fx]) {
        vis[fy] = 1;
      }
      fa[fx] = fy;
      vis[fx] = 1;
    }
  }
  for (int i = 1; i <= N; ++i) {
    if (!vis[i]) {
      printf("%d\n", i - 1);
      return 0;
    }
  }
  return 0;
}
