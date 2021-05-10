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
const int N=100000+5;
int n,m;
struct node {
	int l,r,tag;
	ll sum;
	node *lc,*rc;
} pool[N<<2];
node* ptr=&pool[0];
inline node* newnode() {
	return ++ptr;
}
void build(node *o,int l,int r) 
{
	o->l=l, o->r=r;
	if (l==r) {
		scanf("%lld",&o->sum);
		o->tag=(o->sum<=1);
		return;
	}
	int mid=(l+r)>>1;
	build(o->lc=newnode(),l,mid);
	build(o->rc=newnode(),mid+1,r);
	o->sum=o->lc->sum+o->rc->sum;
	o->tag=o->lc->tag&o->rc->tag;
}
ll query(node *o,int l,int r)
{
	if (o->l>=l&&o->r<=r) return o->sum;
	int mid=(o->l+o->r)>>1;
	ll ret=0;
	if (l<=mid) ret+=query(o->lc,l,r);
	if (r>mid) ret+=query(o->rc,l,r);
	return ret;
}
void modify(node *o,int l,int r) 
{
	if (o->tag) return;
	if (o->l==o->r) {
		o->sum=sqrt(o->sum);
		o->tag=(o->sum<=1);
		return;
	}
	int mid=(o->l+o->r)>>1;
	if (l<=mid) modify(o->lc,l,r);
	if (r>mid) modify(o->rc,l,r);
	o->sum=o->lc->sum+o->rc->sum;
	o->tag=o->lc->tag&o->rc->tag;
}
int main() 
{
	int cas=0;
	while (~scanf("%d",&n)) {
		ptr=&pool[0];
		build(root,1,n);
		scanf("%d",&m);
		int o,x,y;
		printf("Case #%d:\n",++cas);
		rep(i,0,m) {
			scanf("%d%d%d",&o,&x,&y);
			if (o==0) modify(root,min(x,y),max(x,y));
			else printf("%lld\n",query(root,min(x,y),max(x,y)));
		}
		puts("");
	}
	return 0;
}
