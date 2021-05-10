#include <bits/stdc++.h>

#define st first
#define nd second
#define make_pair com
#define sz(x) ((int)x.size())
#define mem(x, v) memset(x, v, sizeof(x))
#define exc(x, a, b) for (auto x = (a); x <  (b); ++x)
#define inc(x, a, b) for (auto x = (a); x <= (b); ++x)
#define cxe(x, a, b) for (auto x = (b) - 1; x >= (a); --x)
#define cni(x, a, b) for (auto x = (b)    ; x >= (a); --x)

using namespace std;

const int mod = (int) 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef double dbl;
typedef pair<int, int> mti;

inline void add(int &a, int b) { a + b >= mod ? a += b - mod : a += b; }
inline void sub(int &a, int b) { a - b < 0 ? a -= b - mod : a -= b; }
inline int mul(int a, int b) { return (long long) a * b % mod; }
inline int modexp(int a, int x) {
  int res = 1;
  for (; x; x >>= 1, a = mul(a, a)) {
    if (x & 1) res = mul(res, a);
  }
  return res;
}

template <typename T>
vector<T>& operator << (vector<T> &v, T x) { return v.push_back(x), v; }
//head;

const int N = 1e6 + 5;

int n;
int k;

int c[N];
int v[N];

long long mxc[N];
long long dp[N];
long long sum[N];

inline long long get(int l, int r) {
  return l == 0 ? sum[r] : sum[r] - sum[l - 1];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> k;
  exc (i, 0, n) cin >> c[i];
  exc (i, 0, n) {
    cin >> v[i];
  }

  sum[0] = v[0];
  exc (i, 1, n) sum[i] = sum[i - 1] + v[i];

  mem(dp, 0xcf);
  mem(mxc, 0xcf);
  dp[0] = 0;
  mxc[c[0]] = 0;
  exc (i, 1, n) {
    dp[i] = max(dp[i - 1], mxc[c[i]] + sum[i]);
    mxc[c[i]] = max(mxc[c[i]], dp[i - 1] - sum[i - 1]);
  }
  cout << dp[n - 1] << endl;
  return 0;
}