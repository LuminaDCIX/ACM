#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)
#define rep(i,a,n) for (int i=(a);i<(n);++i)
typedef double db;

using namespace std;

const db eps=1e-7;
const int N=50000+5;

struct pnt {
  db x,y;
  pnt(db a=0,db b=0) {x=a,y=b;}
};
pnt operator-(pnt a,pnt b) {return pnt(a.x-b.x,a.y-b.y);}
pnt operator+(pnt a,pnt b) {return pnt(a.x+b.x,a.y+b.y);}
db det(pnt a,pnt b) {return a.x*b.y-a.y*b.x;}
db dot(pnt a,pnt b) {return a.x*b.x+a.y*b.y;}
db len(pnt a) {return sqrt(dot(a,a));}
int sgn(db x) {
  if (fabs(x)<eps) return 0;
  return x<0?-1:1;
}
bool operator==(pnt a,pnt b) {return sgn(a.x-b.x)==0&&sgn(a.y-b.y)==0;}

int n;

pnt p[N];

int top;
pnt stk[N];

bool cmp(pnt a,pnt b) {
  return sgn(a.x-b.x)==0?sgn(a.y-b.y)<0:sgn(a.x-b.x)<0;
}

void ch() {
  sort(p,p+n,cmp);
  rep (i,0,n) {
    while (top>1&&sgn(det(stk[top-1]-stk[top-2],p[i]-stk[top-1]))<=0) --top;
    stk[top++]=p[i];
  }
  int t=top;
  per (i,0,n-1) {
    while (top>t&&sgn(det(stk[top-1]-stk[top-2],p[i]-stk[top-1]))<=0) --top;
    stk[top++]=p[i];
  }
  --top,n=top;
  rep (i,0,n) p[i]=stk[i];
}

db ans=1e100;
pnt c[5];

int nxt(int x) {
  return x+1==n?0:x+1;
}

void prt(pnt x) {
  cerr<<x.x<<" "<<x.y<<" ";
}

void rc() {
  int q=1,x=0,y=1;
  // rep (i,0,n) cerr<<p[i].x<<" "<<p[i].y<<endl;
  // cerr<<endl;
  rep (i,0,n) {
    while (sgn(det(p[nxt(i)]-p[i],p[q]-p[i])-det(p[nxt(i)]-p[i],p[nxt(q)]-p[i]))<=0) {
      if (p[y]==p[q]) y=nxt(y);
      q=nxt(q);;
    }
    pnt it=p[nxt(i)]-p[i];
    pnt ii=pnt(-it.y,it.x),qq=pnt(it.y,-it.x);
    // prt(ii),prt(qq);
    while (sgn(det(ii,p[nxt(x)]-p[x]))<0) x=nxt(x);
    while (sgn(det(qq,p[nxt(y)]-p[y]))<0) y=nxt(y);
    // prt(p[i]),prt(p[x]),prt(p[y]),prt(p[q]);cerr<<endl;
    db t=fabs((det(p[q]-p[i],p[nxt(i)]-p[i])/len(p[nxt(i)]-p[i]))*(det(p[x]-p[y],ii)/len(ii)));
    if (t<ans) ans=t,c[0]=p[i],c[1]=p[x],c[2]=p[q],c[3]=p[y],c[4]=p[nxt(i)];
  }
}

pnt cross(pnt a,pnt b,pnt x,pnt y) {
  // prt(a),prt(b),prt(x),prt(y);
  db s1=det(y-x,a-x),s2=det(b-x,y-x),xx=(s1*b.x+s2*a.x)/(s1+s2);
  db yy=(s1*b.y+s2*a.y)/(s1+s2);
  return pnt(xx,yy);
}
pnt d[4];
int main() {
  scanf("%d",&n);
  rep (i,0,n) scanf("%lf%lf",&p[i].x,&p[i].y);
  ch(),rc();
  printf("%.5f\n",ans);
  int o=0;
  // prt(c[0]),cerr<<endl;
  pnt k=c[4]-c[0],kk=pnt(-k.y,k.x);
  d[0]=cross(c[0],c[0]+k,c[1],c[1]+kk);
  d[1]=cross(c[1],c[1]+kk,c[2],c[2]+k);
  d[2]=cross(c[2],c[2]+k,c[3],c[3]+kk);
  d[3]=cross(c[3],c[3]+kk,c[0],c[0]+k);
  rep (i,0,4) if (sgn(d[i].y-d[o].y)<0||(sgn(d[i].y-d[o].y)==0&&sgn(d[i].x-d[o].x)<0)) o=i;
  rep (i,0,4) printf("%.5f %.5f\n",d[o].x+eps,d[o].y+eps),o=(o+1)%4;
  return 0;
}
