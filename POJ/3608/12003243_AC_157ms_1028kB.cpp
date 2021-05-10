#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define rep(i,a,n) for (int i=(a);i<(n);++i)

typedef double db;

const int N=10000+5;
const db eps=1e-10;

int n;
int m;

struct pnt {
  db x,y;
  pnt(db a=0,db b=0) {x=a,y=b;}
};
pnt operator-(pnt a,pnt b) {return pnt(a.x-b.x,a.y-b.y);}
pnt operator+(pnt a,pnt b) {return pnt(a.x+b.x,a.y+b.y);}
db det(pnt a,pnt b) {return a.x*b.y-a.y*b.x;}
db dot(pnt a,pnt b) {return a.x*b.x+a.y*b.y;}
db len(pnt a) {return sqrt(a.x*a.x+a.y*a.y);}
int sgn(db x) {
  if (abs(x)<eps) return 0;
  return x<0?-1:1;
}
bool operator==(pnt a,pnt b) {return sgn(a.x-b.x)==0&&sgn(a.y-b.y)==0;}

pnt a[N],b[N];

db dis(pnt x,pnt y,pnt a) {
  if (x==y) return len(a-x);
  pnt v1=a-x,v2=a-y,v3=y-x;
  if (sgn(dot(v2,v3))>0) return len(v2);
  else if (sgn(dot(v1,v3))<0) return len(v1);
  else return fabs(det(v2,v3)/len(v3));
}

db rc(pnt *a,pnt *b,int n,int m) {
  db ans=1e99;
  int p=0,q=0;
  rep (i,1,n) if (sgn(a[i].y-a[p].y)<0) p=i;
  rep (i,1,m) if (sgn(b[i].y-b[q].y)>0) q=i;
  a[n]=a[0];
  b[m]=b[0];
  rep (i,0,n) {
    while (sgn(det(a[p+1]-a[p],b[q+1]-b[q]))<0) q=(q+1==m)?0:q+1;
    db t=det(a[p+1]-a[p],b[q+1]-b[q]);
    if (sgn(t)==0) {
      ans=min(ans,min(dis(a[p],a[p+1],b[q]),dis(a[p],a[p+1],b[q+1])));
      ans=min(ans,min(dis(b[q],b[q+1],a[p]),dis(b[q],b[q+1],a[p+1])));
    } else ans=min(ans,dis(a[p],a[p+1],b[q]));
    p=(p+1==n)?0:p+1;
  }
  return ans;
}

pnt o;

bool cmp(const pnt&a,const pnt&b) { //a<b
  if (a==o) return 1;
  if (b==o) return 0;
  db d=det(a-o,b-o);
  if (sgn(d)!=0) return d<0;
  else return sgn(len(a-o)-len(b-o))<0;
}

void init(pnt *p,int n) {
  o=p[0];
  rep (i,1,n) {
    if (p[i].x==o.x&&p[i].y<o.y) o=p[i];
    if (p[i].x<o.x) o=p[i];
  }
  sort(p,p+n,cmp);
}

int main() {
  while (scanf("%d%d",&n,&m)&&n+m) {
    rep (i,0,n) scanf("%lf%lf",&a[i].x,&a[i].y);
    rep (i,0,m) scanf("%lf%lf",&b[i].x,&b[i].y);
    init(a,n);
    init(b,m);
    // rep (i,0,n) cerr<<a[i].x<<" "<<a[i].y<<endl;
    // rep (i,0,m) cerr<<b[i].x<<" "<<b[i].y<<endl;

    printf("%.5f\n",min(rc(a,b,n,m),rc(b,a,m,n)));
  }
  return 0;
}
