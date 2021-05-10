#include<stdio.h>  
#include<iostream>  
#include<queue>  
#include<stack>  
#include<string.h>  
using namespace std;  
typedef struct nn  
{  
    char ch[9];  
    int son;  
  
}node1;  
typedef struct n  
{  
    char way;//记录从父节点到当前节点的走法  
    int father;//记录当前节点的父节点的位置  
}node2;  
node2 Node[40321];//节点  
int fac[8]={1,1,2,6,24,120,720,5040};//阶层  
int cantor(char s[])//计算s在康托展开的位置,每一个都是独一无二的  
{  
    int i,j,k,ans=0;  
    for(i=0;i<8;i++)  
    {  
        k=0;  
        for(j=i+1;j<8;j++)  
        if(s[i]>s[j])  
            k++;  
        ans+=k*fac[7-i];  
    }  
    return ans;  
}  
void BFS(char ch1[])  
{  
    queue<node1>Q;  
    node1 now,next;  
    int i,son,e=0;  
    char tc;  
    son=cantor(ch1);  
    strcpy(now.ch,ch1);now.ch[8]='\0';  
    now.son=son;Node[son].father=0;//最终父节点为本本身  
    Q.push(now);  
    while(!Q.empty())  
    {  
        now=Q.front(); Q.pop();  
        //printf("%s ",now.ch);if(e==300)getchar();e++;用于调试  
        next=now;  
        for(i=0;i<4;i++) {tc=next.ch[i];next.ch[i]=next.ch[7-i];next.ch[7-i]=tc; }  
        son=cantor(next.ch);   next.son=son;  
        if(Node[son].father==-1)  
        {  
            Node[next.son].father=now.son; Node[next.son].way='A';  
            Q.push(next);  
        }  
  
        next=now;  
        tc=next.ch[3];for(i=3;i>0;i--) next.ch[i]=next.ch[i-1];   next.ch[0]=tc;  
        tc=next.ch[4];for(i=4;i<7;i++) next.ch[i]=next.ch[i+1];   next.ch[7]=tc;  
        son=cantor(next.ch);   next.son=son;  
        if(Node[son].father==-1)  
        {  
            Node[next.son].father=now.son; Node[next.son].way='B';  
            Q.push(next);  
        }  
  
        next=now;  
        tc=next.ch[5];next.ch[5]=next.ch[2];next.ch[2]=next.ch[1];next.ch[1]=next.ch[6];next.ch[6]=tc;  
        son=cantor(next.ch);   next.son=son;  
        if(Node[son].father==-1)  
        {  
            Node[next.son].father=now.son; Node[next.son].way='C';  
            Q.push(next);  
        }  
    }  
}  
int main()  
{  
    int c,s,i;  
    char str[9];  
    char ch1[9]={'1','2','3','4','5','6','7','8'};  
        for(i=0;i<40321;i++)  
        Node[i].father=-1;  
  
        BFS(ch1);  
    char Way[10000];  
    while(cin>>ch1>>str)  
    {  
        char pos[10];  
        char des[8];  
        for( i=0;i<8;i++)//转换  
            pos[ch1[i]-'0']=i+1+'0';  
        for( i=0;i<8;i++)  
            des[i]=pos[str[i]-'0'];  
        s=cantor(des);  
        i=0;  
        while(0!=s)//从目标到初太搜索路径  
        {  
            Way[i++]=Node[s].way;//printf("7 ");  
            s=Node[s].father;  
        }  
        while(i--)//输出从初态到目标的路径  
        {  
            printf("%c",Way[i]);  
        }  
        printf("\n");  
    }  
}  