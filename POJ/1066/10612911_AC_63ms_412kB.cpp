#include <cmath>
#include <stack>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define debug(x) cout
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size)
#define all(x) x.begin(),x.end()
#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)
#define y0 abcd
#define y1 dcba
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
inline ll read() {
  ll x=0, f=1; char ch=getchar();
  while (ch<'0'||ch>'9') f=(ch=='-')?-1:1, ch=getchar();
  while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+ch-'0', ch=getchar();
  return x*f;
}
inline void fileio() {
  freopen("t.in","r",stdin);
  //freopen("t.out","w",stdout);
}
//Produced By MiracleEEEE
//head

struct point {
	double x,y;
	point (double _x=0.0,double _y=0.0) {x=_x, y=_y;}
} p[105];
struct vec {
	double x,y;
	vec (double _x,double _y) {x=_x, y=_y;}
};
struct segment {
	point a,b;
	segment(point _a=point(),point _b=point()) {a=_a, b=_b;}
} s[105];
vec operator - (point a,point b) {return vec(a.x-b.x,a.y-b.y);}
double operator * (vec a,vec b) {return a.x*b.y-a.y*b.x;}
const double eps=1e-8;
int n;
int cnt;
inline bool judge(segment l1,segment l2) {
	return max(l1.a.x,l1.b.x)>=min(l2.a.x,l2.b.x)&&max(l1.a.y,l1.b.y)>=min(l2.a.y,l2.b.y);
}
inline bool cross(segment l1,segment l2) 
{
	if (!judge(l1,l2)||!judge(l2,l1)) return false;
	double bar1=((l2.b-l2.a)*(l1.b-l2.a))*((l2.b-l2.a)*(l1.a-l2.a));
	double bar2=((l1.b-l1.a)*(l2.b-l1.a))*((l1.b-l1.a)*(l2.a-l1.a));
	if (bar1<-eps&&bar2<-eps) return true;
	return false;
}

int main() {
	n=read();
	rep(i,0,n) scanf("%lf%lf%lf%lf",&s[i].a.x,&s[i].a.y,&s[i].b.x,&s[i].b.y);
	rep(i,0,n) p[cnt++]=s[i].a, p[cnt++]=s[i].b;
	scanf("%lf%lf",&p[cnt].x,&p[cnt].y);
	int ans=100;
	int sum;
	rep(i,0,cnt) {
		segment now=segment(p[i],p[cnt]);
		sum=0;
		rep(j,0,n) if (cross(now,s[j])) ++sum;
		ans=min(ans,sum);
	}
	printf("Number of doors = %d\n",n==0?1:ans+1);
	return 0;
}
