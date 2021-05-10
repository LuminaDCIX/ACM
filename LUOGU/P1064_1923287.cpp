#include <cstdio>
#include <vector>
#include <cassert>
#include <cstring>
#include <algorithm>
using namespace std;
#define REP(i,a,n) for (int i=a;i<=(n);i++)
#define PER(i,a,n) for (int i=n;i>=a;i--)
#define MEM(a,b) memset(a,b,sizeof(a))
#define PAUSE system("pause")
#define FILE
#define DEBUG

typedef long long ll;
const ll mod=1000000007;
const int maxn=32000;
int m,N,f[61][maxn];int v[61],w[61],b[61],d[61][maxn];
vector<int> s[61];
struct item{
        int val,wgt;
        item(int a,int b) {
                val=a,wgt=b;
        }
};
vector<item> t;

inline int getc() {
    static const int L=1<<15;static char buf[L],*S=buf,*T=buf;
    if(S==T) {T=(S=buf)+fread(buf,1,L,stdin);if(S==T) return EOF;}
    return *S++;
}
inline int read() {
    int c; while(!isdigit(c=getc())); int tem=c-'0';
    while(isdigit(c=getc())) tem=(tem<<1)+(tem<<3)+c-'0';
    return tem;
}
void input() {
        N=read(),m=read();N/=10;
        int r,p,q;
        REP (i,1,m) {
                r=read(),p=read(),q=read();
                w[i]=r/10,v[i]=r*p;
                if(q!=0)s[q].push_back(i),b[i]=1;
        }
        return;
}
//f[i]=max(f[i],f[i-cost]+w)
void print(int k) {
        printf("\n%d\n",k);
        REP(i,1,N) {if(f[k][i]!=0) printf("i=%d %d \n",i,f[k][i]);}
        //REP(i,1,m) {REP(j,0,(int)s[i].size()-1) printf("%d ",s[i][j]); putchar('\n');}
}
void solve() {
        REP(i,1,m) {
                int mx=(int)s[i].size()-1;
                REP(j,1,N) f[i][j]=f[i-1][j];
                if(b[i]==1) {continue;}
                REP(k,0,mx) {
                    PER(j,0,N-w[i]) if(j-w[s[i][k]]>=0) d[i][j]=max(d[i][j],d[i][j-w[s[i][k]]]+v[s[i][k]]);
                }
                t.clear();
                t.push_back(item(0,0));
                REP(j,1,N-w[i]) if(d[i][j]!=d[i][j-1]) {t.push_back(item(d[i][j],j));}
                mx=(int)t.size()-1;
                REP(k,0,mx) {
                        PER(j,0,N-w[i]) {
                                if(j-t[k].wgt>=0) f[i][j+w[i]]=max(f[i][j+w[i]],f[i-1][j-t[k].wgt]+t[k].val+v[i]);
                                else f[i][j]=max(f[i-1][j],f[i][j]);
                        }
                }
        }
        int ans=0;
        REP(i,1,N) ans=max(ans,f[m][i]);
        printf("%d\n",ans);
}

int main() {
	memset(f,0,sizeof(f));
	memset(d,0,sizeof(d));
	input();
	solve();
	return 0;
}
