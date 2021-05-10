#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 200000 + 5;

int n;
int k;

char s[N];

int c[N];
int t0[N];
int t1[N];
int sa[N];

int rk[N];
int ht[N];

int n0;
int n1;

inline void build() {
  n = n0 + n1 + 1;
  int *x = t0;
  int *y = t1;
  int m = 256;
  s[n++] = 0;
  for (int i = 0; i < m; ++i) {
    c[i] = 0;
  }
  for (int i = 0; i < n; ++i) {
    x[i] = s[i];
    ++c[s[i]];
  }
  for (int i = 1; i < m; ++i) {
    c[i] += c[i - 1];
  }
  for (int i = n - 1; i >= 0; --i) {
    int t = --c[x[i]];
    sa[t] = i;
  }
  for (int k = 1; k <= n; k <<= 1) {
    int p = 0;
    for (int i = n - k; i < n; ++i) {
      y[p++] = i;
    }
    for (int i = 0; i < n; ++i) {
      if (sa[i] >= k) {
        y[p++] = sa[i] - k;
      }
    }
    for (int i = 0; i < m; ++i) {
      c[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
      ++c[x[y[i]]];
    }
    for (int i = 1; i < m; ++i) {
      c[i] += c[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
      int t = --c[x[y[i]]];
      sa[t] = y[i];
    }
    p = 1;
    swap(x, y);
    x[sa[0]] = 0;
    for (int i = 1; i < n; ++i) {
      if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) {
        x[sa[i]] = p - 1;
      } else {
        x[sa[i]] = p++;
      }
    }
    if (p >= n) {
      break;
    }
    m = p;
  }

  --n;
  for (int i = 0; i < n; ++i) {
    sa[i] = sa[i + 1];
  }
  for (int i = 0; i < n; ++i) {
    rk[sa[i]] = i;
  }
  int k = 0;
  for (int i = 0; i < n; ++i) {
    if (k) {
      --k;
    }
    if (rk[i] == 0) {
      k = 0;
      continue;
    }
    int j = sa[rk[i] - 1];
    while (s[i + k] == s[j + k]) {
      ++k;
    }
    ht[rk[i]] = k;
  }
}

int top;
pair <int, int>  stk[N];

inline long long calc(int l,int r) {
  // cerr<<l<<" "<<r<<endl;
  top=0;
  long long sum=0;
  long long ret=0;
  for (int i=l+1;i<=r;++i) {
    int h=ht[i];
    int num=0;
    while (top>0&&stk[top-1].first>=h) {
      int c=stk[top-1].second;
      sum-=(long long)(stk[top-1].first-k+1)*c;
      top--;
      num+=c;
    }
    if (sa[i-1]<n0) {
      stk[top++]=make_pair(h,num+1);
      sum+=(long long)(h-k+1)*(num+1);
    } else {
      if (num!=0) {
        stk[top++]=make_pair(h,num);
        sum+=(long long)(h-k+1)*(num);
      }
    }
    if (sa[i]>n0) {
      ret+=sum;
    }
  
  }
  top=0;
    sum=0;
    for (int i=l+1;i<=r;++i) {
      int h=ht[i];
    int num=0;
    while (top>0&&stk[top-1].first>=h) {
      int c=stk[top-1].second;
      sum-=(long long)(stk[top-1].first-k+1)*c;
      top--;
      num+=c;
    }
    if (sa[i-1]>n0) {
      stk[top++]=make_pair(h,num+1);
      sum+=(long long)(h-k+1)*(num+1);
    } else {
      if (num!=0) {
        stk[top++]=make_pair(h,num);
        sum+=(long long)(h-k+1)*(num);
      }
    }
    
    if (sa[i]<n0) {
      ret+=sum;
    }
  }
  return ret;
}

inline long long solve() {
  // for (int i = 0; i < n; ++i) {
  //   cerr << ht[i] << " ";
  // }
  // cerr << endl;
  long long ret = 0;
  for (int i=1;i<n;++i) {
    int l=i;
    int r=i;
    while (r+1<n&&ht[r+1]>=k) {
      ++r;
    }
    ret+=calc(l,r);
    i=r;
  }
  return ret;
}

int main() {
  while (scanf("%d", &k) && k){
    scanf("%s", s);
    n0 = strlen(s);
    s[n0] = '#';
    scanf("%s", s + n0 + 1);
    n1 = strlen(s + n0 + 1);
    // cerr << s << endl;
    // cerr << n0 << " " << n1 << endl;
    build();
    printf("%lld\n", solve());
  }
  return 0;
}
