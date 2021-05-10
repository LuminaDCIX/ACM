#include <map>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define siz(x) ((int)x.size())
#define pb push_back
#define mp make_pair
#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)
#define itr(x) for (__typeof(x) it=x.begin();it!=x.end();++it)
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef map<int,int> mii;
typedef pair<int,int> pii;

int read() {
  int f=1,x=0;char ch=getchar();
  while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
  while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
  return f*x;
}

//head

const int N=1e5+5;

int v[N];

string str[N];
char op[N];

bool check(int x) {
  int cnt=0;
  rep (i,0,26) if (x&(1<<i)) ++cnt;
  return cnt==1;
}

void print(int k) {
  rep (i,0,26) cerr<<((k>>i)&1);
  cerr<<endl;
}

int main() {
  int n=read();
  bool ok=false;
  int k=(1<<26)-1;
  int cnt=0;
  rep (i,0,n) {
    scanf("\n");
    op[i]=getchar(),cin>>str[i];
  }
  char l=str[n-1][0];
  rep (i,0,n) {
    // print(k);
    if (op[i]=='!') {
      if (ok) {
        ++cnt;
        continue;
      }
      int p=0,len=str[i].length();
      rep (j,0,len) p|=1<<(str[i][j]-'a');
      k=k&p;
      if (!ok&&check(k)) ok=1;
    } else if (op[i]=='?') {
      if (ok&&l!=str[i][0]) {
        ++cnt;
      } else if (!ok) {
        int x=1<<(str[i][0]-'a');
        if (str[i][0]!=l) {
          k|=x;
          k^=x;
        }
      }
      if (!ok&&check(k)) ok=1;
    } else {
      int p=0,len=str[i].length();
      rep (j,0,len) p|=1<<(str[i][j]-'a');
      p=((1<<26)-1)^p;
      k=k&p;
      if (!ok&&check(k)) ok=1;
    }
  }
  printf("%d\n",cnt);
  return 0;
}
