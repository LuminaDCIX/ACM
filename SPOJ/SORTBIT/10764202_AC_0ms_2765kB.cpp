#include <cstdio>
#include <cstring>
#include <algorithm>

#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)

using namespace std;

inline int read() {
  int f=1, x=0;
  char ch=getchar();
  while (ch<'0'||ch>'9') f=(ch=='-')?-1:1, ch=getchar();
  while (ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
  return f*x;
}

const int N=33;

int l, r, k;
int f[N][N];

int trs[N];
int tot;

inline int solve(int x,int s) {
  tot=0;
  int ret=0;
  while (x) trs[tot++]=x&1, x>>=1;
  per (i,0,tot) {
    if (trs[i]==1) ret+=f[i][s], --s;
    if (!s) break;
  }
  if (!s) ++ret;
  return ret;
}

inline int num_of(int l,int r,int k) {
  return solve(r,k)-solve(l-1,k);
}

inline int lowerbd(int low,int high,int cnt,int k) {
  int mid, ans=0;
  //  printf("%d\n",cnt);
  while (low<=high) {
    mid=low+high>>1;
    //    printf("%d %d %d %d\n",low,high,mid,num_of(l,mid,cnt));
    if (num_of(l,mid,cnt)<k) low=mid+1;
    else high=mid-1, ans=mid;
  }
  return ans;
}

int main() {
  f[0][0]=1;
  rep (i,1,N) {
    f[i][0]=1;
    rep (j,1,i+1) f[i][j]=f[i-1][j]+f[i-1][j-1];
  }
  int T=read();
  while (T--) {
    l=read(), r=read(), k=read();
    int flg=0;
    if (r==0) r=-1, --k;
    if (k==0) {
      puts("0"); continue;
    }
    if (l<0) swap(l,r), l=~l, r=~r, k=r-l+1-k+1, flg=1;
    if (l==0) --k, l=1;
    if (k==0) {
      puts(flg?"-1":"0");
      continue;
    }
    //  printf("%d %d %d\n",l,r,k);
    int cnt=1;
    int x;
    while (k-(x=num_of(l,r,cnt))>0) k-=x, ++cnt;
    printf("%d\n",flg?~lowerbd(l,r,cnt,k):lowerbd(l,r,cnt,k));
  }
  return 0;
}

