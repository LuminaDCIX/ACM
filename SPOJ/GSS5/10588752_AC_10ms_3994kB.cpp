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
const int N=10000+5;
int n,m;
int s[N];
struct node {
	int l,r;
	int sum,lmx,rmx,mx;
	node *lc,*rc;
} pool[N<<2];
node* ptr=&pool[0];
inline node* newnode() {
	return ++ptr;
}
inline void update(node *o) 
{
	o->sum=o->lc->sum+o->rc->sum;
	o->lmx=max(o->lc->lmx,o->lc->sum+o->rc->lmx);
	o->rmx=max(o->rc->rmx,o->lc->rmx+o->rc->sum);
	o->mx=max(max(o->lc->mx,o->rc->mx),o->lc->rmx+o->rc->lmx);
}
void build(node *o,int l,int r) 
{
	o->l=l, o->r=r;
	if (l==r) {
		scanf("%d",&o->sum);
		o->lmx=o->rmx=o->mx=o->sum;
		s[l]=s[l-1]+o->sum;
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
	else if(l>mid) query(o->rc,l,r,L,R,MX,S);
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
	return;
}

int main() 
{
	int T;
	scanf("%d",&T);
	while (T--) {
		scanf("%d",&n);
		ptr=root;
		build(root,1,n);
		scanf("%d",&m);
		int x1,x2,y1,y2;
		int L,R,MX,S;
		rep(i,0,m) {
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			int ans=0;
			int a=0,b=0,c=0,d=0;
			if (y1<x2) {
				query(root,x1,y1,L,R,MX,S), ans+=R;
				query(root,x2,y2,L,R,MX,S), ans+=L;
				printf("%d\n",s[x2-1]-s[y1]+ans);
			}
			else {
				query(root,x2,y1,L,R,MX,S), ans=MX, a=S, b=L, c=R;
				if (x1!=x2) query(root,x1,x2-1,L,R,MX,S), ans=max(ans,R+b), b=R;
				else b=0;
				if (y1!=y2) query(root,y1+1,y2,L,R,MX,S), ans=max(ans,L+c), c=L;
				else c=0;
				ans=max(ans, a+b+c);
				printf("%d\n",ans);
			}
		}
	}
	return 0;
}
