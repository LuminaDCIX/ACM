#include <cstdio>
#include <cstdlib>
using namespace std;

const int mod=10001;
int s[210],T;

void input() {
    scanf("%d",&T);
    for (int i=1;i<=T;i++) scanf("%d",&s[i*2-1]);
    return;
}
void solve() {
    int b=0;
    for(int a=0;a<=10001;a++) {
        b=1;
        bool ok=0,flag=0;
        while(b<mod) {
            if(s[3]!=(a*((s[1]*a+b)%mod)+b)%mod) {b++; continue;}
            flag=1;
            for (int i=2;i<=2*T;i++) {
                if (i&1) {
                    int k=((a*s[i-1]+b)%mod);
                    //printf("s[%d]=%d\n",i,k);
                    if(k!=s[i]) {ok=1; break;} 
                } else {
                    s[i]=((a*s[i-1]+b)%mod);
                    //printf("s[%d]=%d\n",i,s[i]);
                }
            }
            if(!ok&&flag) {break;} 
            b++;
        }
        if(!ok&&flag) break;
    }
}

void output() {
    for(int i=2;i<=2*T;i+=2) printf("%d\n",s[i]);
}

int main() {
    input();
    solve();
    output();
    return 0;
}
