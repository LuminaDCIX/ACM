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

const int N = 150000 + 5;

long long a[N];
map <long long, int> cnt;
set <long long> s;

map <long long, set <int> > ocr;

int main() {
  int n = read();
  for (int i = 1; i <= n; ++i) {
    a[i] = read();
  }
  for (int i = 1; i <= n; ++i) {
    ++cnt[a[i]];
    ocr[a[i]].insert(i);
    if (cnt[a[i]] >= 2) {
      s.insert(a[i]);
    }
  }
  int k = 0;
  while (!s.empty()) {
    long long x = *s.begin();
    s.erase(x);
    int fi = *ocr[x].begin();
    ocr[x].erase(fi);
    int se = *ocr[x].begin();
    ocr[x].erase(se);
    a[fi] = 0;
    a[se] += x;
    ocr[a[se]].insert(se);
    --cnt[x];
    --cnt[x];
    ++cnt[a[se]];
    if (cnt[a[se]] >= 2) {
      s.insert(a[se]);
    }
    if (cnt[x] >= 2) {
      s.insert(x);
    }
  }
  
  for (int i = 1; i <= n; ++i) {
    if (a[i]) {
      ++k;
    }
  }
  cout << k << endl;
  
  for (int i = 1; i <= n; ++i) {
    if (a[i]) {
      printf("%lld ", a[i]);
    }
  }
  puts("");
  return 0;
}

