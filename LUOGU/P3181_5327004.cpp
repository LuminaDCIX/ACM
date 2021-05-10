// luogu-judger-enable-o2
#include <cstdio>
#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 200000 + 5;
const int NODE = 200000 * 4 + 5;
const int ALPHA = 26;

struct SuffixAutomaton {
  int fa[NODE];
  int siz[NODE][2];
  int nxt[NODE][ALPHA];
  int len[NODE];
  int tot;
  int root;
  int last;

  void init() {
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
    if (nxt[p][x] != 0 && len[nxt[p][x]] == len[p] + 1) {
      last = nxt[p][x];
      return;
    }
    int np = newnode(len[p] + 1);
    while (p && nxt[p][x] == 0) {
      nxt[p][x] = np;
      p = fa[p];
    }
    if (p == 0) {
      fa[np] = root;
    } else {
      int q = nxt[p][x];
      if (len[p] + 1 == len[q]) {
        fa[np] = q;
      } else {
        int nq = newnode(len[p] + 1);
        memcpy(nxt[nq], nxt[q], sizeof(nxt[q]));
        fa[nq] = fa[q];
        fa[q] = nq;
        fa[np] = nq;
        while (~p && nxt[p][x] == q) {
          nxt[p][x] = nq;
          p = fa[p];
        }
      }
    }
    last = np;
  }
};

SuffixAutomaton s;

char a[N];
char b[N];
int na;
int nb;

long long ans;

int c[N];
int que[NODE];

void solve() {
  int *fa = s.fa;
  int (*siz)[2] = s.siz;
  int *len = s.len;
  int (*nxt)[26] = s.nxt;
  int tot = s.tot;
  for (int i = 1; i < tot; ++i) {
    ++c[len[i]];
  }
  int mxlen = max(na, nb);
  for (int i = 1; i <= mxlen; ++i) {
    c[i] += c[i - 1];
  }
  for (int i = 1; i < tot; ++i) {
    int t = --c[len[i]];
    que[t] = i;
  }
  for (int i = tot - 1; i >= 1; --i) {
    int x = que[i];
    siz[fa[x]][0] += siz[x][0];
    siz[fa[x]][1] += siz[x][1];
  }
  for (int i = 1; i < tot; ++i) {
    ans += (long long) siz[i][0] * siz[i][1] * (len[i] - len[fa[i]]);
  }
}

int main() {                            
  s.init();
  scanf("%s %s", a, b);
  na = strlen(a);
  nb = strlen(b);
  for (int i = 0; i < na; ++i) {
    s.extend(a[i] - 'a');
    ++(s.siz[s.last][0]);
  }
  s.last = s.root;
  for (int i = 0; i < nb; ++i) {
    s.extend(b[i] - 'a');
    ++(s.siz[s.last][1]);
  }   
  solve();
  printf("%lld\n", ans);
  return 0;
}