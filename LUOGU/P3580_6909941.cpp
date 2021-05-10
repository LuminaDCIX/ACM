// luogu-judger-enable-o2
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

const int N = 1000000 + 5;

int n, t[N];
multiset <long long> st;
long long f[N];

int main() {
  n = read();
  long long s = read();
  for (int i = 1; i <= n; ++i) {
    t[i] = read();
  }
  for (int i = 2; i <= n; ++i) {
    t[i] = max(t[i], t[i - 1] + 1);
  }
  memset(f, 0x3f3f, sizeof(f));
  f[0] = 0;
  int ptr = 0;
  for (int i = 1; i <= n; ++i) {
    while (ptr < n && f[ptr + 1] - (ptr + 1) - 1 <= t[i] - i) {
      ++ptr;
      st.erase(st.find(f[ptr] - 2 * ptr));
    }
    f[i] = t[i] + 2 * s + (i - ptr - 1);
    if (st.size()) {
      f[i] = min(f[i], *(st.begin()) + 2 * i  - 2 + 2 * s);
    }
    st.insert(f[i] - 2 * i);
  }
  cout << f[n] << endl;
  return 0;
}
