 #include <set>
 #include <map>
 #include <queue>
 #include <stack>
 #include <cmath>
 #include <vector>
 #include <cstdio>
 #include <bitset>
 #include <cstdlib>
 #include <cstring>
 #include <iostream>
 #include <algorithm>

 #define y0 y0z
 #define y1 y1z
 #define yn ynz
 #define j0 j0z
 #define j1 j1z
 #define jn jnz
 #define fi first
 #define se second
 #define mp make_pair
 #define pb push_back
 #define fil(a,b) memset((a),(b),sizeof(a))
 #define all(x) (x).begin(),(x).end()
 #define siz(x) ((int)(x).size()) 
 #define rep(i,a,n,...) for (int i=(a);i<(n);++i)
#define per(i,a,n,...) for (int i=(n)-1;i>=(a);--i)
 #define debug(...) fprintf(stderr,__VA_ARGS__)
 using namespace std;

 typedef long long ll;
 typedef vector <int> vi;
 typedef pair <int,int> pii;

 char xB[1<<15],*xS=xB,*xT=xB;  
 #define getc() (xS==xT&&(xT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xT)?0:*xS++)  
 inline ll read() {
   ll x=0;
   int f=1;
   char ch=getc();
   for (;ch<'0'||ch>'9';f=(ch=='-')?-1:1,ch=getc());
   for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getc());
   return f*x;
 }

 inline void timer() {
 #ifdef MiracleEEEE
   clock_t s_=clock();
   if (s_/1000<=5) {
     fprintf(stderr,"time=%ldmicrosecond\n",s_);
   } else {
     fprintf(stderr,"time=%ldmillisecond\n",s_/1000);
   }
 #endif
 }

 inline void file(string name) {
   freopen((name+".in").c_str(),"r",stdin);
   freopen((name+".out").c_str(),"w",stdout);
 }

 //head

 const int N=2e5+5;

 int n;
 int m;

 struct graph {
   int tot;
   int head[N];

   struct edge {
     int nxt;
     int to;
   };

   edge e[N<<1];

   inline void add(int u,int v) {
     e[tot].to=v;
     e[tot].nxt=head[u];
     head[u]=tot++;
   }
 };

 graph g1;
 graph g2;

 stack <pii> s;

 int dfs_cnt;
 int dfn[N];
 int low[N];

 int bcc[N];
 int nbcc;

 vector <int> bel[N];
 int is_cut[N];

 void dfs(int u,int fa) {
   dfn[u]=++dfs_cnt;
   low[u]=dfs_cnt;
   int ch=0;
   for (int o=g1.head[u],v;~o;o=g1.e[o].nxt) {
     v=g1.e[o].to;
     pii c=mp(u,v);
     if (!dfn[v]) {
       s.push(c);
       dfs(v,u);
       ++ch;
       low[u]=min(low[u],low[v]);
       if (low[v]>=dfn[u]) {
         ++nbcc;
         is_cut[u]=1;
         while (true) {
           pii x=s.top();
           s.pop();
           if (bcc[x.fi]!=nbcc) {
             bcc[x.fi]=nbcc;
             bel[x.fi].pb(nbcc);
           }
           if (bcc[x.se]!=nbcc) {
             bcc[x.se]=nbcc;
             bel[x.se].pb(nbcc);
           }
           if (x.fi==u&&x.se==v) {
             break;
           }
         }
       }
     } else if (dfn[v]<dfn[u]&&v!=fa) {
       s.push(c);
       low[u]=min(low[u],dfn[v]);
     }
   }
   if (fa==-1&&ch<=1) {
     is_cut[u]=0;
   }
   return;
 }

 int val[N];
 int q;

 multiset <int> mn[N];

 int son[N];
 int fa[N];
 int id[N];
 int pre[N];
 int siz[N];
 int top[N];
 int dep[N];

 int cnt;

 void dfs0(int u,int f) {
   siz[u]=1;
   fa[u]=f;
   //  debug("to%d\n",u);
   for (int o=g2.head[u],v;~o;o=g2.e[o].nxt) {
     v=g2.e[o].to;
     if (v==f) {
       continue;
     }
     dep[v]=dep[u]+1;
     dfs0(v,u);
     siz[u]+=siz[v];
     if (siz[v]>siz[son[u]]) {
       son[u]=v;
     }
   }
 }

 void dfs1(int u,int f,int anc) {
   id[u]=++cnt;
   pre[cnt]=u;
   top[u]=anc;
   if (!son[u]) {
     return;
   }
   dfs1(son[u],u,anc);
   for (int o=g2.head[u],v;~o;o=g2.e[o].nxt) {
     v=g2.e[o].to;
     if (v==f||v==son[u]) {
       continue;
     }
     dfs1(v,u,v);
   }
 }

 struct node {
   node *lc;
   node *rc;
   int mn;
 };

 node pool[N<<2];

 node *root=&pool[0];

 inline node* newnode() {
   static node* ptr=root;
   return ++ptr;
 }

 void build(node *o,int ll,int rr) {
   if (ll==rr) {
     o->mn=*mn[pre[ll]].begin();
     return;
   }
   int mid=ll+rr>>1;
   build(o->lc=newnode(),ll,mid);
   build(o->rc=newnode(),mid+1,rr);
   o->mn=min(o->lc->mn,o->rc->mn);
 }

 int lca(int a,int b) {
   while (top[a]!=top[b]) {
     if (dep[top[a]]>dep[top[b]]) {
       a=fa[top[a]];
     } else {
       b=fa[top[b]];
     }
   }
   return dep[a]>dep[b]?b:a;
 }

 void modify(node *o,int ll,int rr,int p,int v) {
   if (ll==p&&rr==p) {
     o->mn=v;
     return;
   }
   int mid=ll+rr>>1;
   if (p<=mid) {
     modify(o->lc,ll,mid,p,v);
   } else {
     modify(o->rc,mid+1,rr,p,v);
   }
   o->mn=min(o->lc->mn,o->rc->mn);
 }

 int query(node *o,int ll,int rr,int l,int r) {
   if (ll>=l&&rr<=r) {
     return o->mn;
   }
   int mid=ll+rr>>1;
   if (r<=mid) {
     return query(o->lc,ll,mid,l,r);
   } else if (l>mid) {
     return query(o->rc,mid+1,rr,l,r);
   } else {
     return min(query(o->lc,ll,mid,l,r),query(o->rc,mid+1,rr,l,r));
   }
 }

inline int query(int x,int y) {
  int ret=1e9;
  while (top[x]!=top[y]) {
    ret=min(ret,query(root,1,2*n,id[top[x]],id[x]));
    x=fa[top[x]];
  }
  return min(ret,query(root,1,2*n,id[y],id[x]));
}

int main() {
  n=read();
  m=read();
  q=read();
  fil(g1.head,-1);
  fil(g2.head,-1);
  rep (i,1,n+1) {
    val[i]=read();
  }
  rep (i,0,m) {
    int u=read();
    int v=read();
    g1.add(u,v);
    g1.add(v,u);
  }
  dfs(1,-1);
  rep (i,1,n+1) {
    if (is_cut[i]) {
      rep (j,0,siz(bel[i])) {
        g2.add(n+i,bel[i][j]);
        g2.add(bel[i][j],n+i);
      }
    }
  }
  dfs0(1,0);
  dfs1(1,0,1);
  rep (i,1,n+1) {
    if (is_cut[i]) {
      mn[fa[i+n]].insert(val[i]);
      mn[i+n].insert(1e9);
    } else {
      mn[bcc[i]].insert(val[i]);
    }
  }
  char o;
  build(root,1,2*n);
  rep (i,0,q) {
    int o=getc();
    int x=read();
    int y=read();
    if (o=='A') {
      if (x==y) {
        printf("%d\n",val[x]);
        continue;
      }
      x=is_cut[x]?x+n:bcc[x];
      y=is_cut[y]?y+n:bcc[y];
      int c=lca(x,y);
      int t=1e9;
      if (c>n) {
        t=val[c-n];
      } else if (c!=1) {
        t=val[fa[c]-n];
      }
      printf("%d\n",min(t,min(query(x,c),query(y,c))));
    } else {
      int t=val[x];
      val[x]=y;
      if (is_cut[x]) {
        if (fa[x+n]) {
          mn[fa[x+n]].erase(t);
          mn[fa[x+n]].insert(y);
          modify(root,1,2*n,id[fa[x+n]],*mn[fa[x+n]].begin());
        }
      } else {
        mn[bcc[x]].erase(t);
        mn[bcc[x]].insert(y);
        modify(root,1,2*n,id[bcc[x]],*mn[bcc[x]].begin());
      }
    }
  }
  return 0;
}
