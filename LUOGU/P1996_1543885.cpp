#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int x[10001]={0};//初始设置每个人都是活着的
int main(){
  int i=0,j=0,k,m,n,sum=0;
  scanf("%d%d",&n,&m);
  while(sum<n){
    i++;  
    if(i>n)
      i=1;//再一次循环
    if(x[i]==0)//活着的进行，死的忽略
      j++;
    if(j==m){
      printf("%d ",i);//输出
      sum++;//死亡人数
      x[i]++;//记录死亡
      j=0;//j清零
    }
  }
  printf("\n");
  return 0;
}