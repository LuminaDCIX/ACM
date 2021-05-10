#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

#define pb push_back
#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)
typedef double db;

using namespace std;

const int N=100+5;
const db eps=1e-8;

struct pnt {
  db x,y;
  pnt(db _x=0,db _y=0):x(_x),y(_y) {};
};
pnt operator+(pnt a,pnt b) {return pnt(a.x+b.x,a.y+b.y);}
pnt operator-(pnt a,pnt b) {return pnt(a.x-b.x,a.y-b.y);}
pnt operator/(pnt a,db b) {return pnt(a.x/b,a.y/b);}
pnt operator*(pnt a,db b) {return pnt(a.x*b,a.y*b);}
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

int n,r;
pnt a[N];

struct hpl {
  pnt x,y;
  db ang;
  void init(pnt a,pnt b) {
    x=a,y=b;
    ang=atan2(b.y-a.y,b.x-a.x);
  }
};
bool operator<(hpl a,hpl b) {
  int d=sgn(a.ang-b.ang);
  if (d==0) return sgn(det(a.y-a.x,b.y-a.x))<=0;
  else return d<=0;
}
hpl g[N];

int h,t;
hpl que[N];

pnt insc(pnt a,pnt b,pnt x,pnt y) {
  db s1=det(b-a,x-a),s2=det(y-a,b-a);
  return pnt((s1*y.x+s2*x.x)/(s1+s2),(s1*y.y+s2*x.y)/(s1+s2));
}

bool judge(hpl a,hpl b, hpl x) {
  pnt c=insc(a.x,a.y,b.x,b.y);
  // cerr<<c.x<<" "<<c.y<<endl;
  return sgn(det(x.y-x.x,c-x.x))<0;
}

pnt p[N];

void hpcross() {
  sort(g,g+n);
  vector<hpl> v;
  v.pb(g[0]);
  rep (i,1,n) {
    int d=sgn(g[i].ang-g[i-1].ang);
    if (d==0) continue;
    v.pb(g[i]);
  }
  int sz=(int)v.size();
  rep (i,0,sz) g[i]=v[i];
  que[t++]=g[0];
  que[t++]=g[1];
  rep (i,2,n) {
    while (h<t-1&&judge(que[t-1],que[t-2],g[i])) --t;
    while (h<t-1&&judge(que[h],que[h+1],g[i])) ++h;
    que[t++]=g[i];
  }

  while (h<t-1&&judge(que[t-1],que[t-2],que[h])) --t;
  n=0;
  que[t]=que[h];
  rep (i,h,t) p[n++]=insc(que[i].x,que[i].y,que[i+1].x,que[i+1].y);
}

int nxt(int x) {return (x+1==n)?0:x+1;}

pnt o;
bool cmp(pnt a,pnt b) {
  if (a==o) return 1;
  if (b==o) return 0;
  db k=det(a-o,b-o);
  if (sgn(k)==0) return len(a-o)<len(b-o);
  else return k>0;
}

void solve() {
  o=p[0];
  sort(p,p+n,cmp);
  vector<pnt> v;
  v.pb(p[0]);
  rep (i,1,n) {
    if (p[i]==p[i-1]) continue;
    v.pb(p[i]);
  }
  n=v.size();
  rep (i,0,n) p[i]=v[i];

  if (n==1) {
    printf("%.5f %.5f %.5f %.5f\n",p[0].x,p[0].y,p[0].x,p[0].y);
    return;
  }
  if (n==2) {
    printf("%.5f %.5f %.5f %.5f\n",p[0].x,p[0].y,p[1].x,p[1].y);
    return;
  }
  db ans=0;
  int q=1;
  pnt l0,l1;
  rep (i,0,n) {
    pnt x=p[nxt(i)]-p[i];
    while (sgn(det(x,p[nxt(q)]-p[i])-det(x,p[q]-p[i]))>=0) q=nxt(q);
    db d=len(p[q]-p[i]);
    if (d>ans) ans=d,l0=p[i],l1=p[q];
    d=len(p[q]-p[nxt(i)]);
    if (d>ans) ans=d,l0=p[nxt(i)],l1=p[q];
  }

  printf("%.5f %.5f %.5f %.5f\n",l0.x,l0.y,l1.x,l1.y);
}

int main() {
  scanf("%d%d",&n,&r);
  rep (i,0,n) scanf("%lf%lf",&a[i].x,&a[i].y);

  reverse(a,a+n);
  a[n]=a[0];
  rep (i,0,n) {
    pnt x=a[i],y=a[i+1],c=y-x,d=pnt(-c.y,c.x);
    db k=len(d);
    d.x/=k,d.y/=k;
    g[i].init(x+d*r,y+d*r);
  }

  hpcross();
  solve();
  return 0;
}
