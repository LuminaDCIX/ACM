#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)
#define rep(i,a,n) for (int i=(a);i<(n);++i)
typedef long long ll;

const int N=5e5+5;
const int SIZ=26;
const int MAX=1e6+5;

struct node {
  node *fa,*nxt[SIZ];
  int len,siz;
  ll sum;
} pool[MAX],*root=pool,*lst=pool,*ptr=pool+1;

node* newnode(int x) {
  ptr->len=x;
  return ptr++;
}

void extend(int x) {
  node *p=lst,*np=newnode(p->len+1);
  while (p&&p->nxt[x]==0) p->nxt[x]=np,p=p->fa;
  if (!p) np->fa=root;
  else {
    node *q=p->nxt[x];
    if (q->len==p->len+1) np->fa=q;
    else {
      node *nq=newnode(p->len+1);
      memcpy(nq->nxt,q->nxt,sizeof(q->nxt));
      nq->fa=q->fa;
      np->fa=q->fa=nq;
      while (p&&p->nxt[x]==q) p->nxt[x]=nq,p=p->fa;
    }
  }
  lst=np,np->siz=1;
}

char str[N];
int n,t,k;

int c[N];
node *a[MAX];

void init() {
  int cnt=0;
  for (node *x=pool+1;x!=ptr;++x) ++c[x->len];
  rep (i,1,n+1) c[i]+=c[i-1];
  cnt=c[n]-1;
  for (node *x=pool+1;x!=ptr;++x) a[--c[x->len]]=x;

  for (node **y=a+cnt;y!=a-1;--y) {
    node *x=*y,*p=x->fa;
    if (!t) x->siz=1;
    else x->fa->siz+=x->siz;
    x->sum+=x->siz;
    rep (i,0,26) if (x->nxt[i]) x->sum+=x->nxt[i]->sum;
  }
  root->siz=0;
  rep (i,0,26) if (root->nxt[i]) root->sum+=root->nxt[i]->sum;
}

int top,stk[MAX];
bool dfs(node *u) {
  if (u->sum<k) {
    k-=u->sum;
    return false;
  }
  int x=u->siz;
  if (k<=x) return 1;
  k-=x;
  rep (i,0,26) if (u->nxt[i]) {
    stk[top++]=i;
    if (dfs(u->nxt[i])) return true;
    --top;
  }
}

int main() {
  scanf("%s",str);
  n=strlen(str);
  rep (i,0,n) extend(str[i]-'a');
  scanf("%d%d",&t,&k);
  init();
  if (!dfs(root)) {
    puts("-1");
    return 0;
  }
  rep (i,0,top) putchar(stk[i]+'a');
  puts("");
  return 0;
}
