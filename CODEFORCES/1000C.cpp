#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

inline void add(int &a, int b) {
  a += b;
  if (a >= mod) {
    a -= mod;
  }
}
inline void sub(int &a, int b) {
  a -= b;
  if (a < 0) {
    a += mod;
  }
}
inline int mul(int a, int b) {
  return (long long) a * b % mod;
}
inline int modexp(int a, int x) {
  int res = 1;
  while (x) {
    if (x & 1) {
      res = mul(res, a);
    }
    a = mul(a, a);
    x >>= 1;
  }
  return res;
}

// struct edge {
//   int nxt;
//   int ver;
// };
// vector<edge> e;
// void add_edge(int u, int v) {
//   e.push_back((edge){head[u], v});
//   head[u] = (int) e.size() - 1;
// }

const int N = 12e5 + 5;

int n;
long long l[N];
long long r[N];
int sum[N];

long long cnt[N];
    

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  vector<long long> v;
  for (int i = 0; i < n; ++i) {
    cin >> l[i] >> r[i];
    v.push_back(l[i]);
    v.push_back(r[i]);
    v.push_back(l[i] + 1);
    v.push_back(l[i] - 1);
    v.push_back(r[i] + 1);
    v.push_back(r[i] - 1);
  }
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());

  int siz = v.size();
  map<long long, long long> id;
  map<long long, long long> pre;
  for (int i = 0; i < siz; ++i) {
    id[v[i]] = i;
    pre[i] = v[i];
  }

  for (int i = 0; i < n; ++i) {
    int ll = id[l[i]];
    int rr = id[r[i]];
    sum[ll]++;
    sum[rr + 1]--;
  }
  for (int i = 1; i < siz; ++i) {
    sum[i] += sum[i - 1];
  }

  for (int i = 0; i < siz - 1; ++i) {
    cnt[sum[i]] += pre[i + 1] - pre[i];
  }
  for (int i = 1; i <= n; ++i) {
    cout << cnt[i] << " ";
  }
  cout << endl;
  return 0;
}
