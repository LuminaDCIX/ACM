#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<vector>
using namespace std;

const int maxn=50;
const int inf=(int)1e9;
typedef long long ll;
ll f[maxn+5][maxn+5][2];
int op[maxn+5];
int opt[maxn+5];
int a[maxn+5];
int t[maxn+5];
int n;
vector<int> edge;
//t->+ x->x
//   1    2
//0  min 
//1 max
inline void solve()
{
	for(int i=0;i<=n;++i){
		for(int j=0;j<=n;++j){
			f[i][j][0]=inf;
			f[i][j][1]=-inf;
		}
	}
	for(int i=1;i<=n;++i){
		f[i][i][0]=f[i][i][1]=t[i];
	}
	for(int len=2;len<=n;++len){//qujian chang du
		for(int l=1;l<n;++l){//zuo duan dian 
			int r=l+len-1;//you duan dian
			if(r>n){
				break;
			}
			for(int k=l;k<r;++k){
				if(opt[k]==1){
					f[l][r][0]=min(f[l][r][0],f[l][k][0]+f[k+1][r][0]);
					f[l][r][1]=max(f[l][r][1],f[l][k][1]+f[k+1][r][1]);
				}
				else{
					f[l][r][0]=min(f[l][r][0],f[l][k][0]*f[k+1][r][0]);
					f[l][r][0]=min(f[l][r][0],f[l][k][1]*f[k+1][r][1]);
					f[l][r][0]=min(f[l][r][0],f[l][k][1]*f[k+1][r][0]);
					f[l][r][0]=min(f[l][r][0],f[l][k][0]*f[k+1][r][1]);
					f[l][r][1]=max(f[l][r][1],f[l][k][0]*f[k+1][r][0]);
					f[l][r][1]=max(f[l][r][1],f[l][k][1]*f[k+1][r][1]);
				}
			}
		}
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		char ch=getchar();
		while(ch<'a'||ch>'z'){
			ch=getchar();
		}
		if(ch=='t'){
			op[i]=1;
		}
		else{
			op[i]=2;
		}
		scanf("%d",&a[i]);
	}
	ll ans=-inf;
	for(int i=1;i<=n;++i){
		int cnt=0;
		int pos=i;
		while(cnt<n){
			opt[++cnt]=op[((pos+1)==n+1)?1:(pos+1)];
			t[cnt]=a[pos];
			if(pos==n){
				pos=1;
			}
			else{
				++pos;
			}
		}
		solve();
		if(ans==f[1][n][1]){
			edge.push_back(i);
		}
		if(ans<f[1][n][1]){
			edge.clear();
			edge.push_back(i);
			ans=f[1][n][1];
		}
	}
	printf("%lld\n",ans);
	for(int i=0;i<edge.size();++i){
		if(i){
			putchar(' '); 
		}
		printf("%d",edge[i]);
	}
	puts("");
	return 0;
}