#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 100 + 5;
const int NODE = N * N * N * 2;
const int mod = 19260817;
 
int n;
int tot;
int a[N];
 
int val[NODE];
int nxt[NODE];
int key[NODE];
 
int head1[mod];
int head2[mod];
 
void insert(int *head, int k) {
  int t = k;
  k %= mod;
  if (k < 0) {
    k += mod;
  }
  for (int o = head[k]; o; o = nxt[o]) {
    if (key[o] == t) {
      ++val[o];
      return;
    }
  }
  nxt[tot] = head[k];
  key[tot] = t;
  val[tot] = 1;
  head[k] = tot++;
}
 
 
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
 
int main() {
  n = read();
  for (int i = 0; i < n; ++i) {
    a[i] = read();
  }
  ++tot;
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        insert(head1, a[i] * a[j] + a[k]);
        if (a[i] != 0) {
          insert(head2, a[i] * (a[j] + a[k]));
        }
      }
    }
  }
  for (int i = 0; i < mod; ++i) {
    if (head1[i] == -1) {
      continue;
    }
    for (int o = head1[i]; o; o = nxt[o]) {
      int t = key[o] % mod;
      if (t < 0) {
        t += mod;
      }
      for (int o2 = head2[t]; o2; o2 = nxt[o2]) {
        if (key[o2] == key[o]) {
          ans += (long long) val[o2] * val[o];
        }
      }
    }
  }
  cout << ans << endl;
  return 0;
} 