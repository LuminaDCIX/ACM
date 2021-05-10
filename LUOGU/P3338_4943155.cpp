#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define rep(i,a,n) for (int i=(a);i<(n);++i)

const int N=400000+5;
const double pi=acos(-1.0);

double read() {
  double x;scanf("%lf",&x);return x;
}

int n;

int bit,lim;

double q[N];

struct complx {
  double x,y;

  complx(double a=0,double b=0) {
    x=a,y=b;
  }
};
complx operator + (const complx &a,const complx &b) {return complx(a.x+b.x,a.y+b.y);}
complx operator - (const complx &a,const complx &b) {return complx(a.x-b.x,a.y-b.y);}
complx operator * (const complx &a,const complx &b) {return complx(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}

complx f1[N],f2[N],w[N];

int rev[N];

void fft(complx f[],int bit,int o) {
  rep (i,0,lim) if (rev[i]>i) swap(f[rev[i]],f[i]);

  rep (i,0,bit) for (int j=0;j<lim;j+=1<<i+1) {
    int wn=0,len=1<<i;
    rep (k,j,j+len) {
      complx t=w[wn]*f[k+len];
      f[k+len]=f[k]-t;
      f[k]=f[k]+t;
      wn+=o*(1<<bit-i-1);
      if (wn<0) wn+=lim;
    }
  }
}

void calc() {
  rep (i,0,lim) f1[i]=complx(q[i],0);
  memset(f2,0,sizeof(f2));
  f2[0]=complx(0,0);
  for (double i=1;i<n;i+=1) f2[(int)i]=complx(1/i/i,0);

  fft(f1,bit,1);
  fft(f2,bit,1);
  rep (i,0,lim) f1[i]=f1[i]*f2[i];
  fft(f1,bit,-1);
  rep (i,0,lim) f1[i].x/=lim;
}

int revbit (int x) {
  int ret=0;
  rep (i,0,bit) ret<<=1,ret|=x&1,x>>=1;
  return ret;
}

double ans[N];

int main() {
  n=read();
  rep (i,0,n) q[i]=read();
  
  while ((1<<bit)<n*2) ++bit;
  lim=1<<bit;
  
  w[0].x=1;
  w[1]=complx(cos(2*pi/lim),sin(2*pi/lim));

  rep (i,2,lim) w[i]=w[i-1]*w[1];
  rep (i,0,lim) rev[i]=revbit(i);
  calc();
  rep (i,0,n) ans[i]+=f1[i].x;
  reverse(q,q+n),calc();
  rep (i,0,n) ans[n-i-1]-=f1[i].x;
  rep (i,0,n) printf("%.3f\n",ans[i]);
  return 0;
}
