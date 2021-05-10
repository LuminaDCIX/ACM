#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
using namespace std;
#define REP(i,a,n) for (int i=a;i<=n;i++)
#define PER(i,a,n) for (int i=n;i>=a;i--)
#define MEM(a,b) memset(a,b,sizeof(a))
#define PAUSE system("pause")
#define FILE
#define DEBUG
#define Siz(t) (t?t->siz:0)
typedef long long ll;
const int INF=1000000007;
const int maxn=200000+5;

inline int read(){
	char ch=getchar(); int f=1,x=0;
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f*x;
}

inline int rnd() {
        static int rfx=12345678;
        rfx+=rfx<<2|1;
        return rfx;
}
typedef struct nod {
        int val,siz,fix;
        int afg,rfg,mn;
        nod* son[2];
        inline void upd() {
                mn=val+afg;
                if(son[0]) mn=min(mn,son[0]->mn+son[0]->afg);
                if(son[1]) mn=min(mn,son[1]->mn+son[1]->afg);
                siz=Siz(son[0])+Siz(son[1])+1;
        }
        inline void psd() {
                if(rfg) {
                        swap(son[0],son[1]),rfg=0;
                        if(son[0]) son[0]->rfg^=1;
                        if(son[1]) son[1]->rfg^=1;
                }
                if(afg) {
                        val+=afg;
                        mn+=afg;
                        if(son[0]) son[0]->afg+=afg;
                        if(son[1]) son[1]->afg+=afg;
                        afg=0;
                }
                return;
        }
        inline void init(int v) {
                mn=v;
                val=v;
                siz=1;
                afg=rfg=0;
                fix=rnd();
                return;
        }
}*Treap;
Treap root;
typedef pair<Treap,Treap> Droot;

nod fre[maxn]; int top=-1;
Treap gnd(int v) {
        Treap t=&fre[++top];
        t->init(v);
        return t;
}

Treap merge(Treap a,Treap b) {
        if(!a) return b;
        if(!b) return a;
        if(a->fix<b->fix) {
                a->psd();
                //a->mn=INF;
                a->son[1]=merge(a->son[1],b);
                a->upd();
                return a;
        }else{
                b->psd();
                //a->mn=INF;
                b->son[0]=merge(a,b->son[0]);
                b->upd();
                return b;
        }
}
Droot split(Treap t,int k) {
        if(!t) return Droot(NULL,NULL);
        t->psd();
        //t->mn=INF;
        Droot droot;
        if(Siz(t->son[0])>=k) {
                droot=split(t->son[0],k);
                t->son[0]=droot.second;
                t->upd();
                droot.second=t;
        }else{
                droot=split(t->son[1],k-Siz(t->son[0])-1);
                t->son[1]=droot.first;
                t->upd();
                droot.first=t;
        }
        return droot;
}
Treap plt,prt,pmd;
inline void cut(int l,int r) {
        Droot d1=split(root,l-1),d2=split(d1.second,r-l+1);
        plt=d1.first;prt=d2.second;pmd=d2.first;
}
inline void join() {
        root=merge(merge(plt,pmd),prt);
}
void print(Treap t) {
        if(!t)return;
        if(t->son[0]) print(t->son[0]);
        printf("val=%d mn=%d tag=%d\n",t->val,t->mn,t->afg);
        if(t->son[1]) print(t->son[1]);
}
int N,M;
void input() {
        N=read();
        root=gnd(read());
        REP(i,2,N) {root=merge(root,gnd(read()));}
        int l,r,t;
        M=read();
        //print(root),putchar('\n'); 1 2 3 4 5  1 3 4 2 5
        REP(i,1,M) {
                char odr[10];
                scanf("%s",odr);
                Droot droot,x,y;
                switch(odr[0]) {
                case 'A'://add
                        l=read(),r=read(),t=read();
                        cut(l,r);
                        pmd->afg+=t;
                        //print(pmd);
                        pmd->psd();
                        join();
                        break;
                case 'R':
                        if(odr[4]=='R') {
                                l=read(),r=read();
                                cut(l,r);
                                pmd->rfg^=1;
                                join();
                        }else{
                                l=read(),r=read(),t=read();
                                t%=(r-l+1);
                                t+=(r-l+1);
                                t%=(r-l+1);
                                cut(l,r);
                                droot=split(pmd,(r-l+1)-t);
                                pmd=merge(droot.second,droot.first);
                                join();
                        }
                        break;
                case 'I':
                        droot=split(root,read());
                        root=merge(merge(droot.first,gnd(read())),droot.second);
                        break;
                case 'D':
                        l=read();
                        x=split(root,l-1);
                        y=split(x.second,1);
                        root=merge(x.first,y.second);
                        break;
                case 'M':
                        l=read(),r=read();
                        cut(l,r);
                        printf("%d\n",pmd->mn);
                        join();
                        break;
                }
               //print(root),putchar('\n');
        }
}

int main() {
	input();
	return 0;
}
