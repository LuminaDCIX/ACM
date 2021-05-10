#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;

const int maxp=2000;
int t;
int T,W,n;
int f[maxp+5][maxp+5];
int bs[maxp+5],as[maxp+5];
int bp[maxp+5],ap[maxp+5];
int a[maxp+5],b[maxp+5],head,tail;

int main()
{
	scanf("%d",&t);
	while (t--) {
		scanf("%d%d%d",&T,&n,&W);
		for (int i=1;i<=T;++i) {
			scanf("%d%d%d%d",&ap[i],&bp[i],&as[i],&bs[i]);
		}
		for (int i=0;i<=T;++i) {
			for (int j=0;j<=n;++j) {
				f[i][j]=-100000000;
			}
		}
		for (int i=1;i<=W+1;++i) {
			int c=min(n,as[i]);
			for (int j=0;j<=c;++j) {
				f[i][j]=-j*ap[i];
			}
		}
		for (int i=1;i<=W+1;++i) {
			for (int j=0;j<=n;++j) {
				f[i][j]=max(f[i-1][j],f[i][j]);
			}
		}
		for (int i=W+2;i<=T;++i) {
			head=tail=0;
			for (int j=0;j<=n;++j) {
				int x=j;
				int y=f[i-W-1][j]+j*ap[i];
				//printf("%d %d %d\n",x,y,b[tail-1]);
				while (head<tail&&b[tail-1]<y) {
					tail--;
				}
				a[tail]=j;
				b[tail++]=y;
				while (head<tail&&j-a[head]>as[i]) {
					head++;
				}
				//printf("%d\n",b[head]);
				f[i][j]=max(max(f[i][j],f[i-1][j]),b[head]-j*ap[i]);
				//printf("f[%d][%d]=%d\n",i,j,f[i][j]);
			}
			head=tail=0;
			for (int j=n;j>=0;--j) {
				int x=j;
				int y=f[i-W-1][j]+j*bp[i];
				while (head<tail&&b[tail-1]<y) {
					tail--;
				}
				a[tail]=x;
				b[tail++]=y;
				while (head<tail&&a[head]-j>bs[i]) {
					head++;
				}
				f[i][j]=max(max(f[i-1][j],f[i][j]),b[head]-j*bp[i]);
				//printf("f[%d][%d]=%d\n",i,j,f[i][j]);
			}
		}
		int ans=0;
		for (int i=0;i<=n;++i) {
			ans=max(ans,f[T][i]);
		}
		printf("%d\n",ans);
	}
	return 0;
}