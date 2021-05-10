#include<cmath>
#include<cstdio>

using namespace std;

int n,k;
int add,ans;

int main()
{
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;++i) {
		int t;
		scanf("%d",&t);
		add+=t;
	}
	if (double(add)/n>double(k)-0.5) {
		printf("%d\n",0);
		return 0;
	}
	else ans=ceil((add+1.0*n/2-n*k)*(-2));
	printf("%d\n",ans);
	return 0;
}