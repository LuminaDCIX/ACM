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

const int N=5000+5;
int n,m;
int x0,y0,x1,y1;
struct point {
	int x,y;
	point(int a=0,int b=0) {x=a, y=b;}
};
struct segment {
	point a,b;
	segment (point x=point(0,0),point y=point(0,0)) {a=x, b=y;}
};
struct vec {
	int x,y;
	vec(int a,int b) {x=a, y=b;}
};
vec operator - (point a,point b) {return vec(a.x-b.x,a.y-b.y);}
int operator * (vec a,vec b) {return a.x*b.y-a.y*b.x;}
segment s[N];
point p[N];
int cnt[N];
inline int lbd(point x) {
	int l=0,r=n;
	int ret=0;
	while (l<=r) {
		int mid=(l+r)>>1;
		//printf("%d\n",(s[mid].b-s[mid].a)*(x-s[mid].b));
		if ((s[mid].b-s[mid].a)*(x-s[mid].b)>=0) ret=mid, l=mid+1;
		else r=mid-1;
	}
	return ret;
}
int main() {
  while (true) {
		n=read(); if (!n) return 0;
		m=read();
		x0=read(), y1=read(), x1=read(), y0=read();
		memset(cnt,0,sizeof(cnt));
		int u,l;
		s[0]=segment(point(x0,y1),point(x0,y0));
		rep(i,1,n+1) u=read(), l=read(), s[i]=segment(point(u,y1),point(l,y0));
		rep(i,0,m) p[i].x=read(), p[i].y=read();
		//printf("%d\n",lbd(p[1]));
		rep(i,0,m) ++cnt[lbd(p[i])];
		rep(i,0,n+1) printf("%d: %d\n",i,cnt[i]); 
		puts("");
	}
	return 0;
}
