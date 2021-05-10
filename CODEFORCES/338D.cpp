#include <bits/stdc++.h>

using namespace std;

const int N = 10000 + 5;

long long n;
long long m;
long long a[N];

inline long long gcd(long long a, long long b) {
  return !b ? a : gcd(b, a % b);
}
inline long long lcm(long long a, long long b) {
  return a / gcd(a, b) * b;
}
template <typename T>
inline T exgcd(T a, T b, T &x, T &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  T d = exgcd(b, a % b, y, x);
  y -= (a / b) * x;
  return d;
}

inline long long modmul(long long a, long long b, long long mod) {
  return (a * b - (long long) ((long double) a / mod * b) * mod + mod) % mod;
}

template <typename T>
inline bool diophantine(T a, T b, T c, T &x, T &y, T &g) {
  if (a == 0 && b == 0) {
    if (c == 0) {
      x = y = g = 0;
      return true;
    }
    return false;
  }
  if (a == 0) {
    if (c % b == 0) {
      x = 0;
      y = c / b;
      g = abs(b);
      return true;
    }
    return false;
  }
  if (b == 0) {
    if (c % a == 0) {
      x = c / a;
      y = 0;
      g = abs(a);
      return true;
    }
    return false;
  }

  if (b < 0) {
    a = -a;
    b = -b;
    c = -c;
  }
    
  g = exgcd(a, b, x, y);
  if (c % g != 0) {
    return false;
  }

  a /= g;
  b /= g;
  T d = c / g;
  
  // T t =  x * d / b;
  // x = x * d + t * b;
  // y = y * d - t * a;
  
  x = modmul(x, d, b);
  return true;
}

bool crt(long long k1, long long m1, long long k2, long long m2, long long &k, long long &m) {
  k1 %= m1;
  if (k1 < 0) {
    k1 += m1;
  }
  k2 %= m2;
  if (k2 < 0) {
    k2 += m2;
  }
  long long x;
  long long y;
  long long g;
  if (!diophantine(m1, -m2, k2 - k1, x, y, g)) {
    return false;
  }
  m = m1 / gcd(m1, m2) * m2;
  k = (k1 + modmul(m1, x, m)) % m;
  return true;
}

int main() {
  int cnt;
  long long p;
  cin >> n >> p >> cnt;
  long long c = 1;
  for (int i = 1; i <= cnt; ++i) {
    cin >> a[i];
    c = lcm(c, a[i]);
    if (c > n) {
      puts("NO");
      exit(0);
    }
  }
  long long k = a[1];
  long long m = a[1];
  for (int i = 2; i <= cnt; ++i) {
    long long k1 = 1 - i;
    long long m1 = a[i];
    if (!crt(k, m, k1, m1, k, m)) {
      puts("NO");
      exit(0);
    }
  }
  if (k == 0) {
    k += c;
  }
  if (k + cnt - 1 > p) {
    puts("NO");
    exit(0);
  }
  for (long long i = k; i < k + cnt; ++i) {
    if (gcd(i, c) != a[i - k + 1]) {
      puts("NO");
      exit(0);
    }
  }
  puts("YES"); 
  return 0;
}
