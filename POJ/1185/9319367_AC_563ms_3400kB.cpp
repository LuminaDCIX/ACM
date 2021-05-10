#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<cstdio>
#include<vector>

using namespace std;

const int maxn=100;
vector<int> v;
int f[maxn+5][maxn+5][maxn+5];
int n,m;
int a[maxn+5];

inline bool fit(int x,int y)
{
  return !(x&(y<<2))&&!(x&(y<<1))&&!(y&(x<<1))&&!(y&(x<<2));
}

void init()
{
  for (int s=0;s<(1<<m);++s) {
    if (fit(s,s)) {
      v.push_back(s);
    }
  }
  return;
}

inline int num(int x)
{
  int ret=0;
  while (x) {
    x-=x&-x;
    ret++;
  }
  return ret;
}

inline void print(int x)
{
  for (int i=1;i<=32;++i) {
    printf("%d",x<0);
    x<<=1;
  }
  puts("");
}

int main()
{
  scanf("%d%d",&n,&m);
  init();
  char l[13];
  for (int i=1;i<=n;++i) {
    scanf("%s",l);
    for (int j=0;l[j]!='\0';++j) {
      if (l[j]=='H') {
        a[i]+=1<<(j);
      }
    }
  }
  for (int i=0;i<v.size();++i) {
    if (!(a[1]&v[i])) {
      f[1][i][0]=max(f[1][i][0],num(v[i]));
    }
  }
  for (int i=0;i<v.size();++i) {
    for (int j=0;j<v.size();++j) {
      if ((!(a[2]&v[i]))&&(!(v[i]&v[j]))) {
        f[2][i][j]=max(f[2][i][j],f[1][j][0]+num(v[i]));
      }
    }
  }
  for (int k=3;k<=n;++k) {
    for (int i=0;i<v.size();++i) {
      for (int j=0;j<v.size();++j) {
        for (int p=0;p<v.size();++p) {
          if ((!(v[i]&a[k]))&&(!(v[i]&v[j]))&&(!(v[j]&v[p]))&&(!(v[i]&v[p]))&&(!(v[i]&v[p]))) {
            f[k][i][j]=max(f[k][i][j],f[k-1][j][p]+num(v[i]));  
          }
        }
      }
    }
  }
  int ans=0;
  for (int i=0;i<v.size();++i) {
    for (int j=0;j<v.size();++j) {
      ans=max(ans,f[n][i][j]);
    }
  }
  printf("%d\n",ans);
  return 0;
}