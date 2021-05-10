#include <bits/stdc++.h>
#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define root (&pool[0])
using namespace std;

const int N=2*1e5+5;
typedef long long ll;
int n,m;
ll t[N],cnt[N];
struct point {
	int x,t,num;
	bool operator < (const point rhs) const {
		return x<rhs.x;
	}
}p[N];
multiset<point> s;
int id[N];
struct node {
	node *lc,*rc;
	int l,r,mx;
}pool[N<<2];
inline node* newnode() {
	static node *ptr=&pool[0];
	return ++ptr;
}
void build(node *o,int l,int r) 
{
	o->l=l,o->r=r;
	if (l==r) {
		o->mx=p[l].x+p[l].t;
		return;
	}
	int mid=(l+r)>>1;
	build(o->lc=newnode(),l,mid);
	build(o->rc=newnode(),mid+1,r);
	o->mx=max(o->lc->mx,o->rc->mx);
}
int query(node *o,int l,int r)
{
	if (o->l>=l&&o->r<=r) return o->mx;
	int mid=(o->l+o->r)>>1,x=-1e9;
	if (l<=mid) x=max(x,query(o->lc,l,r));
	if (r>mid) x=max(x,query(o->rc,l,r));
	return x;
}
void add(node *o,int p,int v) 
{
	if (o->l==p&&o->r==p) {
		o->mx+=v;
		return;
	}
	int mid=(o->l+o->r)>>1;
	if (p<=mid) add(o->lc,p,v);
	if (p>mid) add(o->rc,p,v);
	o->mx=max(o->lc->mx,o->rc->mx);
}
inline int lowerbd(int x) 
{
	int ans=-1,l=0,r=upper_bound(id,id+n,x)-id-1;
	int mid;
	while (l<=r) {
		mid=(l+r)>>1;
		if (query(root,0,mid)>=x) ans=mid,r=mid-1;
		else l=mid+1;
	}
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	rep(i,0,n) scanf("%d%d",&p[i].x,&p[i].t),p[i].num=i,t[i]=p[i].t;
	sort(p,p+n);
	rep(i,0,n) id[i]=p[i].x;
	build(root,0,n-1);
	int x,y;
	rep(i,0,m) {
		scanf("%d%d",&x,&y);
		int pos=lowerbd(x);
		if (pos==-1) {
			s.insert((point){x,y});
			continue;
		}
		add(root,pos,y);
		t[p[pos].num]+=y; cnt[p[pos].num]++;
		set<point>::iterator it=s.lower_bound((point){id[pos],0});
		while (it!=s.end()&&it->x<=id[pos]+t[p[pos].num]) {
			t[p[pos].num]+=it->t; cnt[p[pos].num]++;
			add(root,pos,it->t);
			s.erase(it++);
		}
	}
	rep(i,0,n) printf("%lld %lld\n",cnt[i],t[i]);
	return 0;
}
