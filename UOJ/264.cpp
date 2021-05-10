#include <set>
#include <map>
#include <stack>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
 
using namespace std;

inline int read()
{
  int x = 0;
  int f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    f = (ch == '-') ? -1 : 1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * f;
}

const int N = 1e5 + 5;
const int M = 7 * 1e6 + 5;
const int inf = 0x7fffffff;

struct queue {
  int head;
  int tail;
  int s[M];

  inline int front() {
    if (head == tail) {
      return -inf;
    }
    return s[head];
  }
  
  inline bool empty() {
    return head == tail;
  }

  inline void push(int x) {
    s[tail++] = x;
  }

  inline void pop() {
    ++head;
  }
} q[3];

int a[N];           
int cut[M];

int n, m;
int u, v;
int p, t;

int main() {
  n = read();
  m = read();
  p = read();
  u = read();
  v = read();
  t = read();
  for (int i = 0; i < n; ++i) {
    a[i] = read();
  }
  sort(a, a + n);
  for (int i = n - 1; i >= 0; --i) {
    q[0].push(a[i]);
  }
  for (int i = 0; i < m; ++i) {
    int mx = -inf;
    int id = 0;
    
    for (int j = 0; j < 3; ++j) {
      if (mx < q[j].front()) {
        mx = q[j].front();
        id = j;
      }
    }

    q[id].pop();
    int c = mx + i * p;
    cut[i] = c;
    c = 1ll * c * u / v;

    q[1].push(c - (i + 1) * p);
    q[2].push(mx - c - p);
  }
  int cnt = 0;
  for (int i = 0; i < m; ++i) {
    if ((i + 1) % t == 0) {
      if (cnt) {
      	putchar(' ');
      }
      cnt = 1;
      printf("%d", cut[i]);
    }
  }
  puts("");
  int time = 0;
  cnt = 0;
  while (!q[0].empty() || !q[1].empty() || !q[2].empty()) {
    int mx = -inf;
    int id = 0;
    for (int i = 0; i < 3; ++i) {
      if (mx < q[i].front()) {
        id = i;
        mx = q[i].front();
      }
    }
    q[id].pop();
    ++time; 
    if (time % t == 0) {
      if (cnt) {
      	putchar(' ');
      }
      cnt = 1;
      printf("%d", mx + m * p);
    }
  }
  return 0;
}


