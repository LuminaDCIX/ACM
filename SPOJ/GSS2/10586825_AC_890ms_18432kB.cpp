#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,b) for (int i=(n)-1;i>=a;--i)
#define root (&pool[0])
#define lst(i) (lst[i+N])
using namespace std;

const int N=100000+5;
int n,m;
int x[N];
int lst[N<<2];
int ans[N];
struct node {
	int l,r;
	node *lc,*rc;
	int mx,prmx;
	int ad,prad;
} pool[N<<2];
struct Q {
	int l,r,id;
} q[N];
bool cmp(Q a,Q b) {
	return a.r<b.r;
}
inline node* newnode() {
	static node* ptr=&pool[0];
	return ++ptr;
}
void build(node *o,int l,int r)
{
	o->l=l, o->r=r;
	if (l==r) {
		o->mx=0, o->prmx=o->prad=-1e9;
		return;
	}
	int mid=(l+r)>>1;
	build(o->lc=newnode(),l,mid);
	build(o->rc=newnode(),mid+1,r);
}
void pushdown(node *o) {
	o->lc->prad=max(o->lc->prad,o->prad+o->lc->ad);
	o->rc->prad=max(o->rc->prad,o->prad+o->rc->ad);
	o->lc->prmx=max(o->lc->prmx,o->lc->mx+o->prad);
	o->rc->prmx=max(o->rc->prmx,o->rc->mx+o->prad);
	if (o->ad) {
		o->lc->ad+=o->ad, o->lc->mx+=o->ad;
		o->rc->ad+=o->ad, o->rc->mx+=o->ad;
	}
	o->ad=0, o->prad=-1e9;
}
int query(node *o,int l,int r)
{
	if (o->l!=o->r) pushdown(o);
	if (o->l>=l&&o->r<=r) return o->prmx;
	int mid=(o->l+o->r)>>1,x=-1e9;
	if (l<=mid) x=max(x,query(o->lc,l,r));
	if (r>mid) x=max(x,query(o->rc,l,r));
	o->mx=max(o->lc->mx,o->rc->mx);
	o->prmx=max(o->lc->prmx,o->rc->prmx);
	return x;
}
void modify(node *o,int l,int r,int v)
{
	if (o->l!=o->r) pushdown(o);
	if (o->l>=l&&o->r<=r) {
		o->ad=o->prad=v;
		o->mx+=v, o->prmx=max(o->prmx,o->mx);
		return;
	}
	int mid=(o->l+o->r)>>1;
	if (l<=mid) modify(o->lc,l,r,v);
	if (r>mid) modify(o->rc,l,r,v);
	o->mx=max(o->lc->mx,o->rc->mx);
	o->prmx=max(o->lc->prmx,o->rc->prmx);
}
int main()
{
	scanf("%d",&n);
	build(root,0,n-1);
	rep(i,0,n) scanf("%d",&x[i]);
	scanf("%d",&m);
	rep(i,0,m) scanf("%d%d",&q[i].l,&q[i].r), q[i].id=i, --q[i].l, --q[i].r;
	sort(q,q+m,cmp);
	memset(lst,-1,sizeof(lst));
	int r=0;
	rep(i,0,m) {
		while (r<=q[i].r) modify(root,lst(x[r])+1,r,x[r]), lst(x[r])=r++;
		ans[q[i].id]=query(root,q[i].l,q[i].r);
	}
	rep(i,0,m) printf("%d\n",ans[i]);
	return 0;
}
