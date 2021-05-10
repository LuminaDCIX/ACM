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

int n;

vector <int> p, r, b;
set <int> s;

inline long long calc(vector <int> v, int l, int r) {
  long long ans = 0;
  if (v.size() == 0) {
    return 0;
  }
  if (v[0] <= l) {
    ans += l - v[0];
  }
  if (v.back() >= r) {
    ans += v.back() - r;
  }
  return ans;
}

int main() {
  n = read();
  for (int i = 1; i <= n; ++i) {
    int x = read();
    char l = getchar();
    if (l == 'R') {
      r.push_back(x);
    } else if (l == 'P') {
      p.push_back(x);
    } else {
      b.push_back(x);
    }
  }
  sort(r.begin(), r.end());
  sort(p.begin(), p.end());
  sort(b.begin(), b.end());
  if (p.size() == 0) {
    long long ans = 0;
    for (int i = 1; i < (int) r.size(); ++i) {
      ans += r[i] - r[i - 1];
    }
    for (int i = 1; i < (int) b.size(); ++i) {
      ans += b[i] - b[i - 1];
    }
    cout << ans << endl;
    return 0;
  }
  long long ans = 0;
  long long mn = p[0];
  long long mx = p.back();
  ans += calc(b, mn, mx);
  ans += calc(r, mn, mx);
  int bptr = 0;
  int rptr = 0;
  while (bptr < b.size() && b[bptr] <= mn) {
    ++bptr;
  }
  while (rptr < r.size() && r[rptr] <= mn) {
    ++rptr;
  }
  for (int i = 0; i < (int) p.size() - 1; ++i) {
    int ll = p[i];
    int rr = p[i + 1];
    int Bl = bptr;
    while (bptr < b.size() && b[bptr] <= rr) {
      ++bptr;
    }
    int Br = bptr - 1;
    int Rl = rptr;
    while (rptr < r.size() && r[rptr] <= rr) {
      ++rptr;
    }
    int Rr = rptr - 1;
    long long nw = (rr - ll) * 2ll;
    long long nw2 = rr - ll;
    long long add = 1e18;
    if (Bl <= Br) {
      add = min(b[Br] - ll, rr - b[Bl]);
      for (int j = Bl; j < Br; ++j) {
        add = min(add, (long long) rr - b[j + 1] + b[j] - ll);
      }
    } else {
      add = 0;
    }
    nw2 += add;
    add = 1e18;
    if (Rl <= Rr) {
      add = min(r[Rr] - ll, rr - r[Rl]);
      for (int j = Rl; j < Rr; ++j) {
        add = min(add, (long long) rr - r[j + 1] + r[j] - ll);
      }
    } else {
      add = 0;
    }
    nw2 += add;
    ans += min(nw2, nw);
  }
  cout << ans << endl;
  return 0;
}
