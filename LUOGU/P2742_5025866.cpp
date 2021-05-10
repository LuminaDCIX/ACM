#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef double db;
#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)

const int N=10000+5;

int n;

struct pnt {
  db x,y;
  pnt(db a=0,db b=0) {x=a,y=b;}
} p[N];
bool operator<(const pnt&a,const pnt&b) {return a.x==b.x?a.y<b.y:a.x<b.x;}
pnt operator-(const pnt&a,const pnt&b) {return pnt(a.x-b.x,a.y-b.y);}

int top;
pnt stk[N];

bool check(pnt a,pnt b) {return a.x*b.y-a.y*b.x<=0;}

void convex_hall() {
  sort(p,p+n);
  rep (i,0,n)  {
    while (top>1&&check(stk[top-1]-stk[top-2],p[i]-stk[top-1])) --top;
    stk[top++]=p[i];
  }
  int t=top;
  per (i,0,n-1) {
    while (top>t&&check(stk[top-1]-stk[top-2],p[i]-stk[top-1])) --top;
    stk[top++]=p[i];
  }
  --top;
}

db len(pnt a) {return sqrt(a.x*a.x+a.y*a.y);}

int main() {
  scanf("%d",&n);
  rep (i,0,n) scanf("%lf%lf",&p[i].x,&p[i].y);
  convex_hall();
  db ans=0;
  rep (i,0,top-1) ans+=len(stk[i+1]-stk[i]);
  ans+=len(stk[top-1]-stk[0]);
  printf("%.2f\n",ans);
  return 0;
}
