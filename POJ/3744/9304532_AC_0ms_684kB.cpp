#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<cmath>

using namespace std;

const int maxn=100000000;

int id[15];
double turn[2][2];
double t[2][2],o[2][2];
double now[2][2];
int n;
double p;

void mul(double mat1[][2],double mat2[][2])
{
  memset(t,0,sizeof(t));
  for (int k=0;k<=1;++k) {
    for (int i=0;i<=1;++i) {
      for (int j=0;j<=1;++j) {
        t[i][j]+=mat1[i][k]*mat2[k][j];
      }
    }
  }
  return;
}

void powmod(double mat1[][2],int x)
{
  memset(o,0,sizeof(o));
  o[0][0]=o[1][1]=1.0;
  double mat[2][2];
  memcpy(mat,mat1,sizeof(double)*4);
  while (x) {
    if (x&1) {
      mul(o,mat);
      memcpy(o,t,sizeof(double)*4);
    }
    mul(mat,mat);
    memcpy(mat,t,sizeof(double)*4);
    x>>=1;
  }
  return;
}

void solve()
{
  turn[0][0]=p;
  turn[1][0]=1-p;
  turn[0][1]=1.0;
  now[0][1]=1.0;
  sort(id+1,id+n+1);
  id[0]=1;
  for (int i=n;i>=1;--i) {
    now[0][0]=0.0;
    powmod(turn,id[i]-id[i-1]);
    mul(now,o);
    memcpy(now,t,sizeof(double)*4);
  }
  printf("%.7f\n",now[0][0]);
  return;
}

int main()
{
  while (scanf("%d",&n)!=EOF) {
    scanf("%lf",&p);
    for (int i=1;i<=n;++i) {
      scanf("%d",&id[i]);
    }
    solve();
  }
  return 0;
}