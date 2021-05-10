#include<bits/stdc++.h>

using namespace std;

const int maxn=50000;
const int maxm=100000;

int n,m;
struct edge
{
  int from,to,va,vb;
  bool operator < (const edge a) const 
  {
    return va==a.va?vb<a.vb:va<a.va;
  }
}
edges[maxm+5];


struct node
{
  node *l,*r,*fa;
  int v,maxv,id;
  bool rtag;
  void init(int x,int p);
  void update();
  void rev()
  {
    swap(l,r);
    rtag^=1;
  }
  void push()
  {
    if (fa->l==this||fa->r==this) {
      fa->push();
    }
    if (rtag) {
      l->rev();
      r->rev();
      rtag=0;
    }
  }
}
p[maxn+maxm+5],*t[maxn+maxm+5],*null;

inline void node::init(int x,int p)
{
  l=r=fa=null;
  v=x;
  id=maxv=p;
  
  return;
}

bool cmp(int a,int b)
{
  return edges[a].vb<edges[b].vb;
}

inline void node::update()
{
  //puts("1");
  //maxv=v;
  maxv=max(id,max(l->maxv,r->maxv,cmp),cmp);
  //puts("2");
  return;
}

inline void rot(node *x)
{ 
  node *y=x->fa;
  node *z=y->fa;
  node *b;
  if (y->l==x) {
    b=x->r;
    x->r=y;
    y->l=b;
  }
  else if (y->r==x) {
    b=x->l;
    x->l=y;
    y->r=b;
  }
  b->fa=y;
  y->fa=x;
  if (z->l==y) {
    z->l=x;
  }
  else if (z->r==y) {
    z->r=x;
  }
  x->fa=z;
  y->update();
  return;
}

inline void splay(node *x)
{
  node *y,*z;
  x->push();
  while (x->fa->l==x||x->fa->r==x) {
    y=x->fa;
    z=y->fa;
    if ((y->l==x&&z->l==y)||(y->r==x&&z->r==y)) {
      rot(y);
    }
    rot(x);
  }
  x->update();
  return;
}

inline void access(node *x)
{
  node *y=null;
  while (x!=null) {
    splay(x);
    x->r=y;
    x->update();
    y=x;
    x=x->fa;
  }
  return;
}

inline void move_to_root(node *x)
{
  access(x);
  splay(x);
  x->rev();
  return;
}

inline void link(node *x,node *y)
{
  move_to_root(x);
  x->fa=y;
  return;
}

inline void cut(node *x,node *y)
{
  move_to_root(x);
  access(y);
  splay(y);
  y->l=null;
  x->fa=null;
  y->update();
  return;
}

node* find_fa(node *a)
{
  while (a->fa!=null) {
    a=a->fa;
  }
  return a;
}

int query(node *a,node *b)
{
  move_to_root(a);
  access(b);
  splay(b);
  return b->maxv;
}

int main()
{
int ans=0x7fffffff;
  null=new node();
  null->init(0,0);
  t[0]=&p[0];
  t[0]->init(0,0);
  scanf("%d%d",&n,&m);
  for (int i=1;i<=m;++i) {
    scanf("%d%d%d%d",&edges[i].from,&edges[i].to,&edges[i].va,&edges[i].vb);
  }
  sort(edges+1,edges+1+m);
  for (int i=1;i<=n+m;++i) {
    t[i]=&p[i];
  }
  for (int i=1;i<=n;++i) {
    t[i]->init(0,0);
  }
  for (int i=1;i<=m;++i) {
    edge e=edges[i];
    t[i+n]->init(e.vb,i);
    if (find_fa(t[e.from])==find_fa(t[e.to])) {
      int k=query(t[e.from],t[e.to]);
      if (edges[k].vb>e.vb) {
        cut(t[edges[k].from],t[k+n]);
        cut(t[k+n],t[edges[k].to]);
        link(t[e.from],t[i+n]);
        link(t[i+n],t[e.to]);
      }
    }
    else {
      link(t[e.from],t[i+n]);
      link(t[i+n],t[e.to]);
    }
    if (find_fa(t[1])==find_fa(t[n])) {
      int k=query(t[1],t[n]);
      ans=min(ans,edges[i].va+edges[k].vb);
      //printf("%d %d\n",k,t[k]->v);
      //return 0;
    }
  }
  printf("%d\n",(ans==0x7fffffff)?-1:ans);
  return 0;
}