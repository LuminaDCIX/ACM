#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib>

using namespace std;

const int maxn=100000;
bool f[maxn+5];
int used[maxn+5];
int n,m;
int c[105],a[105];
//c->num
int main()
{
	while(scanf("%d%d",&n,&m)&&(n+m)){
		for(int i=1;i<=n;++i){
			scanf("%d",&a[i]);
		}
		for(int i=1;i<=n;++i){
			scanf("%d",&c[i]);
		}
		memset(f,0,sizeof(f));
		f[0]=1;
		for(int i=1;i<=n;++i){
			memset(used,0,sizeof(used));
			for(int j=a[i];j<=m;++j){
				if(!f[j]&&f[j-a[i]]&&used[j-a[i]]<c[i]){
					used[j]=used[j-a[i]]+1;
					f[j]=1;
				}
			}
		}
		int ans=0;
		for(int i=1;i<=m;++i){
			if(f[i]){
				ans++;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}