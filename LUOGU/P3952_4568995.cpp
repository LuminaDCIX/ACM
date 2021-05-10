#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#define M 305
#define for1(a,b,i) for(register int i=a;i<=b;++i)
#define for2(a,b,i) for(register int i=a;i>=b;--i)
using namespace std;
typedef long long ll;
inline int read(){
    char x=getchar(); int f=1,sum=0;
    for(;!isdigit(x);x=getchar()) if(x=='-') f=-1;
    for(;isdigit(x);x=getchar()) sum=sum*10+x-'0';
    return f*sum;
}

int n,f,Kuo,ans;
string a[M],vis_[M];  bool judge_;
int is_n[M];

void getfu(){
	f=0;
    int len=a[1].size();
    if(a[1][2]=='n'){
	   int pos=4;
	   while(isdigit(a[1][pos])){
	      f=f*10+a[1][pos]-'0';
	      pos++;
	   }
	}
	else f=0;
}

inline bool find_(string now){
    for1(1,Kuo-1,i)
	   if(vis_[i]==now) return 1;
    return 0;
}

inline int pan__(string now){
	int size=now.size();
	if(isdigit(now[0])){
	   int num=0;
	   for1(1,size,i)
	     num=num*10+now[i-1]-'0';
	   return num;
	}
	else return 0;
}

void getans(){
    int cnt=0;
    for1(1,Kuo,i) 
	   if(is_n[i]==1) cnt++;
	   else if(is_n[i]==2) break;
    ans=max(ans,cnt);
}

inline void get_F(int id){
	int size=a[id].size(); 
    if(a[id][0]=='F'){
	   Kuo++;  
	  
	   int pos=3;
	   while(a[id][pos-1]!=' ') pos++;
	   string ha=a[id].substr(2,pos-2);
	   if(find_(ha)) {judge_=1;return;} 
	   vis_[Kuo]=ha;
	   
	   pos++;
	   int be_gin=pos,haha1=0,haha2=0;
	   while(a[id][pos-1]!=' ') pos++;
	   haha1=pan__(a[id].substr(be_gin-1,pos-be_gin));
	   
	   pos++; be_gin=pos;
	   while(pos<=size&&a[id][pos-1]!=' ') pos++;
	   haha2=pan__(a[id].substr(be_gin-1,pos-be_gin));
	    
	   if(haha1&&haha2&&haha1<=haha2) is_n[Kuo]=0;
	   else if(haha1&&haha2&&haha1>haha2) is_n[Kuo]=2;
	   else if(!haha1&&haha2) is_n[Kuo]=2;
	   else if(!haha1&&!haha2) is_n[Kuo]=0;
	   else is_n[Kuo]=1;  
	}
    else{
	   Kuo--;
	   if(Kuo<0) judge_=1;
	}
	getans();
}

void init(){
    judge_=ans=0; memset(is_n,0,sizeof(is_n));
    Kuo=0;
}

int main(){
    int T=read();
    while(T--){
       init();
	   n=read();
	   for1(1,n+1,i) getline(cin,a[i]);
	   getfu();
	   
	   for1(2,n+1,i){ 
	      get_F(i);
          if(judge_) break;
	   }
	   if(Kuo) judge_=1;
	   if(judge_) printf("ERR\n");
	   else{
	      if(ans==f) printf("Yes\n");
	      else  printf("No\n");
	   }
	}
    return 0;
}
