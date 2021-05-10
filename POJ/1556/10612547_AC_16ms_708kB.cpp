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
point p0,p1,q0,q1;
int n,cnt,top;
int id[105],head[105],tot;
double dis[105];
struct edge {
	int nxt,to;
	double val;
} e[10005];
inline void add(int u,int v,double val) {
	e[tot].to=v, e[tot].nxt=head[u], e[tot].val=val, head[u]=tot++;
}
inline bool judge(segment l1,segment l2) {
	return max(l1.a.x,l1.b.x)>=min(l2.a.x,l2.b.x)&&max(l1.a.y,l1.b.y)>=min(l2.a.y,l2.b.y);
}
inline bool onseg(point a,segment l) {
	return a.x>=min(l.a.x,l.b.x)&&a.x<=max(l.a.x,l.b.x)&&a.y>=min(l.a.y,l.b.y)
		&&a.y<=max(l.a.y,l.b.y)&&(a-l.a)*(l.b-l.a)==0;
}
inline bool cross(segment l1,segment l2)
{
	if (!judge(l1,l2)||!judge(l2,l1)) return false;
	double bar1=((l2.b-l2.a)*(l1.b-l2.a))*((l2.b-l2.a)*(l1.a-l2.b));
	double bar2=((l1.b-l1.a)*(l2.b-l1.a))*((l1.b-l1.a)*(l2.a-l1.b));
	if (bar1<0&&bar2<0) return true;
	//if (bar1==0||bar2==0) {
	//	if (onseg(l1.a,l2)||onseg(l1.b,l2)||onseg(l2.a,l1)||onseg(l2.b,l1)) return true;
	//}
	return false;
}
inline double dist(point a,point b) {
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
void build() {
	tot=0;
	memset(head,-1,sizeof(head));
	rep(i,0,cnt) rep(j,0,cnt) if (i!=j) {
		segment now=segment(p[i],p[j]);
		bool flg=1;
		rep(k,0,top) if (cross(now,s[k])) {
			flg=0; break;
		}
		if (flg) add(i,j,dist(p[i],p[j])), add(j,i,dist(p[i],p[j]));/* printf("%d %d\n",i,j);*/
	}
}
inline double run() {
	rep(i,0,cnt) dis[i]=1e9;
	dis[0]=0;
	queue<int> que;
	que.push(0);
	while (!que.empty()) {
		int u=que.front();
		que.pop();
		for (int i=head[u];~i;i=e[i].nxt) {
			int v=e[i].to;
			if (dis[v]>dis[u]+e[i].val) {
				dis[v]=dis[u]+e[i].val;
				que.push(v);
			}
		}
	}
	return dis[1];
}
int main() {
	//fileio();
	while (scanf("%d",&n)&&n!=-1) {
		cnt=0;
		top=0;
		p[cnt++]=point(0,5);
		p[cnt++]=point(10,5);
		double x,y[4];
		rep(i,0,n) {
			scanf("%lf",&x);
			rep(i,0,4) scanf("%lf",&y[i]);
			rep(i,0,4) p[cnt++]=point(x,y[i]);
			s[top++]=segment(point(x,0),point(x,y[0]));
			s[top++]=segment(point(x,y[1]),point(x,y[2]));
			s[top++]=segment(point(x,y[3]),point(x,10));
		}
		build();
		printf("%.2f\n",run());
	}
	return 0;
}
