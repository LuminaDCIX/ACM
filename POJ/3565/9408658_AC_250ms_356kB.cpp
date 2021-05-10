#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<vector>

using namespace std;

const int maxn=200;
const double inf=2e11;
int n;
double w[maxn+5][maxn+5];
double lx[maxn+5],ly[maxn+5];
bool visx[maxn+5],visy[maxn+5];
double temp,eps=1e-5;
int link[maxn+5];
double slack[maxn+5];
struct node
{
  double x,y;
}
l[maxn+5],r[maxn+5];
inline double dist(node a,node b)
{
  return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));  
}
#define Abs(t) ((t)<0?-(t):(t))
bool dfs(int x)
{
  visx[x]=1;
  for(int y=0;y<n;++y){
    if(!visy[y]){
      if(Abs(lx[x]+ly[y]-w[x][y])<eps){
        visy[y]=1;
        if(link[y]==-1||dfs(link[y])){
          link[y]=x;
          return 1;
        }
      }
      else{
        slack[y]=min(slack[y],lx[x]+ly[y]-w[x][y]);
      }
    }
  }
  return 0;
}

int main()
{
  scanf("%d",&n);
  for(int i=0;i<n;++i){
    scanf("%lf%lf",&r[i].x,&r[i].y);
  }
  for(int i=0;i<n;++i){
    scanf("%lf%lf",&l[i].x,&l[i].y);
  }
  for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
      w[i][j]=-dist(l[i],r[j]);
    }
  }

  memset(link,-1,sizeof(link));
  memset(ly,0,sizeof(ly));
  for(int i=0;i<n;++i){
    lx[i]=-inf;
  }
  for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
      lx[i]=max(lx[i],w[i][j]);
    }
  }
  for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
      slack[j]=inf;
    }
    while(true){
      memset(visx,0,sizeof(visx));
      memset(visy,0,sizeof(visy));
      if(dfs(i)){
        break;
      }     
      double t=inf;
      for(int j=0;j<n;++j){
        if(!visy[j]&&t>slack[j]){
          t=slack[j];
        }
      }
      for(int j=0;j<n;++j){
        if(visx[j]){
          lx[j]-=t;
        }
        if(visy[j]){
          ly[j]+=t;
        }
        else{
          slack[j]-=t;
        }
      }
    }
  }
  for(int i=0;i<n;++i){
    printf("%d\n",link[i]+1);
  }
  return 0;
}