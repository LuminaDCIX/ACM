#include<cmath>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
inline int read()
{
  int f=0,s=1,ch;
  for(ch=getchar();!isdigit(ch);(ch=='-')?s=-1:s=1,ch=getchar());
  for(;isdigit(ch);f=(f<<1)+(f<<3)+ch-'0',ch=getchar());
  return f*s;
}
typedef long long ll;
const int maxn=50;
int v[55][55],n,m;
int f[maxn*2][55][55];
inline bool judge(int x,int y)
{
  return x>=0&&y>=0&&x<n&&y<m;
}
inline void update(int i,int x_1,int x_2)//3 1 2
{
  int y_1=i-x_1;
  int y_2=i-x_2;
  //down down
  int temp=-1;
  if(judge(x_1+1,y_1)&&judge(x_2+1,y_2)){
    temp=v[x_1+1][y_1];
    if(x_1+1!=x_2+1&&y_1!=y_2){
      temp+=v[x_2+1][y_2];
    }
    f[i+1][x_1+1][x_2+1]=max(f[i+1][x_1+1][x_2+1],f[i][x_1][x_2]+temp);
  }
  //right down
  if(judge(x_1,y_1+1)&&judge(x_2+1,y_2)){
    temp=v[x_1][y_1+1];
    if(x_1!=x_2+1&&y_1+1!=y_2){
      temp+=v[x_2+1][y_2];
    }
    f[i+1][x_1][x_2+1]=max(f[i+1][x_1][x_2+1],f[i][x_1][x_2]+temp);
  }
  //down right
  if(judge(x_1+1,y_1)&&judge(x_2,y_2+1)){
    temp=v[x_1+1][y_1];
    if(x_1+1!=x_2&&y_1!=y_2+1){
      temp+=v[x_2][y_2+1];
    }
    f[i+1][x_1+1][x_2]=max(f[i+1][x_1+1][x_2],f[i][x_1][x_2]+temp);
  }
  //right right
  if(judge(x_1,y_1+1)&&judge(x_2,y_2+1)){
    temp=v[x_1][y_1+1];
    if(x_1!=x_2&&y_1+1!=y_2+1){
      temp+=v[x_2][y_2+1];
    }
    f[i+1][x_1][x_2]=max(f[i+1][x_1][x_2],f[i][x_1][x_2]+temp);
  }   
}
int main()
{
  n=read(),
  m=read();
  for(int i=0;i<n;++i){
    for(int j=0;j<m;++j){
      v[i][j]=read();
    }
  }  
  memset(f,0xcfcf,sizeof(f));
  f[0][0][0]=v[0][0];
  for(int i=0;i<m+n-2;++i){
    for(int j=0;j<n;++j){
      for(int k=0;k<n;++k){
        update(i,j,k);  
      }
    }
  }
  printf("%d\n",f[n+m-2][n-1][n-1]);
  return 0;
}