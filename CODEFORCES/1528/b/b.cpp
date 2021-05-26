#include <bits/stdc++.h>

using namespace std;

std::string to_string(std::string s) { return '"' + s + '"'; }

std::string to_string(const char* s) { return to_string((std::string)s); }

std::string to_string(bool b) { return (b ? "true" : "false"); }

template <typename A, typename B>
std::string to_string(std::pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A>
std::string to_string(A v) {
  using ::to_string;
  using std::to_string;
  bool first = true;
  std::string res = "{";
  for (const auto& x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}

void debug_out() { std::cerr << std::endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  using ::to_string;
  using std::to_string;
  std::cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef LOCAL
#define debug(...)                                    \
  std::cerr << __FUNCTION__ << "(" << __LINE__ << ")" \
            << "[" << #__VA_ARGS__ << "]:",           \
      debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

const int mod = 998244353;

inline int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }

inline int sub(int a, int b) { return a - b < 0 ? a - b + mod : a - b; }

inline int mul(int a, int b) { return (int)((long long)a * b % mod); }

vector<int> euler_sieve(int n) {
  vector<int> is_prime(n + 1, 1);
  vector<int> prime;
  is_prime[1] = 0;

  vector<int> phi(n + 1);
  vector<int> mu(n + 1);
  vector<int> fsum_t(n + 1);
  vector<int> fsum(n + 1);
  vector<int> fcnt(n + 1);
  vector<int> minf(n + 1);
  vector<int> minf_cnt(n + 1);

  phi[1] = 1;
  mu[1] = 1;
  fsum_t[1] = 1;
  fsum[1] = 1;
  fcnt[1] = 1;
  minf[1] = -1;
  minf_cnt[1] = -1;

  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      prime.push_back(i);
      phi[i] = i - 1;
      mu[i] = -1;
      fsum_t[i] = fsum[i] = i + 1;
      fcnt[i] = 2;
      minf[i] = i;
      minf_cnt[i] = 1;
    }
    for (auto p : prime) {
      if ((long long)i * p > n) {
        break;
      }
      is_prime[i * p] = 0;
      minf[i * p] = p;
      if (i % p) {
        phi[i * p] = phi[i] * (p - 1);
        mu[i * p] = -mu[i];
        fsum[i * p] = fsum[i] * fsum[p];
        fsum_t[i * p] = 1 + p;
        minf_cnt[i * p] = 1;
        fcnt[i * p] = fcnt[i] * fcnt[p];
      } else {
        phi[i * p] = phi[i] * p;
        mu[i * p] = 0;
        fsum_t[i * p] = fsum_t[i] * p + 1;
        fsum[i * p] = fsum[i] / fsum_t[i] * fsum_t[i * p];
        minf_cnt[i * p] = minf_cnt[i] + 1;
        fcnt[i * p] = fcnt[i] / (minf_cnt[i] + 1) * (minf_cnt[i * p] + 1);
        break;
      }
    }
  }
  return fcnt;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> f(n + 1);
  vector<int> sum(n + 1);
  vector<int> fcnt = euler_sieve(n);
  f[1] = 1;
  sum[1] = 1;
  for (int i = 2; i <= n; ++i) {
    f[i] = add(fcnt[i], sum[i - 1]);
    sum[i] = add(sum[i - 1], f[i]);
  }
  cout << f[n] << endl;
  return 0;
}