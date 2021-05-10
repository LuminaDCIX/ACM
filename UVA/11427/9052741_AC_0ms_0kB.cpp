#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
double f[105][105];
int main()
{
  int T;
  int kase=0;
  scanf("%d",&T);
  while (T--) {
    int a,b,n;
    memset(f,0,sizeof(f));
    scanf("%d/%d%d",&a,&b,&n);
    double p=(double)a/b;
    f[0][0]=1.0; 
    for (int j=1;j<=n;++j)
      for (int i=0;i*b<=j*a;++i) {
        f[i][j]=(1-p)*f[i][j-1];
        if (i)
          f[i][j]+=p*f[i-1][j-1];
      }
    double Q = 0.0;
    for (int i=0; i*b<=n*a;++i)
      Q+=f[i][n];
    //printf("Q = %lf\n", Q);
    printf("Case #%d: %d\n", ++kase, (int)(1 / Q));
  }
  return 0;
}
