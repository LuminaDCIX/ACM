#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int MAX = 2e5 + 5;
const int P = 1e9 + 7;

struct SuffixAutomaton {
  int siz[MAX];
  int len[MAX];
  int fa[MAX];
  int nxt[MAX][26];
  int tot;
  int root;
  int last;
  long long a;
  long long b;

  int init() {
    tot = 2;
    root = 1;
    last = 1;
  }
  
  int newnode(int x) {
    len[tot] = x;
    return tot++;
  }

  void extend(int x) {
    int p = last;
    int np = newnode(len[p] + 1);
    int add = len[p];
    while (p && nxt[p][x] == 0) {
      nxt[p][x] = np;
      p = fa[p];
    }
    if (!p) {
      fa[np] = root;
    } else {
      int q = nxt[p][x];
      if (len[q] == len[p] + 1) {
        fa[np] = q;
      } else {
        int nq = newnode(len[p] + 1);
        siz[nq] = siz[q];
        memcpy(nxt[nq], nxt[q], sizeof(nxt[q]));
        fa[nq] = fa[q];
        fa[q] = nq;
        fa[np] = nq;
        while (p && nxt[p][x] == q) {
          nxt[p][x] = nq;
          p = fa[p];
        }
      }
    }
    last = np;
    p = np;
    while (p) {
      a = (a + (len[p] - len[fa[p]]) * siz[p]) % P;
      b = (b + (len[p] - len[fa[p]]) * siz[p] * add) % P;
      ++siz[p];
      p = fa[p];
    }
  }
};

SuffixAutomaton s;

char str[N];

int main() {
  int n;
  scanf("%d", &n);
  scanf("%s", str);
  s.init();
  for (int i = 0; i < n; ++i) {
    s.extend(str[i] - 'a');
    // cerr << s.a << " " << s.b << endl;
    printf("%lld\n", ((s.a * (i + 1) % P - s.b) + P) % P);
  }
  return 0;
}
