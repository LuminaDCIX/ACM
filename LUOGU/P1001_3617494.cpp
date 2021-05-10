#include <set>
#include <map>
#include <ctime>
#include <queue>
#include <stack>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

#define rep(i,a,n) for (int i=(a);i<n;++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)

inline int read()
{
  int f=1;
  int x=0;
  char ch=getchar();
  while (ch<'0'||ch>'9') {
    f=(ch=='-')?-1:1;
    ch=getchar();
  }
  while (ch>='0'&&ch<='9') {
    x=x*10+ch-'0';
    ch=getchar();
  }
  return f*x;
}

using namespace std;

int x;
int y;

int main()
{
  clock_t begin_time=clock();
  x=read();
  y=read();
  cout<<x+y;
  cerr<<endl;
  return 0;
}
