#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

const int N = 1e5 + 5;

struct node {
  node *fail;
  node *nxt[26];
  int tag;
} pool[N];

node* root = &pool[0];

inline node* newnode() {
  static node* ptr = &pool[0];
  return ++ptr;
}

inline void _insert(char str[])
{
  int len = strlen(str);
  node *now = root;
  for (int i = 0, x; i < len; ++i) {
    x = str[i] - 'a';
    if (now->nxt[x] == NULL) {
      now->nxt[x] = newnode();
    }
    now = now->nxt[x];
  }
  now->tag = len;
}

queue <node*> que;

inline void build()
{
  for (int i = 0; i < 26; ++i) {
    if (root->nxt[i]) {
      node *p = root->nxt[i];
      p->fail = root;
      que.push(p);
    } else {
      root->nxt[i] = root;
    }
  }
  while (!que.empty()) {
    node *p = que.front();
    que.pop();
    for (int i = 0; i < 26; ++i) {
      if (p->nxt[i] == NULL) {
	p->nxt[i] = p->fail->nxt[i];
	continue;
      }
      p->nxt[i]->fail = p->fail->nxt[i];
      que.push(p->nxt[i]);
    }
  }
}

stack <node*> stk;
stack <char> s;

void solve(char str[])
{
  int len = strlen(str);
  node *now = root;
  stk.push(root);
  for (int i = 0; i < len; ++i) {
    int x = str[i] - 'a';
    now = now->nxt[x];
    stk.push(now);
    s.push(str[i]);
    int k = now->tag;
    while (k--) {
      stk.pop();
      s.pop();
    }
    now = stk.top();
  }
  return;
}

char str[N];
char c[N];

int n;

int main()
{
  scanf("%s", str);
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%s", c);
    _insert(c);
  }
  build();
  solve(str);
  vector <char> ans;
  while (!s.empty()) {
    ans.push_back(s.top());
    s.pop();
  }
  reverse(ans.begin(), ans.end());
  for (int i = 0; i < (int) ans.size(); ++i) {
     putchar(ans[i]);
  }
  puts("");
  return 0;
}
