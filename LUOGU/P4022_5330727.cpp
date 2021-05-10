// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

const int N = 1100000 + 5;
const int MAX = N * 2 + 5;

struct SuffixAutomaton {
  int fa[N];
  int len[N];
  int nxt[N][2];
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
    int t = nxt[p][x];
    if (t && len[t] == len[p] + 1) {
      last = t;
      return;
    }
    int np = newnode(len[p] + 1);
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
  }
};

SuffixAutomaton s;

char str[N];

int mx[N];

int len;

void init(char *str, int nlen) {
  int (*nxt)[2] = s.nxt;
  int *fa = s.fa;
  int *len = s.len;
  int now = s.root;
  int nowlen = 0;
  for (int i = 0; i < nlen; ++i) {
    int x = str[i] - '0';
    while (now && nxt[now][x] == 0) {
      now = fa[now];
      nowlen = len[now];
    }
    if (!now) {
      now = s.root;
      mx[i] = i + 1;
      continue;
    } else {
      now = nxt[now][x];
      ++nowlen;
      mx[i] = i - nowlen + 1;
    }
  }
}

int val[N];
int pos[N];
int dp[N];

bool check(int L) {
  int h = 0;
  int t = 0;
  for (int i = 0; i < len; ++i) {
    int p = i - L;
    if (p >= 0) {
      int v = dp[p] - p;
      while (h < t && v >= val[t - 1]) {
        --t;
      }
      val[t] = v;
      pos[t++] = p;
    } else if (p == -1) {
      val[t] = 1;
      pos[t++] = -1;
    }
    while (h < t && pos[h] < mx[i] - 1) {
      ++h;
    }
    if (h != t) {
      dp[i] = i + val[h];
    } else {
      dp[i] = 0;
    }
    dp[i] = max(dp[i], dp[i - 1]);
  }
  // cerr << L << " : "; for (int i = 0; i < len; ++i) cerr << dp[i] << " "; cerr << endl;
  if (dp[len - 1] * 10 >= len * 9) {
    return true;
  } else {
    return false;
  }
}

int main() {
  int n;
  int m;
  scanf("%d %d", &n, &m);

  s.init();
  for (int i = 0; i < m; ++i) {
    scanf("%s", str);
    len = strlen(str);
    s.last = s.root;
    for (int j = 0; j < len; ++j) {
      s.extend(str[j] - '0');
    }
  }

  for (int i = 0; i < n; ++i) {
    scanf("%s", str);
    len = strlen(str);
    init(str, len);
    int ans = 0;
    int low = 1;
    int high = len;
    while (low <= high) {
      int mid = low + high >> 1;
      if (check(mid)) {
        ans = mid;
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
