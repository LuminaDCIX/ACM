#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<iostream>

using namespace std;

const int maxn=200;
const int maxk=200;
const int inf=1000005;

int e[maxn+5][maxn+5];
int f[maxk+5][maxn+5][maxn+5];
int n,m,sx,sy,k;
int a[maxn+5],h,t;
int b[maxn+5];
int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1};
int ans=0;

struct seg
{
  int l,r,dir;
};
seg segs[maxk+5]; 

bool cmp(seg a,seg b)
{
  return a.l<b.l;
}

void update(int time,int x,int y,int k)
{
  if (e[x][y]) {
    f[k][x][y]=-inf;
    h=t=0;
    return;
  }
  while (h<t&&b[t-1]<=f[k-1][x][y]-time) {
    t--;
  }
  b[t]=f[k-1][x][y]-time;
  a[t++]=time;
  while (h<t&&time-a[h]>segs[k].r-segs[k].l+1) {
    h++;
  }
  f[k][x][y]=b[h]+time;
  ans=max(ans,f[k][x][y]);
  //printf("f[%d][%d][%d]=%d\n",k,x,y,f[k][x][y]);
  return;
}

int main()
{
  //freopen("t.in","r",stdin);
  scanf("%d%d%d%d%d",&n,&m,&sx,&sy,&k);
  for (int i=1;i<=n;++i) {
    while (getchar()!='\n');
    for (int j=1;j<=m;++j) {
      char c=getchar();
      if (c=='x') {
        e[i][j]=1;
      }
      f[0][i][j]=-inf;
    }
  }  
  for (int i=1;i<=k;++i) {
    scanf("%d%d%d",&segs[i].l,&segs[i].r,&segs[i].dir);
  }
  sort(segs+1,segs+1+k,cmp);
  f[0][sx][sy]=0;
  for (int i=1;i<=k;++i) {
    if (segs[i].dir==1) {
      for (int j=1;j<=m;++j) {
        h=t=0;
        for (int l=n;l>=1;--l) {
          update(n-l,l,j,i);  
        }
      }
    }
    if (segs[i].dir==2) {
     for (int j=1;j<=m;++j) {
      h=t=0;
      for (int l=1;l<=n;++l) {
        update(l,l,j,i);
      }
     }
    }
    if (segs[i].dir==3) {
      for (int j=1;j<=n;++j) {
        h=t=0;
        for (int l=m;l>=1;--l) {
          update(m-l,j,l,i);
        }
      }
    }
    if (segs[i].dir==4) {
      for (int j=1;j<=n;++j) {
        h=t=0;
        for (int l=1;l<=m;++l) {
          update(l,j,l,i);
        }
      }
    }
  }
  printf("%d\n",ans);
  return 0;
}