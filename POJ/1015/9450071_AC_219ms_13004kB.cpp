#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<vector>
using namespace std;

const int maxn=200;
const int ad=200*20;
int n,m;
int a[maxn+5],b[maxn+5];
int f[maxn+5][400*20+5];
int pre[maxn+5][400*20+5];
int kase=0;
int main()
{
	while(scanf("%d%d",&n,&m)&&(n+m)){
		for(int i=1;i<=n;++i){
			scanf("%d %d",&a[i],&b[i]);
		}
		memset(f,-1,sizeof(f));
		memset(pre,0,sizeof(pre));
		int ad=m*20;
		f[0][ad]=0;
		for(int j=0;j<m;++j){
			for(int k=0;k<=ad*2;++k){
				if(f[j][k]>=0){
					for(int i=1;i<=n;++i){
						if(f[j][k]+a[i]+b[i]>f[j+1][k+a[i]-b[i]]){
							int t1=j;
							int t2=k;
							while(t1>0&&pre[t1][t2]!=i){
								t2-=a[pre[t1][t2]]-b[pre[t1][t2]];
								t1--;
							}
							if(t1==0){
								f[j+1][k+a[i]-b[i]]=f[j][k]+a[i]+b[i];
								pre[j+1][k+a[i]-b[i]]=i;
							}
						}
					}	
				}	
			}	
		}
		vector<int> ans;
		int i=ad;
		int j=0;
		while(f[m][i+j]<0&&f[m][i-j]<0){
			j++;	
		}
		int k=0;
		if(f[m][i+j]>f[m][i-j]){
			k=i+j;
		}
		else{
			k=i-j;
		}
		printf("Jury #%d\nBest jury has value %d for prosecution and value %d for defence:\n",++kase,(k-ad+f[m][k])/2,(f[m][k]-k+ad)/2);
		for(i=1;i<=m;++i){
			ans.push_back(pre[m-i+1][k]);
			k-=a[ans[i-1]]-b[ans[i-1]];
		}
		sort(ans.begin(),ans.end());
		for(int i=0;i<ans.size();++i){
			printf(" %d",ans[i]);
		} 
		printf("\n\n");
	}
	return 0;
}
