#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;
#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)
#define forg(u) for (int o=head[u],v;~o;o=e[o].nxt) 
#define lson o->lc,ll,mid
#define rson o->rc,mid+1,rr

inline int read() { int x; scanf("%d",&x); return x; }

const int N=100000+5;

int n;

int head[N],tot;

struct edge { int nxt,to; } e[N<<2];

inline void add(int u,int v) { e[tot].to=v,e[tot].nxt=head[u],head[u]=tot++; }

struct node {
  int c,v;
  node *lc,*rc;
  
  void psd() { if (lc&&rc&&c!=-1) lc->v=rc->v=lc->c=rc->c=c, c=-1; }
} pool[N<<2];

node *root=&pool[0],*ptr=&pool[0];

inline node* newnode() { return ++ptr; }

void build(node *o,int ll,int rr) {
  o->c=o->v=-1;
  if (ll==rr) return;
  int mid=ll+rr>>1;
  build(o->lc=newnode(),ll,mid),build(o->rc=newnode(),mid+1,rr);
}

void cov(node *o,int ll,int rr,int l,int r,int v) {
  o->psd();
  if (ll>=l&&rr<=r) { o->v=o->c=v; return; }
  int mid=ll+rr>>1;
  if (l<=mid) cov(lson,l,r,v); if (r>mid) cov(rson,l,r,v);
}

int qry(node *o,int ll,int rr,int p) {
  o->psd();
  if (ll==rr&&rr==p) return o->v;
  int mid=ll+rr>>1;
  if (p<=mid) return qry(lson,p); else return qry(rson,p);
}

struct atom { int l,r; } p[N];

bool cmp(const atom&a,const atom&b) { return a.l==b.l?a.r<b.r:a.l<b.l; }

int cnt;
int a[N];
int mn[N],mx[N],exi[N];

int ind[N],f[N];
int que[N],h,t;

inline int topo() {
  rep (u,0,cnt) forg(u) ++ind[e[o].to];
  rep (i,0,cnt) if (ind[i]==0) que[t++]=i;
  while (h<t) {
    int u=que[h++];
    forg(u) {
      v=e[o].to,--ind[v];
      if (ind[v]==0) que[t++]=v;
    }
  }
  per (i,0,cnt) forg(que[i]) v=e[o].to,f[que[i]]=max(f[que[i]],f[v]+1);
  int ret=0; rep (i,0,cnt) ret=max(ret,f[i]); return ret;
}

int main() {
  memset(head,-1,sizeof(head));
  n=read();
  rep (i,0,n) a[i]=read();// ,printf("%d %d\n",i,a[i]);
  rep (i,0,N) mx[i]=-1,mn[i]=1e9;
  int t; rep (i,0,n) t=a[i],exi[t]=1,mn[t]=min(mn[t],i),mx[t]=max(mx[t],i);
  rep (i,1,N) if (exi[i]) p[cnt++]=(atom){mn[i],mx[i]};
  sort(p,p+cnt,cmp); 
  // rep (i,0,cnt) cerr<<p[i].l<<" "<<p[i].r<<endl
    ;
  build(root,0,n);
  rep (i,0,cnt) {
    int lcol=qry(root,0,n,p[i].l),rcol=qry(root,0,n,p[i].r);
    if (lcol!=rcol) { // cerr<<i<<" "<<lcol<<" "<<rcol<<endl;
      puts("-1"); return 0; }
    if (lcol!=-1) add(lcol,i);// ,cerr<<lcol<<"->"<<i<<endl;
    cov(root,0,n,p[i].l,p[i].r,i);
  }
  printf("%d\n",topo()+1);
  return 0;
}
