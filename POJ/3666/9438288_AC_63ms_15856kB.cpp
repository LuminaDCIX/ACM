#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>

using namespace std;

const int maxn=2000;
int n;
int a[maxn+5];
int nums[maxn+5];
int f[maxn+5][maxn+5];
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		scanf("%d",&a[i]);
		nums[i]=a[i];
	}
	sort(nums,nums+n);
	int m=unique(nums,nums+n)-nums;
	for(int i=1;i<n;++i){
		int bar=f[i-1][0];
		for(int j=0;j<m;++j){
			bar=min(bar,f[i-1][j]);
			f[i][j]=bar+abs(a[i]-nums[j]);
		}
	}
	int ans=1<<30;
	for(int i=0;i<m;++i){
		ans=min(ans,f[n-1][i]);
	}
	printf("%d\n",ans);
	return 0;
}

