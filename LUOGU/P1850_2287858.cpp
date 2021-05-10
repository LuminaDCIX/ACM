#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>

using namespace std;

const int maxv=300;
const int maxn=2000;
const double inf=10000000000.00;

double G[maxv+5][maxv+5];
int n,m,e,v;
int cla[maxn+5][2];
double p[maxn+5];
double f[maxn+5][maxn+5][2];
void init()
{
  for (int k=1;k<=v;++k) {
    for (int i=1;i<=v;++i) {
      for (int j=1;j<=v;++j) {
        G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
      }
    }
  }
  return;
}

int main()
{
  scanf("%d%d%d%d",&n,&m,&v,&e);
  for (int i=1;i<=v;++i) {
    for (int j=1;j<=v;++j) {
      G[i][j]=inf;
    }
  }
  for (int i=1;i<=v;++i) {
    G[i][i]=0.0;
  }
  for (int i=0;i<=1;++i) {
    for (int j=1;j<=n;++j) {
      scanf("%d",&cla[j][i]);
    }
  }
  for (int i=1;i<=n;++i) {
    scanf("%lf",&p[i]);
  }
  for (int i=1;i<=e;++i) {
    int f,t;
    int val;
    scanf("%d%d%d",&f,&t,&val);
    if (G[f][t]<val) {
      val=G[f][t];
    }
    G[f][t]=val;
    G[t][f]=val;
  }
  for (int i=0;i<=n;++i) {
    for (int j=0;j<=m;++j) {
      f[i][j][0]=inf;
      f[i][j][1]=inf;
    }
  } 
  init();
  f[1][0][0]=0.0;
  f[1][1][1]=0.0;
  for (int i=2;i<=n;++i) {
    f[i][0][0]=f[i-1][0][0]+G[cla[i-1][0]][cla[i][0]];
    for (int j=1;j<=min(m,i);++j) {
      f[i][j][0]=min(f[i-1][j][0]+G[cla[i-1][0]][cla[i][0]],f[i-1][j][1]+G[cla[i-1][0]][cla[i][0]]*(1.0-p[i-1])+G[cla[i-1][1]][cla[i][0]]*(p[i-1]));
      f[i][j][1]=min(f[i-1][j-1][0]+p[i]*G[cla[i-1][0]][cla[i][1]]+(1-p[i])*G[cla[i-1][0]][cla[i][0]],f[i-1][j-1][1]+p[i-1]*p[i]*G[cla[i-1][1]][cla[i][1]]
                 +p[i-1]*(1-p[i])*G[cla[i-1][1]][cla[i][0]]+(1-p[i-1])*p[i]*G[cla[i-1][0]][cla[i][1]]+(1-p[i])*(1-p[i-1])*G[cla[i-1][0]][cla[i][0]]);
    }
  }
  double ans=f[n][0][0];
  for (int i=1;i<=m;++i) {
    ans=min(min(f[n][i][0],f[n][i][1]),ans);
    //printf("%lf %lf\n",f[n][i][0],f[n][i][1]);
  }
  printf("%.2lf\n",ans);
  return 0;
}