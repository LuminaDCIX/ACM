#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=(a);i<=(n);++i)
#define per(i,a,n) for (int i=(n);i>=(a);--i)
typedef long long ll;
const int N=1e6+5,M=N*2+5;
char str[N];
int n;
struct sam {
    int nxt[M][26],fa[M],len[M],siz[M];
    int tot,lst;
    inline int nw(int l) {
        ++tot;
        len[tot]=l;
        return tot;
    }
    inline void init() {
        lst=nw(0);
    }
    inline void extend(int x) {
        int p=lst;
        int np=nw(len[p]+1);
        while (p&&nxt[p][x]==0) {
            nxt[p][x]=np;
            p=fa[p];
        }
        if (!p) fa[np]=1;
        else {
            int q=nxt[p][x];
            if (len[q]==len[p]+1) fa[np]=q;
            else {
                int nq=nw(len[p]+1);
                fa[nq]=fa[q];
                fa[q]=nq;
                fa[np]=nq;
                memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
                while (p&&nxt[p][x]==q) {
                    nxt[p][x]=nq;
                    p=fa[p];
                }
            }
        }
        lst=np;
        siz[lst]=1;
    }
    int c[N],q[M];
    inline void build() {
        rep (i,2,tot) c[len[i]]++;
        rep (i,1,n) c[i]+=c[i-1];
        rep (i,2,tot) q[c[len[i]]--]=i;
        per (i,1,tot-1) siz[fa[q[i]]]+=siz[q[i]];
    }
    ll get(char *t,int lim) {
        int n=strlen(t+1);
        int nw=1,in=0;
        ll ans=0;
        // cerr<<n<<" "<<lim<<endl;
        rep (i,1,n) {
            int x=t[i]-'a';
            while (nw!=1&&nxt[nw][x]==0) nw=fa[nw],in=len[nw];
            if (nxt[nw][x]!=0) nw=nxt[nw][x],++in;
            while (fa[nw]!=0&&len[fa[nw]]>=lim) nw=fa[nw],in=len[nw];
            if (in>=lim) ans+=siz[nw];
        }
        return ans;
    }
} ss;
char s[N],t[M];
int nxt[N];
inline int getnxt(char *s,int len) {
    int j=0;
    nxt[1]=0;
    rep (i,2,len) {
        while (j&&s[j+1]!=s[i]) j=nxt[j];
        if (s[j+1]==s[i]) ++j;
        nxt[i]=j;
    }
    int k=len-nxt[len];
    if (len%k==0) return k;
    return len;
}
inline void solve() {
    int tlen=0;
    int slen=strlen(s+1);
    rep (i,1,slen) t[++tlen]=s[i];
    rep (i,1,slen) t[++tlen]=s[i];
    int k=getnxt(s,slen);
    // cerr<<"k="<<k<<endl;
    t[slen+k]=0;
    printf("%lld\n",ss.get(t,slen));
}
int main() {
    scanf("%s",str+1);
    n=strlen(str+1);
    ss.init();
    rep (i,1,n) ss.extend(str[i]-'a');
    ss.build();
    int m;
    scanf("%d",&m);
    rep (i,1,m) {
        scanf("%s",s+1);
        solve();
    }
    return 0;
}
