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
const int N=200000+5;
int n;
int x[N];
int pos[N],val[N];
struct node {
	int l,r,sum;
	node *lc,*rc;
} pool[N<<2];
node *ptr=root;
inline node* newnode() {
	return ++ptr;
}
void build(node *o,int l,int r)
{
	o->l=l, o->r=r, o->sum=0;
	if (l==r) return;
	int mid=(l+r)>>1;
	build(o->lc=newnode(),l,mid);
	build(o->rc=newnode(),mid+1,r);
}
int findkth(node *o,int k) 
{
	if (o->l==o->r) return o->l;
	int mid=(o->l+o->r)>>1;
	int lft=mid-o->l+1-o->lc->sum;
	if (lft>=k) return findkth(o->lc,k);
	else return findkth(o->rc,k-lft);
}
void add(node *o,int p)
{
	if (o->l==o->r) {
		o->sum+=1;
		return;
	}
	int mid=(o->l+o->r)>>1;
	if (p<=mid) add(o->lc,p);
	if (p>mid) add(o->rc,p);
	o->sum=o->lc->sum+o->rc->sum;
}

int main()
{
	while (~scanf("%d",&n)) {
		ptr=root;
		build(root,0,n-1);
		rep(i,0,n) scanf("%d%d",&pos[i],&val[i]), ++pos[i];
		int k;
		per(i,0,n) k=findkth(root,pos[i]), x[k]=val[i], add(root,k);
		rep(i,0,n) printf("%d ",x[i]);
		puts("");
	}
	return 0;
}
