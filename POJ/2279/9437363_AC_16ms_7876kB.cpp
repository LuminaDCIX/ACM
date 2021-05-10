#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>

using namespace std;
typedef long long ll;
ll f[35][35][35][35][35];
int a[7];
int n;
int main()
{
	while(scanf("%d",&n)&&n){
		memset(a,0,sizeof(a));
		for(int i=0;i<n;++i){
			scanf("%d",&a[i]);
		}
		//memset(f,0,sizeof(f));
		f[0][0][0][0][0]=1;
		for(int i=0;i<=a[0];++i){
			for(int j=0;j<=a[1];++j){
				for(int k=0;k<=a[2];++k){
					for(int l=0;l<=a[3];++l){
						for(int m=0;m<=a[4];++m){
							ll &ans=f[i][j][k][l][m];
							if(i+j+k+l+m){
								ans=0;
							}
							if(i>=1){
								ans+=f[i-1][j][k][l][m];
							}
							if(i>=j&&j>=1){
								ans+=f[i][j-1][k][l][m];
							}
							if(j>=k&&k>=1){
								ans+=f[i][j][k-1][l][m];
							}
							if(k>=l&&l>=1){
								ans+=f[i][j][k][l-1][m];
							}
							if(l>=m&&m>=1){
								ans+=f[i][j][k][l][m-1];
							}
						}
					}
				}
			}
		}
		printf("%lld\n",f[a[0]][a[1]][a[2]][a[3]][a[4]]);
	}
	return 0;
}