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

int v[4];

int main() {
  per (i,1,4) v[i]=read();
  v[0]=read();
  int mn=v[0];
  // rep (i,0,4) mn=min(mn,v[i]);
  if (mn*2<v[1]) {
    puts("-1");
    return 0;
  }
  if (mn>2*v[1]) {
    puts("-1");
    return 0;
  }
  int v1=max(v[1],mn);
  int v2=max(max(v[2],v1+1),mn*2+1);
  if (v2>2*v[2]) {
    puts("-1");
    return 0;
  }
  int v3=max(v2+1,v[3]);
  if (v3>2*v[3]) {
    puts("-1");
    return 0;
  }
  printf("%d\n%d\n%d\n",v3,v2,v1);
  return 0;
}
