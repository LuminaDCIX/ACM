#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;

typedef long long LL;
const int N=510;
LL a[N],b[N],s[N];
int f[N][N],u[N][N],v[N][N];

int main()
{
    int n,m;
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
    scanf("%d",&m);
    for (int i=1;i<=m;i++) scanf("%lld",&b[i]);
    memset(f,0,sizeof(f));
    memset(u,0,sizeof(u));
    memset(v,0,sizeof(v));
    for (int i=1;i<=n;i++)
    {
     int p=0,q=0;
     for (int j=1;j<=m;j++)
     {
       f[i][j]=f[i-1][j];
       u[i][j]=u[i-1][j],v[i][j]=v[i-1][j];
       if (a[i]==b[j]) f[i][j]=f[p][q]+1,u[i][j]=p,v[i][j]=q;
       else if (a[i]>b[j] && f[i][j]>f[i][q]) p=i-1,q=j;
     }
    }
    int t=1,cnt=0;
    for (int j=2;j<=m;j++)
      if (f[n][j]>f[n][t]) t=j;
    printf("%d\n",f[n][t]);
    s[++cnt]=b[t];
    int x=n,y=t,xx,yy;
    while (f[x][y])
      s[++cnt]=b[y],xx=x,yy=y,x=u[xx][yy],y=v[xx][yy];
    for (int i=cnt;i>=1;i--) printf("%lld ",s[i]);
    return 0;
}