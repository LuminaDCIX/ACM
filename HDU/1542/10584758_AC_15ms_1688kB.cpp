#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <map>
#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)
#define root (&pool[0])
using namespace std;
const int L=100000+5;
const int N=100+5;
int top;
map<double,int> id;
struct seg {
	double l,r;
	double x;
	int f;
	seg(double a=0.0,double b=0.0,double c=0.0,int d=0) {
		l=a;
		r=b;
		x=c;
		f=d;
	}
};
int n;
seg s[N<<1];
double idy[N<<1];
int siz;
bool cmp(seg a,seg b) {
	return a.x<b.x;
}
struct node {
	int l,r;
	node *lc,*rc;
	double sum;
	int cov;
};
node pool[L<<2];
inline node* newnode() {
	static node* ptr=&pool[0];
	return ++ptr;
}
void build(node *o,int l,int r) {
	o->l=l;
	o->r=r;
	if (r==l+1) return;
	int mid=(l+r)>>1;
	build(o->lc=newnode(),l,mid);
	build(o->rc=newnode(),mid,r);
}
void update(node *o) {
	if (o->cov) o->sum=idy[o->r]-idy[o->l];
	else if (o->r==o->l+1) o->sum=0.0;
	else o->sum=o->lc->sum+o->rc->sum;
}
void add(node *o,int l,int r,int v)
{
	if (o->l>=l&&o->r<=r) {
		o->cov+=v;
		update(o);
		return;
	}
	int mid=(o->l+o->r)>>1;
	if (l<mid) add(o->lc,l,r,v);
	if (r>mid) add(o->rc,l,r,v);
	update(o);
}
int main() 
{
	int kast=0;
	while (scanf("%d",&n)&&n) {
		top=0;
		siz=0;
		double x[2],y[2];
		rep(i,0,n) {
			scanf("%lf%lf%lf%lf",&x[0],&y[0],&x[1],&y[1]);
			s[top++]=seg(y[0],y[1],x[0],1);
			s[top++]=seg(y[0],y[1],x[1],-1);
			idy[siz++]=y[0];
			idy[siz++]=y[1];
		}
		sort(idy,idy+siz);
		int len=unique(idy,idy+siz)-idy;
		build(root,0,len);
		sort(s,s+top,cmp);
		double ans=0;
		rep(i,0,len) id[idy[i]]=i;
		add(root,id[s[0].l],id[s[0].r],1);
		rep(i,1,top) {
			ans+=root->sum*(s[i].x-s[i-1].x);
			add(root,id[s[i].l],id[s[i].r],s[i].f);
		}
		printf("Test case #%d\nTotal explored area: %.2f\n\n",++kast,ans);
	}
	return 0;
}
