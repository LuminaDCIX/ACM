#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
typedef long long ll;
#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=a;--i)
using namespace std;
const int maxn=50;
const int base=200;
const int cut=10000;
const int cut_n=4;
struct bigint {
  int n,a[base+5];
  inline void clear() {
    n=0,memset(a,0,sizeof(a));
  }
  inline void creat(ll t) {
    clear();
    while (t) a[n++]=t%cut,t/=cut;
  }
  inline void print() {
    printf("%d",a[n-1]);
    per(i,0,n-1) printf("%.04d",a[i]);
    puts("");
  }
};
bigint operator - (const bigint &a,const bigint &b) {
  bigint ans; ans.clear();
  ans.n=max(a.n,b.n);
  rep(i,0,ans.n) {
    ans.a[i]+=a.a[i]-b.a[i];
    if (ans.a[i]<0) ans.a[i+1]-=1,ans.a[i]+=cut;
  }
  while (ans.n&&!ans.a[ans.n-1]) --ans.n;
  return ans;
}
bigint operator + (const bigint &a,const bigint &b) {
  bigint ans; ans.clear();
  ans.n=max(a.n,b.n);
  rep(i,0,ans.n) {
    ans.a[i]+=a.a[i]+b.a[i];
    ans.a[i+1]=ans.a[i]/cut;
    ans.a[i]%=cut;
  }
  while (ans.a[ans.n]) ++ans.n;
  return ans;
}
bigint operator * (const bigint &a,const bigint &b) {
  bigint ans; ans.clear();
  rep(i,0,a.n) rep(j,0,b.n) {
    ans.a[i+j]+=a.a[i]*b.a[j];
    ans.a[i+j+1]+=ans.a[i+j]/cut;
    ans.a[i+j]%=cut;
  }
  ans.n=a.n+b.n+1;
  while(ans.n&&!ans.a[ans.n-1]) --ans.n;
  return ans;
}
bigint fac2[maxn*maxn+5];
bigint f[maxn+5];
bigint C[maxn+5][maxn+5];
int main() {
  bigint a,b;
  a.creat(2ll),b.creat(1ll);
  rep(i,0,1251) fac2[i]=b,b=b*a;//b.print();
  f[1].creat(1ll);
  C[0][0].creat(1ll);
  rep(i,1,maxn+1) {
    C[0][i].creat(1ll);
    rep(j,1,i+1) C[j][i]=C[j-1][i-1]+C[j][i-1];//,C[j][i].print();
  }
  rep(i,2,51) {
    f[i]=fac2[(i*(i-1))>>1];
    rep(j,1,i) f[i]=f[i]-f[j]*C[j-1][i-1]*fac2[(i-j)*(i-j-1)/2];
  }
  int s;
  while (scanf("%d",&s)&&s!=0) {
    f[s].print();
  }
  return 0;
}