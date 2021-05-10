#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;
#define pb push_back
#define all(v) v.begin(),v.end()
#define siz(x) ((int)x.size())
#define fil(a,x) memset(a,x,sizeof(a))
#define rep(i,a,n) for (int i=(a);i<=(n);++i)
#define per(i,a,n) for (int i=(n);i>=(a);--i)
typedef vector<int> vi;
inline int read() {
    int f=1,x=0,ch=getchar();
    while (!isdigit(ch)) {
        f=(ch=='-')?-1:1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return f*x;
}
const int N=1e5+5;
const int M=6e6+5;
const int SIZ=10;
int n;
char s[N];
int tl[N],fi[N];
int sum[M][SIZ];
int nxt[N],pre[N];
int nw,mak[N];
void del(int p) {
    pre[nxt[p]]=pre[p];
    nxt[pre[p]]=nxt[p];
}
inline void doit() {
    int p=nxt[0];
    int op=1;
    while (p!=0&&p!=n+1) {
        ++nw;
        // cerr<<nw<<" "<<p<<" "<<mak[p]<<endl;
        if (fi[p]==0) fi[p]=nw;
        if (mak[p]) del(p);
        else if (isdigit(s[p])) {
            if (s[p]=='0') {
                mak[p]=1;
                ++sum[nw][s[p]-'0'];
            } else {
                ++sum[nw][s[p]-'0'];
                --s[p];
            }
        } else {
            op=(s[p]=='<')?-1:1;
            int stp=(op==-1)?pre[p]:nxt[p];
            while (mak[stp]) stp=(op==-1)?pre[stp]:nxt[stp];
            if (s[stp]=='<'||s[stp]=='>') mak[p]=1;
        }
        if (op==-1) tl[p]=min(tl[p],nw);
        p=(op==-1)?pre[p]:nxt[p];
    }
    // cerr<<p<<endl;
    if (p==0&&fi[p]==0) fi[p]=++nw;
    if (p==n+1&&fi[p]==0) fi[p]=++nw;
}
void init() {
    // tr[0]=0;
    fil(tl,0x3f);
    nxt[0]=1;
    pre[n+1]=n;
    rep (i,1,n) {
        nxt[i]=i+1;
        pre[i]=i-1;
    }
    while (nxt[0]!=n+1) {
        int lst=nw;
        doit();
        if (nxt[0]!=n+1&&nw-lst==1&&!isdigit(s[nxt[0]])) {
            int k=nxt[0];
            nxt[pre[k]]=nxt[k];
            pre[nxt[k]]=pre[k];
        }
    }
}
int main() {
    n=read();
    int q=read();
    scanf("%s",s+1);
    init();
    rep (i,1,nw) rep (j,0,SIZ-1) sum[i][j]+=sum[i-1][j];
    if (nw>M) assert(0);
    while (q--) {
        int l=read(),r=read();
        if (fi[l]==0x3f3f3f3f) {
            rep (i,0,SIZ-1) printf("%d ",0);
            puts("");
            continue;
        }
        int *t=sum[fi[l]-1],*s;
        if (tl[l]<fi[r+1]||fi[r+1]==0) s=sum[tl[l]];
        else s=sum[fi[r+1]-1];
        rep (i,0,SIZ-1) printf("%d ",s[i]-t[i]);
        puts("");
    }
    return 0;
}