// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

inline int read() {
  int f = 1;
  int x = 0;
  char ch = getchar();
  for (; !isdigit(ch); ch = getchar()) {
    f = (ch == '-') ? -1 : 1;
  }
  for (; isdigit(ch); ch = getchar()) {
    x = x * 10 + ch - '0';
  }
  return f * x;
}

const int N = (int) 2e6 + 5;
    

class sam {
public:
  struct node {
    int fa;
    int len;
    int siz;
    int nxt[26];
  };

  int lst;
  int root;


  vector<node> tree;
  queue<int> pool;
  
  inline int& fa(const int &x) {
    return tree[x].fa;
  }
  inline int& siz(const int &x) {
    return tree[x].siz;
  }
  inline int& len(const int &x) {
    return tree[x].len;
  }
  inline int* nxt(const int &x) {
    return tree[x].nxt;
  }
  
  int newnode(int len) {
    if (pool.empty()) {
      int n = tree.size();
      tree.resize(n + 1024);
      for (int i = n; i < n + 1024; ++i) {
        pool.push(i);
      }
    }
    int k = pool.front();
    pool.pop();
    tree[k].len = len;
    return k; 
  }

  sam(int n) {
    tree.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
      pool.push(i);
    }
    root = newnode(0);
    lst = root;
  }

  void extend(int x) {
    int p = lst;
    int np = newnode(tree[p].len + 1);
    while (p && nxt(p)[x] == 0) {
      nxt(p)[x] = np;
      p = fa(p);
    }
    if (!p) {
      fa(np) = root;
    } else {
      int q = nxt(p)[x];
      if (len(q) == len(p) + 1) {
        fa(np) = q;
      } else {
        int nq = newnode(tree[p].len + 1);
        fa(nq) = fa(q);
        memcpy(nxt(nq), nxt(q), sizeof(int) * 26);
        fa(q) = nq;
        fa(np) = nq;
        while (p && nxt(p)[x] == q) {
          nxt(p)[x] = nq;
          p = fa(p);
        }
      }
    }
    lst = np;
    ++siz(lst);
  }

  int c[N];
  int f[N];
  
  long long solve() {
    int n = tree.size();
    for (int i = 1; i < n; ++i) {
      ++c[len(i)];
    }
    for (int i = 1; i < n; ++i) {
      c[i] += c[i - 1];
    }
    for (int i = 1; i < n; ++i) {
      f[c[len(i)]--] = i;
    }
    for (int i = n - 1; i >= 1; --i) {
      siz(fa(f[i])) += siz(f[i]);
    }
    long long ans = 0;
    for (int i = 1; i < n; ++i) {
      if (tree[i].siz != 1) {
        ans = max(ans, len(i) * (long long) siz(i));
      }
    }
    return ans;
  }
};

char s[N];

int main() {
  scanf("%s", s);
  int n = strlen(s);
  static sam m = sam(n << 1);
  for (int i = 0; i < n; ++i) {
    m.extend(s[i] - 'a');
  }
  long long ans = m.solve();
  cout << ans << endl;
  return 0;
}
