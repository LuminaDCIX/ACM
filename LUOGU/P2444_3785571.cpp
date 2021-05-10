#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 30000 + 5;

int n;

struct node {
  node *nxt[2];
  node* fail;
  int tag;
};

node pool[N];

node* root = &pool[0];

inline node* newnode() {
  static node* ptr = root;
  return ++ptr;
}

char str[N];

inline void ins(char str[]) {
  int len = strlen(str);
  node* now = root;
  for (int i = 0; i < len; ++i) {
    int x = str[i] - '0';
    if (now->nxt[x] == NULL) {
      now->nxt[x] = newnode();
    }
    now = now->nxt[x];
  }
  now->tag = 2;
}

int h;
int t;
node* que[N];


inline void build() {
  for (int i = 0; i < 2; ++i) {
    if (root->nxt[i]) {
      node* p = root->nxt[i];
      p->fail = root;
      que[t++] = p;
    } else {
      root->nxt[i] = root;
    }
  }
  while (h < t) {
    node* p = que[h++];
    for (int i = 0; i < 2; ++i) {
      if (p->nxt[i] == NULL) {
        p->nxt[i] = p->fail->nxt[i];
      } else {
        node* x = p->nxt[i];
        x->fail = p->fail->nxt[i];
        if (p->fail->nxt[i]->tag == 2) {
          x->tag = 2;
        }
        que[t++] = x;
      }
    }
  }
}


bool dfs(node *x) {
  if (x->tag == 1) {
    return true;
  }
  x->tag = 1;
  for (int i = 0; i < 2; ++i) {
    if (x->nxt[i]->tag == 2) {
      continue;
    }
    if (dfs(x->nxt[i])) {
      return true;
    }
  }
  x->tag = 0;
  x->tag = 2;
  return false;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%s", str);
    ins(str);
  }
  build();
  puts(dfs(root) ? "TAK" : "NIE");
  return 0;
}
