#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>

using namespace std;

int a[105],b[105];
int n1,n2,T;
int f[105][105];

int main()
{
	scanf("%d",&T);
	while (T--) {
		scanf("%d%d",&n1,&n2);
		for (int i=1;i<=n1;++i) {
			scanf("%d",&a[i]);
		}
		for (int i=1;i<=n2;++i) {
			scanf("%d",&b[i]);
		}
		memset(f,0,sizeof(f));
		for (int i=1;i<=n1;++i) {
			for (int j=1;j<=n2;++j) {
				f[i][j]=max(f[i-1][j],f[i][j-1]);
				if (a[i]!=b[j]) {
					int l1=0,l2=0;
					for (int k=i;k>=1;--k) {
						if (a[k]==b[j]) {
							l1=k;
							break;
						}
					}
					for (int k=j;k>=1;--k) {
						if (a[i]==b[k]) {
							l2=k;
							break;
						}
					}
					if (l1&&l2) {
						f[i][j]=max(f[i][j],f[l1-1][l2-1]+2);
					}
				}
			}
		}
		printf("%d\n",f[n1][n2]);
	}
	return 0;
}