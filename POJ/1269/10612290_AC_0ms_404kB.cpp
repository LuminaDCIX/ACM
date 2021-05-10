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
};
struct vec {
	double x,y;
	vec (double _x,double _y) {x=_x, y=_y;}
};
struct segment {
	point a,b;
	segment(point _a=point(),point _b=point()) {a=_a, b=_b;}
};
vec operator - (point a,point b) {return vec(a.x-b.x,a.y-b.y);}
double operator * (vec a,vec b) {return a.x*b.y-a.y*b.x;}
point p0,p1,q0,q1;
int T;

int main() {
	puts("INTERSECTING LINES OUTPUT");
	T=read();
	while (T--) {
		p0.x=read(), p0.y=read(), p1.x=read(), p1.y=read();
		q0.x=read(), q0.y=read(), q1.x=read(), q1.y=read();
		if ((p0-p1)*(q0-q1)==0) {
			if ((p0-q1)*(p0-p1)==0) puts("LINE");
			else puts("NONE");
		}
		else {
			double lmd1=abs((q0-p1)*(q1-p1))*0.5;
			double lmd2=abs((q0-p0)*(q1-p0))*0.5;
			double x=(lmd2*p1.x+lmd1*p0.x)/(lmd1+lmd2);
			double y=(lmd2*p1.y+lmd1*p0.y)/(lmd1+lmd2);
			printf("POINT %.2f %.2f\n",x,y);
		}
	}
	puts("END OF OUTPUT");
	return 0;
}
