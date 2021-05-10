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

string s[12];
int pos[]={0,0,1,2,4,5,6,8,9,10};
int b[]={0,4,8};
int main() {
  rep (i,0,11) getline(cin,s[i]);
  int x=pos[read()],y=pos[read()];
  int xl,yl;
  if (x<=2) xl=0;
  else if (x<=6) xl=1;
  else xl=2;
  if (y<=2) yl=0;
  else if (y<=6) yl=1;
  else yl=2;


  x-=b[xl],y-=b[yl];

  bool ok=false;
  rep (i,b[x],b[x]+3) rep (j,b[y],b[y]+3) if (s[i][j]=='.') ok=1;

  if (!ok) {
    rep (i,0,11) rep (j,0,11) if (s[i][j]=='.') s[i][j]='!';
  } else {
    rep (i,b[x],b[x]+3) rep (j,b[y],b[y]+3) if (s[i][j]=='.') s[i][j]='!';
  }
  rep (i,0,11) cout<<s[i]<<endl;
}
