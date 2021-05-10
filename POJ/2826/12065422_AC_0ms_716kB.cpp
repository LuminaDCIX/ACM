#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define siz(x) ((int)x.size())
#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)
#define foreach(e,x) for (__typeof(x.begin()) e=x.begin();e!=x.end();++e)
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

// head

const db eps=1e-8;

struct pnt {
  db x,y;
  pnt(db _x=0,db _y=0):x(_x),y(_y){}
};
pnt operator+(pnt a,pnt b) {return pnt(a.x+b.x,a.y+b.y);}
pnt operator-(pnt a,pnt b) {return pnt(a.x-b.x,a.y-b.y);}
db det(pnt a,pnt b) {return a.x*b.y-a.y*b.x;}
db dot(pnt a,pnt b) {return a.x*b.x+a.y*b.y;}
db len(pnt a) {return sqrt(dot(a,a));}
int sgn(db x) {
  if (fabs(x)<eps) return 0;
  return x<0?-1:1;
}
bool operator==(pnt a,pnt b) {
  return sgn(a.x-b.x)==0&&sgn(a.y-b.y)==0;
}

pnt a[2];
pnt b[2];

bool cross(pnt a,pnt b,pnt c,pnt d) {
  db x=det(c-a,b-a)*det(d-a,b-a);
  db y=det(a-c,d-c)*det(b-c,d-c);
  return sgn(x)<=0&&sgn(y)<=0;
}

bool level(pnt a,pnt b) {return sgn(a.y-b.y)==0;}

pnt p;

bool check_null() {
  if (!cross(a[0],a[1],b[0],b[1])) return 1;
  if (level(a[0],a[1])||level(b[0],b[1])) return 1;
  if (sgn(det(a[0]-b[1],a[1]-b[1]))==0&&sgn(det(a[0]-b[0],a[1]-b[0]))==0) return 1;
  pnt k=pnt(p.x,p.y+100);
  pnt m=k-p;
  if (sgn(a[0].y-b[0].y)>=0) {
    if (sgn(det(m,a[0]-p))<=0&&sgn(det(a[0]-p,b[0]-p))<=0&&sgn(b[0].x-a[0].x)<=0) return 1;
    if (sgn(det(m,a[0]-p))>=0&&sgn(det(a[0]-p,b[0]-p))>=0&&sgn(b[0].x-a[0].x)>=0) return 1;
  } else {
    if (sgn(det(m,b[0]-p))<=0&&sgn(det(b[0]-p,a[0]-p))<=0&&sgn(a[0].x-b[0].x)<=0) return 1;
    if (sgn(det(m,b[0]-p))>=0&&sgn(det(b[0]-p,a[0]-p))>=0&&sgn(a[0].x-b[0].x)>=0) return 1;
  }
  return 0;
}

pnt insc(pnt a,pnt b,pnt x,pnt y) {
  db s1=det(b-a,x-a),s2=det(y-a,b-a);
  return pnt((s1*y.x+s2*x.x)/(s1+s2),(s1*y.y+s2*x.y)/(s1+s2));
}

int T;

int main() {
  T=read();
  while (T--) {
    rep (i,0,2) a[i].x=read(),a[i].y=read();
    rep (i,0,2) b[i].x=read(),b[i].y=read();

    if (sgn(b[0].y-b[1].y)<0) swap(b[0],b[1]);
    if (sgn(a[0].y-a[1].y)<0) swap(a[0],a[1]);

    p=insc(a[0],a[1],b[0],b[1]);

    if (check_null()) puts("0.00");
    else {
      db ans=0;
      if (sgn(a[0].y-b[0].y)<0) {
        pnt y=insc(a[0],pnt(rand(),a[0].y),b[0],b[1]);
        ans=fabs(0.5*det(a[0]-p,y-p));
      } else {
        pnt y=insc(b[0],pnt(rand(),b[0].y),a[0],a[1]);
        ans=fabs(0.5*det(b[0]-p,y-p));
      }
      printf("%.2f\n",ans+eps);
    }
  }
  return 0;
}
