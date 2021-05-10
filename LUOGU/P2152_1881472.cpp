#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

char sA[10005],sB[10005];
const int Base=1000000000;
const int Width=9;
struct BigInt {

    int s[10000],l;
    BigInt operator = (char* str) {
        l=0;
        int len=strlen(str);
        l=len/9+3;
        for(int i=1;i<=l;i++) {
            int k1=max(0,len-i*9),k2=len-(i-1)*9;
            for (int j=k1;j<k2;j++) s[i-1]=s[i-1]*10+str[j]-'0';
        }
        while(l&&s[l-1]==0)l--;
        return *this;  
    }

    BigInt operator - (const BigInt& b) {
        BigInt c;
        memset(c.s,0,sizeof(c.s));
        c.l=0;
        for(int i=0;;i++) {
            if(i>=l&&i>=b.l) break;
            if(i<b.l) c.s[i]=s[i]-b.s[i];
            else if (i<l) c.s[i]=s[i];
            else c.s[i]=0;
            if(c.s[i]<0) c.s[i]+=Base,s[i+1]--;
        }
        c.l=l;
        while(c.l&&c.s[c.l-1]==0)c.l--;
        return c;
    }

    bool operator > (const BigInt &b) const {
        if(l!=b.l) return l>b.l;
        for (int i=l-1;i>=0;i--) if(b.s[i]!=s[i]) return s[i]>b.s[i];
    }
}A,B,mn,mx;
int cnt;
void diva() {
    for(int i=0;i<A.l;i++) {
        if (i&&A.s[i]&1) A.s[i-1]+=Base/2;
        A.s[i]>>=1;
    }
    while(A.l&&A.s[A.l-1]==0)A.l--;
}
void divb() {
    for(int i=0;i<B.l;i++) {
        if (i&&B.s[i]&1) B.s[i-1]+=Base/2;
        B.s[i]>>=1;
    }
    while(B.l&&B.s[B.l-1]==0)B.l--;
}
void mul() {
    for(int i=A.l-1;i>=0;i--) {
        A.s[i]<<=1;
        A.s[i+1]+=A.s[i]/Base;
        A.s[i]%=Base;
    }
    while(A.s[A.l-1]>0) A.l++;
}
int main() {
    ios::sync_with_stdio(false);
    cin>>sA>>sB;
    A=sA,B=sB;
    while(1) {
        bool ok=1;
        if(A.l==B.l) {
            for(int i=0;i<A.l;i++) if(A.s[i]!=B.s[i]) {ok=0; break;}
        } else ok=0;
        if(ok) break;
        if(A.s[0]%2==0&&B.s[0]%2==0) diva(),divb(),cnt++;
        else if(A.s[0]%2==0) diva();
        else if(B.s[0]%2==0) divb();
        else if(A>B) {A=A-B;}
        else {B=B-A;}
    }
    while(cnt--) mul();
    //for(int i=A.l-1;i>=0;i--) cout<<A.s[i];
    while(A.l&&A.s[A.l-1]==0)A.l--;
    for(int i=A.l-1;i>=0;i--) {
        if(i==A.l-1) printf("%d",A.s[i]);
        else printf("%09d",A.s[i]);
    }
    return 0;
}

//