#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)
typedef double db;

struct pnt {
  int x,y;
  pnt(int a=0,int b=0) {x=a,y=b;}
};
pnt operator-(pnt a,pnt b) {return pnt(a.x-b.x,a.y-b.y);}
pnt operator+(pnt a,pnt b) {return pnt(a.x+b.x,a.y+b.y);}
int det(pnt a,pnt b) {return a.x*b.y-a.y*b.x;}
int len(pnt a) {return a.x*a.x+a.y*a.y;}

const int N=50000+5;

int read() {
  int f=1,x=0;char ch=getchar();
  while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
  while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
  return f*x;
}

int n;

int top;
pnt stk[N];
pnt p[N];

bool cmp(pnt a,pnt b) {
  return a.x==b.x?a.y<b.y:a.x<b.x;
}
void convex_hall() {
  sort(p,p+n,cmp);
  rep (i,0,n) {
    while (top>1&&det(stk[top-1]-stk[top-2],p[i]-stk[top-1])<=0) --top;
    stk[top++]=p[i];
  }
  int t=top;
  per (i,0,n-1) {
    while (top>t&&det(stk[top-1]-stk[top-2],p[i]-stk[top-1])<=0) --top;
    stk[top++]=p[i];
  }
  --top;
}

int rotating_caliper() {
  int j=1;
  int ans=0;
  stk[top]=stk[0];
  rep (i,0,top) {
    while (det(stk[i+1]-stk[i],stk[j]-stk[i])<det(stk[i+1]-stk[i],stk[j+1]-stk[i])) j=(j+1==top)?0:j+1;
    ans=max(ans,max(len(stk[i]-stk[j]),len(stk[i+1]-stk[j])));
  }
  return ans;
}

int main() {
  n=read();
  rep (i,0,n) p[i].x=read(),p[i].y=read();
  convex_hall();
  printf("%d\n",rotating_caliper());
  return 0;
}
