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

const int N=100+5;
const double eps=1e-8;
int n,T;
struct point {
	double x,y;
	point(double _x=0,double _y=0) {x=_x, y=_y;}
};
struct vec {
	double x,y;
	vec(double _x=0,double _y=0) {x=_x, y=_y;}
};
struct segment {
	point a,b;
	segment(point _a=point(),point _b=point()) {a=_a, b=_b;}
} s[N];
vec operator - (point a,point b) {return vec(a.x-b.x,a.y-b.y);}
double operator * (vec a,vec b) {return a.x*b.y-a.y*b.x;}
inline bool same(point a,point b) {
	return fabs(a.x-b.x)<eps&&fabs(a.y-b.y)<eps;
}
inline bool judge(point x,point y) {
	if (same(x,y)) return false;
	rep(i,0,n) if ((((x-y)*(s[i].a-y))*((x-y)*(s[i].b-y)))>eps) 
		return false;
	return true;
}
int main()
{
	T=read();
	while (T--) {
		n=read();
		rep(i,0,n) scanf("%lf%lf%lf%lf",&s[i].a.x,&s[i].a.y,&s[i].b.x,&s[i].b.y);
		if (n==1) {
			puts("Yes!");
			goto end;
		}
		rep(i,0,n) rep(j,0,n) {
			if (judge(s[i].a,s[j].b)||judge(s[i].b,s[j].a)) {
				puts("Yes!");
				goto end;
			}
			if (judge(s[i].a,s[j].a)||judge(s[i].b,s[j].b)) {
				puts("Yes!");
				goto end;
			}
		}
		puts("No!");
	end:;
	}
	return 0;
}
	
