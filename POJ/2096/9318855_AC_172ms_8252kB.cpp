#include<cstdio>
#include<algorithm>
#include<cstdlib>

using namespace std;

const int maxn=1000;

int n,s;
double f[maxn+5][maxn+5];
int main()
{
  scanf("%d%d",&n,&s);
  for (int i=n;i>=0;--i) {
    for (int j=s;j>=0;--j) {
      if (i!=n||j!=s) {
        f[i][j]=(1.00*(n-i)*(s-j)*(f[i+1][j+1]+1)+1.00*i*(s-j)*(f[i][j+1]+1)+1.00*(n-i)*j*(f[i+1][j]+1)+1.00*i*j)/(n*s-i*j);
      }
      //printf("%d %d %lf\n",i,j,f[i][j]);
    }
  }
  printf("%.4f\n",f[0][0]);
  return 0;
}