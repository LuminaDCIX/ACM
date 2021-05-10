#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<vector>
#include<list>
using namespace std;
const int maxn=9;

int box[maxn+1][maxn+1];
int ans=0;
int now[maxn+1][maxn+1];
int c[maxn+1][maxn+1]={
{},
{0,6,6,6,6,6,6,6,6,6},
{0,6,7,7,7,7,7,7,7,6},
{0,6,7,8,8,8,8,8,7,6},
{0,6,7,8,9,9,9,8,7,6},
{0,6,7,8,9,10,9,8,7,6},
{0,6,7,8,9,9,9,8,7,6},
{0,6,7,8,8,8,8,8,7,6},
{0,6,7,7,7,7,7,7,7,6},
{0,6,6,6,6,6,6,6,6,6},
};
int exi[3][10];

inline int find_best(int &rx,int &ry) {
  int best=9;
  int ret=0;
  int m=0,b=0,t=0;
  for (int i=1;i<=9;++i) {
    for (int j=1;j<=9;++j) {
      if (now[i][j]) {
        continue;
      }
      t=0,b=0;
      m=t=exi[0][i]|exi[1][j]|exi[2][(i-1)/3*3+(j-1)/3];
      while (m) {
        m-=m&-m;
        b++;
      }
      b=9-b;
      if (b==0) {
        rx=ry=0;
        return ret;
      }
      if (b<best&&b!=0) {
        rx=i;
        ry=j;
        best=b;
        ret=t;
      }
      //printf("%d %d\n",ite->first,ite->second);
    }
  }
  return ret;
}

void dfs(int cnt,int sc) 
{ 
  if (cnt==81) {
    ans=max(ans,sc);
    return;
  }
  int rx=0;
  int ry=0;
  int t=find_best(rx,ry);
  if (rx+ry==0) {
    return;
  }
  for (int i=1;i<=9;++i) {
    if (t&(1<<i>>1)) {
      continue;
    }
    now[rx][ry]=i;
    exi[0][rx]+=(1<<now[rx][ry]>>1);
    exi[1][ry]+=(1<<now[rx][ry]>>1);
    exi[2][(rx-1)/3*3+(ry-1)/3]+=(1<<now[rx][ry]>>1);
    dfs(cnt+1,sc+now[rx][ry]*c[rx][ry]);
    exi[0][rx]-=(1<<now[rx][ry]>>1);
    exi[1][ry]-=(1<<now[rx][ry]>>1);
    exi[2][(rx-1)/3*3+(ry-1)/3]-=(1<<now[rx][ry]>>1);
    now[rx][ry]=0;
  }
  return;
}


int main()
{
  int cnt=0;
  int sc=0;
  for (int i=1;i<=9;++i) {
    for (int j=1;j<=9;++j) {
      scanf("%d",&box[i][j]);
      now[i][j]=box[i][j];
      exi[0][i]=exi[0][i]|(1<<box[i][j]>>1);
      exi[1][j]=exi[1][j]|(1<<box[i][j]>>1);
      exi[2][(i-1)/3*3+(j-1)/3]=exi[2][(i-1)/3*3+(j-1)/3]|(1<<box[i][j]>>1);
      if (now[i][j]) {
        ++cnt;
        sc+=now[i][j]*c[i][j];
      }
    }
  }
  dfs(cnt,sc);
  if (ans==0) {
    puts("-1");
  }
  else {
    printf("%d\n",ans);
  }
  return 0;
}