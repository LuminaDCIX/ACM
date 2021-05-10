#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<cstring>

typedef long long ll;
using namespace std;

const int maxn=50000;
const int maxm=100000;
struct node
{
  int l,r;
  node *son[2];
  int val;
}
pool[maxm*4+5];
int ptop=0;
node* root;
int n,s;
int f[maxn+5][2];
int nxt[maxn+5][2];
int L[maxn+5],R[maxn+5];

inline node* newnode()
{
  return &pool[ptop++];
}

void build(node* o,int l,int r)
{
  o->l=l;
  o->r=r;
  o->val=0;
  if (l==r) {
    return;
  }
  int mid=(l+r)>>1;
  build(o->son[0]=newnode(),l,mid);
  build(o->son[1]=newnode(),mid+1,r);
  return;
}


int res=0;
void query(node* o,int x)
{
  res=max(res,o->val);
  if (o->l==o->r) {
    return;
  }
  int mid=(o->l+o->r)>>1;
  if (x<=mid) {
    query(o->son[0],x);
  }
  if (x>mid) {
    query(o->son[1],x);
  }
  return;
}

int v,l,r;
void modify(node* o)
{
  if (o->l>=l&&o->r<=r) {
    o->val=v;
    return;
  }
  int mid=(o->l+o->r)>>1;
  if (l<=mid) {
    modify(o->son[0]);
  }
  if (r>mid) {
    modify(o->son[1]);
  }
  return;
}

inline int read()
{
  int x=0,f=1;
  char ch=getchar();
  while(ch<'0'||ch>'9') {
    f=ch=='-'?-1:1;
    ch=getchar();
  }
  while(ch>='0'&&ch<='9') {
    x=x*10+ch-'0';
    ch=getchar();
  }
  return x*f;
}

int main()
{
  root=newnode();
  build(root,1,2*maxm);
  n=read();
  s=read()+maxm;
  for (int i=1;i<=n;++i) {
    res=0;
    L[i]=read()+maxm;
    R[i]=read()+maxm;
    query(root,L[i]);
    nxt[i][0]=res;
    res=0;
    query(root,R[i]);
    nxt[i][1]=res;
    l=L[i];
    r=R[i];
    v=i;
    modify(root);
  }
  memset(f,0x3f3f,sizeof(f));
  f[n][1]=abs(R[n]-s);
  f[n][0]=abs(L[n]-s);
  L[0]=R[0]=maxm;
  for (int i=n;i>=1;--i) {
    f[nxt[i][0]][0]=min(f[nxt[i][0]][0],f[i][0]+abs(L[i]-L[nxt[i][0]]));
    f[nxt[i][0]][1]=min(f[nxt[i][0]][1],f[i][0]+abs(L[i]-R[nxt[i][0]]));
    f[nxt[i][1]][0]=min(f[nxt[i][1]][0],f[i][1]+abs(R[i]-L[nxt[i][1]]));
    f[nxt[i][1]][1]=min(f[nxt[i][1]][1],f[i][1]+abs(R[i]-R[nxt[i][1]]));
  }
  printf("%d\n",min(f[0][0],f[0][1]));
  return 0;
}
