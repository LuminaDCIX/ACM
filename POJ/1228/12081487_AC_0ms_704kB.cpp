#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <cassert>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define FI first
#define SE second
#define PB push_back
#define MP make_pair
#define SIZ(x) ((int)x.size())
#define ALL(v) v.begin(),v.end()
#define REP(i,a,n) for (int i=(a);i<(n);++i)
#define PER(i,a,n) for (int i=(n)-1;i>=(a);--i)
#define FORG(i,x,e) for (int o=x;~o;o=e[o].nxt)
#define FOREACH(e,x) for (__typeof(x.begin()) e=x.begin();e!=x.end();++e)
typedef long long ll;
typedef double db;
typedef map<int,int> mii;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

int read() {
  int f=1,x=0;char ch=getchar();
  while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
  while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
  return f*x;
}


const int N=1000+5;
const db eps=1e-8;

struct pnt {
  db x,y;
  pnt(db _x=0,db _y=0):x(_x),y(_y) {};
} p[N];
pnt operator+(pnt a,pnt b) {return pnt(a.x+b.x,a.y+b.y);}
pnt operator-(pnt a,pnt b) {return pnt(a.x-b.x,a.y-b.y);}
db det(pnt a,pnt b) {return a.x*b.y-a.y*b.x;}
bool operator<(pnt a,pnt b) {return a.x==b.x?a.y<b.y:a.x<b.x;}
int sgn(db x) {
  if (fabs(x)<=eps) return 0;
  return x<0?-1:1;
}

pnt stk[N];

bool cvxhall(int n,pnt *p) {
  sort(p,p+n);
  int top=0;
  REP (i,0,n) {
    while (top>1&&sgn(det(stk[top-1]-stk[top-2],p[i]-stk[top-1]))<0) --top;
    stk[top++]=p[i];
  }
  int bot=top;

  PER (i,0,n-1) {
    while (top>bot&&sgn(det(stk[top-1]-stk[top-2],p[i]-stk[top-1]))<0) --top;
    stk[top++]=p[i];
  }

  int cnt=0;
  REP (l,0,top-1) {
    int r=l+2;
    if (r>=top) return false;
    while (r<top&&sgn(det(stk[r-1]-stk[r-2],stk[r]-stk[r-1]))==0) ++r;
    if (r-l<3) return false;
    l=r-2,++cnt;
  }
  return cnt>1;
}

int main() {
  int T=read();
  while (T--) {
    int n=read();
    REP (i,0,n) p[i].x=read(),p[i].y=read();
    puts(cvxhall(n,p)?"YES":"NO");
  }
  return 0;
}
