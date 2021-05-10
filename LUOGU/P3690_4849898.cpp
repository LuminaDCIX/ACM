#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define lct(x) t[x-1]

const int N=3e5+5;

inline int read() {
  int x=0; char ch=getchar();
  while (ch<'0'||ch>'9') ch=getchar();
  while (ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
  return x;
}

struct node {
  node *l,*r,*fa;
  int v,xv,rflg;

  inline void rev() {
    swap(l,r), rflg^=1;
  }

  inline void pushup() {
    if (fa->l==this||fa->r==this) fa->pushup();
    if (rflg) l->rev(), r->rev(), rflg=0;
  }

  inline void update() {
    xv=l->xv^r->xv^v;
  }
};

typedef node* lct;

node p[N],*t[N],*null=p;

inline lct newnode(int v) {
  static lct ptr=&p[1];
  ptr->l=ptr->r=ptr->fa=null;
  ptr->v=ptr->xv=v; return ptr++;
}

inline void rot(lct x) {
  lct y=x->fa,z=y->fa,b=null;
  if (y->l==x) b=x->r, x->r=y, y->l=b;
  else b=x->l, x->l=y, y->r=b;
  b->fa=y, y->fa=x;
  if (z->l==y) z->l=x;
  else if (z->r==y) z->r=x;
  x->fa=z, y->update();
}

inline void splay(lct x) {
  x->pushup();
  while (x->fa->l==x||x->fa->r==x) {
    lct y=x->fa,z=y->fa;
    if ((y->l==x&&z->l==y)||(y->r==x&&z->r==y)) rot(y);
    rot(x);
  }
  x->update();
}

inline void access(lct x) {
  lct y=null;
  while (x!=null) {
    splay(x), x->r=y, y=x, x->update(), x=x->fa;
  }
}

inline void make_root(lct x) {
  access(x), splay(x), x->rev();
}

inline int query(lct x,lct y) {
  make_root(x), access(y), splay(y); return y->xv;
}

inline lct find_fa(lct x) {
  while (x->fa!=null) x=x->fa; return x;
}

inline void link(lct x,lct y) {
  make_root(x), x->fa=y;
}

inline void cut(lct x,lct y) {
  make_root(x), access(y), splay(y);
  if (y->l==x) y->l=x->fa=null, y->update();
}

int n,m;

int main() {
  null->fa=null->l=null->r=null;
  n=read(),m=read();
  rep (i,0,n) t[i]=newnode(read());
  rep (i,0,m) {
    int o=read(),x=read(),y=read();
    if (o==0) printf("%d\n",query(lct(x),lct(y)));
    else if (o==1&&(find_fa(lct(x))!=find_fa(lct(y)))) link(lct(x),lct(y));
    else if (o==2) cut(lct(x),lct(y));
    else make_root(lct(x)), lct(x)->xv=lct(x)->xv^lct(x)->v^y, lct(x)->v=y;
  }

  return 0;
}
