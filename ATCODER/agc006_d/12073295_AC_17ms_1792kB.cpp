#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define fil(x,t) memset(x,t,sizeof(x));
#define siz(x) ((int)x.size())
#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)
#define foreach(e,x) for (__typeof(x.begin()) e=x.begin();e!=x.end();++e)
typedef long long ll;
typedef double db;
typedef map<int,int> mii;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

int read() {
  int f=1,x=0;char ch=getchar();
  while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
  while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
  return f*x;
}

//head

const int N=1e5+5;
const int MAX=2e5+5;

int n;
int a[MAX],t[MAX];

int check(int v){
  int lim=(n<<1)-1;
  rep (i,0,lim) t[i]=(a[i]>=v)?1:0;
  int l=0,r=lim-1;
  rep (i,n-1,lim-1) if(t[i]==t[i+1]) {
    r=i;break;
  }
  per (i,1,n) if(t[i]==t[i-1]) {
    l=i;break;
  }
  if (r==lim-1&&l==0) return t[0];
  if (n-l-1<=r-n+1) return t[l];
  else return t[r];
}
int main(){
  scanf("%d",&n);
  int lim=(n<<1)-1;
  rep (i,0,lim) a[i]=read();

  int low=0,high=lim,ans=0;
  while (low<=high) {
    int mid=(low+high)>>1;
    if(check(mid)) ans=mid,low=mid+1;
    else high=mid-1;
  }
  printf("%d\n",ans);
  return 0;
}