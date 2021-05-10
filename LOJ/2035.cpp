#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

inline int read() {
  int f = 1;
  int x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    f = (ch == '-') ? -1 : 1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return f * x;
}

const int N = 3000 + 5;

int n, m;

long long f[N][N];
long long sum[N];

long long sqr(long long x) {
  return x * x;
}

pair <int, int> stk[N];

inline long long update(int i, int j, int k) {
  return f[i - 1][k] + sqr(sum[j] - sum[k]);
}

int top;

int find_best(int i, int j) {
  int l = 1;
  int r = top;
  int k = 1;
  // cerr << top << endl;
  while (l <= r) {
    int x = (l + r) / 2;
    if (stk[x].first <= j) {
      k = x;
      l = x + 1;
    } else {
      r = x - 1;
    }
  }
  return stk[k].second;
}

int judge(int l, int f1, int f2, int i) {
  int r = n;
  int k = 0;
  while (l <= r) {
    int x = (l + r) / 2;
    if (update(i, x, f2) <= update(i, x, f1)) {
      k = x;
      r = x - 1;
    } else {
      l = x + 1;
    }
  }
  return k;
}

void push(int i, int j) {
  while (true) {
    if (top == 0) {
      stk[++top] = make_pair(j + 1, j);
      return;
    } else {
      int k = judge(max(stk[top].first, j + 1), stk[top].second, j, i);
      if (k == 0) {
	return;
      }
      if (stk[top].first == k) {
	--top;
      } else {
	stk[++top] = make_pair(k, j);
	return;
      }
    }
  }
}

int main() {
  n = read();
  m = read();
  for (int i = 1; i <= n; ++i) {
    sum[i] = read();
    sum[i] += sum[i - 1];
  }
  long long ans = -sqr(sum[n]);
  memset(f, 0x3f3f, sizeof(f));
  f[0][0] = 0;
  for (int i = 1; i <= m; ++i) {
    // for (int j = 1; j <= n; ++j) {
    //   int pos = -1;
    //   for (int k = 0; k < j; ++k) {
    // 	if (f[i][j] > f[i - 1][k] + sqr(sum[j] - sum[k])) {
    // 	  f[i][j] = min(f[i][j], f[i - 1][k] + sqr(sum[j] - sum[k]));
    // 	  pos = k;
    // 	}
    //   }
    //   cerr << pos << " ";
    // }
    // cerr << endl;
    top = 0;
    stk[++top] = make_pair(1, 0);
    for (int j = 1; j <= n; ++j) {
      // for (int k = 1; k <= top; ++k) {
      // 	cerr << '(' << stk[i].first << " " << stk[i].second  << ")" << endl;
      // }
      int k = find_best(i, j);
      f[i][j] = update(i, j, k);
      push(i, j);
      // cerr << i << " " << j << " " << f[i][j] << endl;
    }
  }
  ans += m * f[m][n];
  cout << ans << endl;
  return 0;
}