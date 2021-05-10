#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,b) for (int i=(n)-1;i>=a;--i)
#define root (&pool[0])
using namespace std;
typedef long long ll;
const int N=50000+5;
int n,m;
struct node {
	int l,r;
	node *lc,*rc;
	int len[2]; // 0 left  1 right 
	int mx,tag;
	void update() {
		mx=max(max(lc->mx,rc->mx),lc->len[1]+rc->len[0]);
		len[0]=(lc->len[0]==(lc->r-lc->l+1))?lc->len[0]+rc->len[0]:lc->len[0];
		len[1]=(rc->len[1]==(rc->r-rc->l+1))?rc->len[1]+lc->len[1]:rc->len[1];
	}
	void pushdown() {
		if (l==r) return;
		if (tag!=-1) {
			lc->tag=rc->tag=tag;
			lc->mx=(tag==1?0:lc->r-lc->l+1);
			rc->mx=(tag==1?0:rc->r-rc->l+1);
			lc->len[0]=lc->len[1]=lc->mx;
			rc->len[0]=rc->len[1]=rc->mx;
			tag=-1;
		}
	}
} pool[N<<2];
inline node* newnode() {
	static node* ptr=root;
	return ++ptr;
}
void build(node *o,int l,int r)
{
	o->l=l, o->r=r, o->tag=-1;
	o->len[0]=o->len[1]=o->mx=r-l+1;
	if (l==r) return;
	int mid=(r+l)>>1;
	build(o->lc=newnode(),l,mid);
	build(o->rc=newnode(),mid+1,r);
}
int query(node *o,int k)
{
	o->pushdown();
	int mid=(o->l+o->r)>>1;
	if (o->lc->mx>=k) return query(o->lc,k);
	else if (o->lc->len[1]+o->rc->len[0]>=k) return mid-o->lc->len[1]+1;
	else return query(o->rc,k);
	o->update();
}
void modify(node *o,int l,int r,int v)
{
	o->pushdown();
	if (o->l>=l&&o->r<=r) {
		o->tag=v;
		o->mx=(v==1)?0:o->r-o->l+1;
		o->len[0]=o->len[1]=o->mx;
		return;
	}
	int mid=(o->l+o->r)>>1;
	if (l<=mid) modify(o->lc,l,r,v);
	if (r>mid) modify(o->rc,l,r,v);
	o->update();
}
int main()
{
	scanf("%d%d",&n,&m);
	build(root,1,n);
	int o,x,y;
	rep(i,0,m) {
		scanf("%d",&o);
		if (o==1) {
			scanf("%d",&x);
			if (root->mx<x) {
				puts("0");
				continue;
			}
			y=query(root,x), printf("%d\n",y), modify(root,y,y+x-1,1);
		}
		else scanf("%d%d",&x,&y), modify(root,x,x+y-1,0);
	}
	return 0;
}
