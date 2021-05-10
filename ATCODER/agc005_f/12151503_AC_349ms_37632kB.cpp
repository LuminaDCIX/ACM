#include <bits/stdc++.h>

using namespace std;

const int P = 924844033;
const int N = 200000 + 5;
const int MAX = 524288 + 5;

int n;

vector <int> G[N];
int siz[N];

int f1[MAX];
int f2[MAX];

int a[N];

int fac[N];
int inv[N];

void dfs(int u, int fa) {
  siz[u] = 1;
  for (int i = 0; i < (int) G[u].size(); ++i) {
    int v = G[u][i];
    if (v == fa) {
      continue;
    }
    dfs(v, u);
    --a[siz[v]];
    siz[u] += siz[v];
  }
  --a[n - siz[u]];
}

int lim;
int bit;

int rev(int x) {
  int ret = 0;
  for (int i = 0; i < bit; ++i) {
    ret <<= 1;
    ret |= x & 1;
    x >>= 1;
  }
  return ret;
}

int revbit[MAX];
int g[MAX];

void fft(int *f, int bit, int o) {
  for (int i = 0; i < lim; ++i) {
    if (revbit[i] > i) {
      swap(f[revbit[i]], f[i]);
    }
  }
  for (int i = 0; i < bit; ++i) {
    int len = 1 << i;
    for (int j = 0; j < lim; j += 1 << i + 1) {
      int wn = 0;
      for (int k = j; k < j + len; ++k) {
        int t = (long long) f[k + len] * g[wn] % P;
        f[k + len] = (f[k] - t) % P;
        if (f[k + len] < 0) {
          f[k + len] += P;
        }
        f[k] = (f[k] + t) % P;
        wn += o * (1 << bit - i - 1);                        
        if (wn < 0) {
          wn += lim;
        }
      }
    }
  }
}

int modexp(int a, int x, int P) {
  int ret = 1;
  while (x) {
    if (x & 1) {
      ret = (long long) ret * a % P;
    }
    a = (long long) a * a % P;
    x >>= 1;
  }
  return ret;
}

void calc() {
  while ((1 << bit) < n + n) {
    ++bit;   
  }
  lim = 1 << bit;
  for (int i = 0; i < lim; ++i) {
    revbit[i] = rev(i);
  }
  g[0] = 1;
  g[1] = modexp(5, (P - 1) / lim, P);
  for (int i = 2; i < lim; ++i) {
    g[i] = (long long) g[i - 1] * g[1] % P;
  }
  fft(f1, bit, 1);
  fft(f2, bit, 1);
  for (int i = 0; i < lim; ++i) {
    f1[i] = (long long) f1[i] * f2[i] % P;
  }
  fft(f1, bit, -1);
  int invlim = modexp(lim, P - 2, P);
  for (int i = 0; i < lim; ++i) {
    f1[i] = (long long) f1[i] * invlim % P;
  }    
}

int main() {
  scanf("%d", &n);
  for (int i = 0, u, v; i < n - 1; ++i) {
    scanf("%d %d", &u, &v);
    --v;
    --u;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  dfs(0, -1);
  a[n] = n;
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = (long long) fac[i - 1] * i % P;
  }
  inv[n] = modexp(fac[n], P - 2, P);
  for (int i = n - 1; i >= 0; --i) {
    inv[i] = (long long) inv[i + 1] * (i + 1) % P;
  }
  for (int i = 1; i <= n; ++i) {
    f1[n - i] = (long long) a[i] * fac[i] % P;
  }
  for (int i = 0; i <= n - 1; ++i) {
    f2[i] = inv[i];
  }
  calc();
  for (int i = n - 1; i >= 0; --i) {
    printf("%lld\n", (long long) f1[i] * inv[n - i] % P);
  }                  
  return 0;
}