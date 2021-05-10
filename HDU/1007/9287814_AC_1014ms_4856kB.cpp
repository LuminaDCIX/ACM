#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;

const int maxn=100000;
pair<double,double> p[maxn+5],t[maxn+5];
int maxr=0;
double ans=0;
int n;

inline double dis(pair<double,double>  a,pair<double,double>  b)
{
  return sqrt(pow(a.first-b.first,2)+pow(a.second-b.second,2));
}

bool cmp(pair<double,double>  a,pair<double,double>  b) 
{
  return a.x==b.x?a.y<b.y:a.x<b.x;
}

bool cmpy(pair<double,double>  a,pair<double,double>  b)
{
  return a.y<b.y;
}

double solve(int l,int r)
{
  if (l==r) {
    return 1e10;
  }
  if (l+1==r) {
    return dis(p[l],p[r]);
  }
  int mid=(l+r)/2;
  double kmid=p[mid].x;
  double k=min(solve(l,mid),solve(mid,r));
  int top=0;
  for (int i=l;i<=r;++i) {
    if (p[i].x>=kmid-k&&p[i].x<=kmid+k) {
      t[++top]=p[i];
    }
  }
  sort(t+1,t+top+1,cmpy);
  for (int i=1;i<=top;++i) {
    for (int j=i+1;j<=top;++j) {
      k=min(k,dis(t[i],t[j]));
      if (t[j].y-t[i].y>k) {
        break;
      }
    }
  }
  return k;
}

int main()
{
  while (1) {
    scanf("%d",&n);
    if (!n) {
      break;  	
    }
    for (int i=1;i<=n;++i) {
      scanf("%lf%lf",&p[i].x,&p[i].y);
      maxr=max(maxr,(int)p[i].x);
    }
    sort(p+1,p+1+n,cmp);
    printf("%.2lf\n",solve(1,n)/2);
  }
  return 0;
}
