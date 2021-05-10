#include<cmath>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
inline int read()
{
  int f=0,s=1,ch;
  for(ch=getchar();!isdigit(ch);(ch=='-')?s=-1:s=1,ch=getchar());
  for(;isdigit(ch);f=(f<<1)+(f<<3)+ch-'0',ch=getchar());
  return f*s;
}
typedef long long ll;
long long phi(long long x)
{ 
  long long ret=x;
  for (int i=2;i*i<=x;++i) {
    if (x%i==0) {
      while (x%i==0) {
        x/=i;
      }
      ret-=ret/i;
    }
  }
  if (x>1) {
    ret-=ret/x;
  }
  return ret;
}
int main()
{
  long long x;
  while (~scanf("%lld",&x)) {
    printf("%lld\n",phi(x-1));
  }
  return 0;
}