#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;

int n,tot;
bool f[105][205];
vector<int> id[205];
vector<int> ans[2];
bool E[105][105],G[105][105];
bool vis[105],fal;
int c[105],t[105][205];

void input()
{
  scanf("%d",&n);
  int to;
  for (int i=1;i<=n;++i) {
    scanf("%d",&to);
    while (to) {
      E[i][to]=1;
      scanf("%d",&to);
    }
  }
  for (int i=1;i<=n;++i) {
    for (int j=1;j<=n;++j) if (i!=j) {
      if ((int)E[i][j]+(int)E[j][i]<=1) {
        G[i][j]=G[j][i]=1;
      }
    }
  }
	/*for (int i=1;i<=n;++i) {
		for (int j=1;j<=n;++j) {
			printf("%d ",G[i][j]);
		}
		puts("");
	}*/
  return;
}

void dfs(int u,bool col) 
{
  vis[u]=1;
  c[u]=col;
  id[tot+col].push_back(u);
  for (int v=1;v<=100;++v) if (v!=u) {
    if (!vis[v]&&G[u][v]) {
      dfs(v,col^1);
    }
    if (vis[v]&&G[u][v]&&c[v]==col) {
      fal=1;
      return;
    }
  }
  return;
}


inline void print(int x)
{
	/*printf("%d\n",x);
	for (int i=1;i<=tot;++i) {
		for (int j=0;j<id[i].size();++j) {
			printf("%d ",id[i][j]);
		}
		puts("");
	}*/
	for (int m=tot>>1;m>=1;--m) {
		if (t[m][x]+(int)id[m*2].size()-(int)id[m*2-1].size()==x) {
			ans[0].push_back(m*2);
			ans[1].push_back(m*2-1);
		}
		else if(t[m][x]+(int)id[m*2-1].size()-(int)id[m*2].size()==x) {
			ans[0].push_back(m*2-1);
			ans[1].push_back(m*2);
		}
		x=t[m][x];
	}
	for (int i=0;i<=1;++i) {
		int cnt=0;
		for (int j=0;j<ans[i].size();++j) {
			cnt+=id[ans[i][j]].size();
		}
		printf("%d",cnt);
		for (int j=0;j<ans[i].size();++j) {
			for (int k=0;k<id[ans[i][j]].size();++k) {
				printf(" %d",id[ans[i][j]][k]);
			}
		}
		puts("");
	}
	return;
}

void solve()
{
  memset(c,-1,sizeof(c));
  f[0][100]=1;
  for (int i=1;i<=n;++i) if (!vis[i]) {
    ++tot;
    dfs(i,0);
		if (fal) {
			puts("No solution");
			return;
		}
    ++tot;
    int val=0;
    for (int i=0;i<=200;++i) if ((val=i-((int)id[tot-1].size()-(int)id[tot].size()))>=1&&val<=200) {
    	if (f[(tot>>1)-1][val]) {
				f[tot>>1][i]|=1;
				t[tot>>1][i]=val;
			}
    }
    
		for (int i=0;i<=200;++i) if ((val=i-((int)id[tot].size()-(int)id[tot-1].size()))>=1&&val<=200) {
    	if (f[(tot>>1)-1][val]) {
				f[tot>>1][i]|=1;
				t[tot>>1][i]=val;
			}
		}
  }
	int mn1=200,mn2=200;
	for (int i=100;i<=200;++i) {
		if (f[tot>>1][i]) {
			mn1=i;
			break;
		}
	}
	for (int i=100;i>=1;--i) {
		if (f[tot>>1][i]) {
			mn2=i;
			break;
		}
	}
	print(mn1-100>100-mn2?mn2:mn1);
	return;
}

int main()
{
  input();
  solve();
  return 0;
}
