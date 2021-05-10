#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)
#define root (&pool[0])
using namespace std;

const int N=50000+5;
struct node{
	int l,r;
	node *lc,*rc;
	int lmx,rmx,mx,sum;
} pool[N<<2];
int n;
inline node* newnode() {
	static node* ptr=&pool[0];
	return ++ptr;
}
void update(node *o) 
{
	o->mx=max(max(o->lc->mx,o->rc->mx),o->lc->rmx+o->rc->lmx);
	o->lmx=max(o->lc->lmx,o->lc->sum+o->rc->lmx);
	o->rmx=max(o->rc->rmx,o->rc->sum+o->lc->rmx);
	o->sum=o->lc->sum+o->rc->sum;
}
void build(node *o,int l,int r) 
{
	o->l=l, o->r=r;
	if (l==r) {
		scanf("%d",&o->sum);
		o->lmx=o->rmx=o->mx=o->sum;
		return;
	}
	int mid=(l+r)>>1;
	build(o->lc=newnode(),l,mid);
	build(o->rc=newnode(),mid+1,r);
	update(o);
}
void query(node *o,int l,int r,int &L,int &R,int &MX,int &S)
{
	if (o->l>=l&&o->r<=r) {
		L=o->lmx, R=o->rmx, MX=o->mx, S=o->sum;
		return;
	}
	int mid=(o->l+o->r)>>1;
	if (r<=mid) query(o->lc,l,r,L,R,MX,S);
	else if (l>mid) query(o->rc,l,r,L,R,MX,S);
	else {
		int L1,R1,MX1,S1;
		int L2,R2,MX2,S2;
		query(o->lc,l,r,L1,R1,MX1,S1);
		query(o->rc,l,r,L2,R2,MX2,S2);
		L=max(L1,S1+L2);
		R=max(R2,S2+R1);
		MX=max(max(MX1,MX2),R1+L2);
		S=S1+S2;
	}
}
int main()
{
	scanf("%d",&n);
	int L=-1e9,R=-1e9,MX=-1e9,S=0;
	int l,r;
	build(root,1,n);
	int m;
	scanf("%d",&m);
	rep(i,0,m) {
		scanf("%d%d",&l,&r);
		L=R=MX=-1e9, S=0;
		query(root,l,r,L,R,MX,S);
		printf("%d\n",max(max(L,R),max(MX,S)));
	}
	return 0;
}
