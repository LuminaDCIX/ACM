#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<vector>

using namespace std;

const int maxn=50;
const int inf=(1<<20)-1;
int w[maxn*4+5][maxn*4+5];
int cost[maxn+5][maxn+5][maxn+5];
int order[maxn+5][maxn+5]; //i need order[i][j] j item
int item[maxn+5][maxn+5]; // i provide item[i][j] j item
bool visl[maxn*4+5],visr[maxn*4+5];//
int lx[maxn*4+5],ly[maxn*4+5];//
int link[maxn*4+5];//
int N,M,K,temp,n,m;//
vector<int> r[maxn+5],l[maxn+5];//

bool dfs(int x)
{
  visl[x]=true;
  for(int y=0;y<m;++y){
    if(!visr[y]){
      if(lx[x]+ly[y]==w[x][y]){
        visr[y]=1;
        if(link[y]==-1||dfs(link[y])){
          link[y]=x;
          return 1;
        }
      }
      else{
        temp=min(temp,lx[x]+ly[y]-w[x][y]);
      }
    }
  }
  return 0;
}

int main()
{
  while(scanf("%d%d%d",&N,&M,&K)&&(N+M+K)){
    for(int i=0;i<N;++i){
      for(int j=0;j<K;++j){
        scanf("%d",&order[i][j]);
      }
    }
    for(int i=0;i<M;++i){
      for(int j=0;j<K;++j){
        scanf("%d",&item[i][j]);
      }
    }
    for(int k=0;k<K;++k){
      for(int i=0;i<N;++i){
        for(int j=0;j<M;++j){
          scanf("%d",&cost[k][i][j]); //move from j to i shop
        }
      }
    }
    int tot=0,ans=0;
    bool succ=1;
    for(int k=0;k<K&&succ;++k){
      n=0,m=0;
      tot=0;
      for(int i=0;i<N;++i){
        l[i].clear();
      }
      for(int j=0;j<M;++j){
        r[j].clear();
      }
      for(int i=0;i<N;++i){
        n+=order[i][k];
        for(int j=0;j<order[i][k];++j){
          l[i].push_back(tot++);
        }
      }
      tot=0;
      for(int i=0;i<M;++i){
        m+=item[i][k];
        for(int j=0;j<item[i][k];++j){
          r[i].push_back(tot++);
        }
      }
      if(m<n){
        succ=0;
        break;
      }
      //printf("n=%d m=%d\n",n,m);
      memset(w,0,sizeof(w));
      memset(link,-1,sizeof(link));
      memset(lx,0x80,sizeof(lx));
      memset(ly,0,sizeof(ly));
      for(int i=0;i<N;++i){
        for(int j=0;j<M;++j){
          for(int p=0;p<l[i].size();++p){
            for(int q=0;q<r[j].size();++q){
              w[l[i][p]][r[j][q]]=-cost[k][i][j];
              //printf("%d->%d=%d\n",l[i][p],r[j][q],w[l[i][p]][r[j][q]]);
            }
          }
        }
      }
      //puts("");
      for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
          lx[i]=max(lx[i],w[i][j]);
        }
      }
      for(int i=0;i<n;++i){
        //for(int p=0;p<n;++p){
        //  printf("%d ",lx[p]);
        //}
       // puts("");
        while(true){
          memset(visl,0,sizeof(visl));
          memset(visr,0,sizeof(visr));
          temp=inf;
          if(dfs(i)){
            break;
          }
          //puts("1");
          if(temp==inf){
            succ=0;
            break;
          }
          for(int j=0;j<n;++j){
            if(visl[j]){
              lx[j]-=temp;
            }
          }
          for(int j=0;j<m;++j){
            if(visr[j]){
              ly[j]+=temp;
            }
          }
        }
      }
      for(int i=0;i<n;++i){
        ans+=lx[i];
      }
      for(int j=0;j<m;++j){
        ans+=ly[j];
      }
    }
    printf("%d\n",succ?-ans:-1);
  }
  return 0;
}