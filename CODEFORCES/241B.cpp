#include <bits/stdc++.h>

using namespace std;

inline int read() {
  int f = 1;
  int x = 0;
  char ch = getchar();
  while (!isdigit(ch)) {
    f = (ch == '-') ? -1 : 1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return f * x;
}

const int N = 5e4 + 5;
const int P = 1e9 + 7;
const int MAX = N * 29 + 5;
const int LOG = 29;

inline int add(int a, int b) {
  return (a += b) >= P ? a - P : a;
}
inline int sub(int a, int b) {
  return (a -= b) < 0 ? a + P : a;
}
inline int mul(int a, int b) {
  return (long long) a * b % P;
}

int n;
long long m;

bool s[55];

struct trie {
  int nxt[MAX][2];
  int sum[MAX][LOG + 1];
  int siz[MAX];

  inline void ins(int x) {
    static int tot = 1;
    int nw = 1;
    for (int i = LOG; i >= 0; --i) {
      int to = !!(x & (1 << i));
      if (nxt[nw][to] == 0) {
        nxt[nw][to] = ++tot;
      }
      nw = nxt[nw][to];
    }
    siz[nw]++;
  }

  void init(int nw, int p) {
    if (nw == 0 || p == -1) {
      return;
    }
    int lc = nxt[nw][0];
    int rc = nxt[nw][1];
    init(lc, p - 1);
    init(rc, p - 1);
    siz[nw] += siz[lc] + siz[rc];
    for (int i = 0; i < p; ++i) {
      sum[nw][i] += sum[lc][i] + sum[rc][i];
    }
    sum[nw][p] = siz[lc];
  }

  long long count(int x, int y, int p, int tarbit) {
    if (siz[x] == 0  || siz[y] == 0) {
      return 0;
    }
    if (p == tarbit) {
      return (long long) siz[x] * siz[y];
    }
    if (s[p] == 1) {
      return count(nxt[x][0], nxt[y][1], p - 1, tarbit) + count(nxt[x][1], nxt[y][0], p - 1, tarbit);
    } else {
      return count(nxt[x][0], nxt[y][0], p - 1, tarbit) + count(nxt[x][1], nxt[y][1], p - 1, tarbit);
    }
  }

  long long calc(int x, int y, int p, int high, int tarbit) {
    if (siz[x] == 0 || siz[y] == 0) {
      return 0;
    }
    if (p == tarbit) {
      int ret = 0;
      ret = add(ret, mul(mul(siz[x], siz[y]), high));
      for (int i = tarbit; i >= 0; --i) {
        ret = add(ret, mul(mul(sum[x][i], siz[y] - sum[y][i]), 1 << i));
        ret = add(ret, mul(mul(siz[x] - sum[x][i], sum[y][i]), 1 << i));
      }
      return ret;
    }
    int ans = 0;
    if (s[p] == 1) {
      ans = calc(nxt[x][0], nxt[y][1], p - 1, high, tarbit);
        ans = add(ans, calc(nxt[x][1], nxt[y][0], p - 1, high, tarbit));
    } else {
      ans = calc(nxt[x][1], nxt[y][1], p - 1, high, tarbit);
      ans = add(ans, calc(nxt[x][0], nxt[y][0], p - 1, high, tarbit));
    }
    return ans;
  }
} t;


int main() {
  n = read();
  cin >> m;
  m *= 2;
  for (int i = 1; i <= n; ++i) {
    int x = read();
    t.ins(x);
  }
  t.init(1, LOG);
  int ans = 0;
  for (int i = LOG; i >= 0; --i) {
    s[i] = 1;
    long long cnt = t.count(1, 1, LOG, i - 1);
    if (cnt <= m) {
      int bit = 0;
      for (int j = 0; j <= LOG; ++j) {
        bit |= s[j] << j;
      }
      ans = add(ans, t.calc(1, 1, LOG, bit, i - 1));
      s[i] = 0;
      m -= cnt;
    }
  }
  int bit = 0;
  for (int i = 0; i <= LOG; ++i) {
    bit |= s[i] << i;
  }

  ans = add(ans, mul(m % P, bit % P));
  ans = mul(ans, (P + 1) / 2);
  cout << ans << endl;
  return 0;
}
