#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N=100000+25;
const int MAX=15;

int kase;

int k;
int n;

char s[N];

int c[N];
int t0[N];
int t1[N];
int sa[N];

int rk[N];
int ht[N];

int bel[N];

inline void build() {
  s[n++]=0;
  int *x=t0;
  int *y=t1;
  int m=256;
  for (int i=0;i<m;++i) {
    c[i]=0;
  }
  for (int i=0;i<n;++i) {
    x[i]=s[i];
    ++c[x[i]];
  }
  for (int i=1;i<m;++i) {
    c[i]+=c[i-1];
  }
  for (int i=0;i<n;++i) {
    int t=--c[x[i]];
    sa[t]=i;
  }
  for (int k=1;k<=n;k<<=1) {
    int p=0;
    for (int i=n-k;i<n;++i) {
      y[p++]=i;
    }
    for (int i=0;i<n;++i) {
      if (sa[i]>=k) {
        y[p++]=sa[i]-k;
      }
    }
    for (int i=0;i<m;++i) {
      c[i]=0;
    }
    for (int i=0;i<n;++i) {
      ++c[x[y[i]]];
    }
    for (int i=1;i<m;++i) {
      c[i]+=c[i-1];
    }
    for (int i=n-1;i>=0;--i) {
      int t=--c[x[y[i]]];
      sa[t]=y[i];
    }
    p=1;
    swap(x,y);
    x[sa[0]]=0;
    for (int i=1;i<n;++i) {
      if (y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]) {
        x[sa[i]]=p-1;
      } else {
        x[sa[i]]=p++;
      }
    }
    if (p>=n) {
      break;
    }
    m=p;
  }

  --n;
  for (int i=0;i<n;++i) {
    sa[i]=sa[i+1];
  }
  for (int i=0;i<n;++i) {
    rk[sa[i]]=i;
  }
  int k=0;
  for (int i=0;i<n;++i) {
    if (k) {
      --k;
    }
    if (rk[i]==0) {
      k=0;
      continue;
    }
    int j=sa[rk[i]-1];
    while (s[i+k]==s[j+k]) {
      ++k;
    }
    ht[rk[i]]=k;
  }
  return;
}

int mn[MAX];
int mx[MAX];

inline bool check(int l,int r,int x) {
  for (int i=0;i<k;++i) {
    mn[i]=0x3f3f3f3f;
    mx[i]=-1;
  }
  for (int i=l;i<=r;++i) {
    mn[bel[sa[i]]]=min(mn[bel[sa[i]]],sa[i]);
    mx[bel[sa[i]]]=max(mx[bel[sa[i]]],sa[i]);
  }
  for (int i=0;i<k;++i) {
    if (mx[i]==-1) {
      return false;
    }
    if (mx[i]-mn[i]<x) {
      return false;
    }
  }
  return true;
}

inline bool judge(int x) {
  for (int i=k;i<n;++i) {
    int l=i;
    int r=i;
    while (r+1<n&&ht[r+1]>=x) {
      ++r;
    }
    if (check(l,r,x)) {
      return true;
    }
    i=r;
  }
  return false;
}

inline int lowerbound(int lim) {
  int l=0;
  int r=lim/2;
  int ans=0;
  // cerr<<l<<" "<<r<<endl;
  while (l<=r) {
    int mid=l+r>>1;
    if (judge(mid)) {
      l=mid+1;
      ans=mid;
    } else {
      r=mid-1;
    }
  }
  return ans;
}

int main() {
  scanf("%d",&kase);
  while (kase--) {
    n=0;
    scanf("%d",&k);
    int lim=0x3f3f3f3f;
    for (int i=0;i<k;++i) {
      s[n++]='#';
      int l=n;
      scanf("%s",s+n);
      int len=strlen(s+n);
      lim=min(lim,len);
      int r=l+len-1;
      for (int j=l;j<=r;++j) {
        bel[j]=i;
      }
      n+=len;
    }
    // cerr<<n<<endl;
    // cerr<<s<<endl;
    build();
    // cerr<<"hi"<<endl;
    // for (int i=0;i<n;++i) {
    //   cerr<<bel[i]<<endl; 
    // }
    int k=lowerbound(lim);
    printf("%d\n",k);
  }
  return 0;
}
