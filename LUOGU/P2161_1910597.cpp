#include <cstdio>
#include <set>
#include <bitset>
#include <cassert>
#include <cstring>
#include <algorithm>
using namespace std;
#define REP(i,a,n) for (int i=a;i<=n;i++)
#define PER(i,a,n) for (int i=n;i>=a;i--)
#define MEM(a,b) memset(a,b,sizeof(a))
#define PAUSE system("pause")
#define DEBUG 0
typedef long long ll;
const ll mod=1000000007;
const int Max=100000;
int M;
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
struct Node {
        int l,r;
        bool operator<(const Node &v)const{return l==v.l?r<v.r:l<v.l;}
};
set<Node> s;
int main() {
        scanf("%d",&M);
        REP(i,1,M) {
                int ql,qr;
                char c[2];
                scanf("%s",c);
                if (c[0]=='A') {
                        scanf("%d%d",&ql,&qr);
                        Node a=Node{ql,qr};
                        int dc=0;
                        while(1) {
                                set<Node>::iterator it=s.lower_bound(a);
                                if(it->l<=a.r&&a.l<=it->r) {dc++,s.erase(it);continue;}
                                it=s.lower_bound(a);
                                if (it!=s.begin()) {
                                        it--;
                                        if(it->l<=a.r&&a.l<=it->r) {dc++;s.erase(it);continue;}
                                }
                                break;
                        }
                        s.insert(a);
                        printf("%d\n",dc);
                }
                else printf("%d\n",s.size());
        }
        return 0;
}
